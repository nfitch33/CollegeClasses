from flask import Flask, request, send_file
from audiocraft.models import MusicGen
import torchaudio
import torchaudio.functional as F
import tempfile
import torch
import librosa
import numpy as np
import os
import json
from dotenv import load_dotenv

# --- Load environment variables ---
load_dotenv()
HUGGINGFACE_HUB_TOKEN = os.environ.get("HUGGINGFACE_HUB_TOKEN")
if not HUGGINGFACE_HUB_TOKEN:
    raise RuntimeError("HUGGINGFACE_HUB_TOKEN environment variable not set!")

# --- Flask app ---
app = Flask(__name__)

# --- Load MusicGen model ---
print("🎵 Loading MusicGen melody model...")
model = MusicGen.get_pretrained("facebook/musicgen-melody")
print("✅ Model loaded!")

TARGET_SR = 32000

# --- Scales & Chords ---
MAJOR_SCALE = [0, 2, 4, 5, 7, 9, 11]
POP_PROGRESSIONS = [[0, 4, 9, 5]]
JAZZ_PROGRESSIONS = [[2, 5, 0]]  # ii–V–I

# --- Rhythm Patterns ---
DEFAULT_RHYTHM_PATTERNS = {
    "pop": {"kick": [1, 0, 0, 0], "snare": [0, 0, 1, 0], "hihat": [1, 1, 1, 1]},
    "hiphop": {"kick": [1, 0, 0, 1], "snare": [0, 0, 1, 0], "hihat": [1, 0, 1, 0]},
    "jazz": {"kick": [1, 0, 0, 0], "snare": [0, 0, 1, 0], "hihat": [1, 0, 1, 0]},
}

# --- Helper Functions ---
def detect_key(waveform, sr):
    y = waveform.squeeze().numpy()
    chroma = librosa.feature.chroma_cens(y=y, sr=sr)
    key_index = chroma.sum(axis=1).argmax()
    key_notes = ["C","C#","D","D#","E","F","F#","G","G#","A","A#","B"]
    return key_notes[key_index]

def key_to_midi(key_note):
    note_map = {"C":60,"C#":61,"D":62,"D#":63,"E":64,"F":65,"F#":66,
                "G":67,"G#":68,"A":69,"A#":70,"B":71}
    return note_map.get(key_note, 60)

def generate_chord_progression(key_note, style="pop", length=4):
    base_prog = POP_PROGRESSIONS[0] if style != "jazz" else JAZZ_PROGRESSIONS[0]
    key_midi = key_to_midi(key_note)
    progression = [(key_midi + interval) for interval in base_prog]
    return [progression[i % len(progression)] for i in range(length)]

def harmonize_melodies(melodies, chord_progression):
    if not melodies:
        return None
    harmonized = []
    for i, melody in enumerate(melodies):
        y = melody.squeeze().numpy()
        f0, _, _ = librosa.pyin(y, fmin=65, fmax=1050)
        f0 = f0[~np.isnan(f0)]
        source_pitch = np.median(f0) if len(f0) > 0 else 440.0
        target_pitch = 440.0 * 2 ** ((chord_progression[i % len(chord_progression)] - 69)/12)
        semitones = 12 * np.log2(target_pitch / (source_pitch + 1e-6))
        factor = 2 ** (semitones / 12)
        new_sr = int(TARGET_SR * factor)
        pitched = F.resample(melody, orig_freq=TARGET_SR, new_freq=new_sr)
        harmonized.append(pitched)
    max_len = max(m.shape[1] for m in harmonized)
    aligned = [torch.nn.functional.pad(m, (0, max_len - m.shape[1])) for m in harmonized]
    return sum(aligned) / len(aligned)

def generate_rhythm(style="pop", bars=4):
    patterns = DEFAULT_RHYTHM_PATTERNS.get(style, DEFAULT_RHYTHM_PATTERNS["pop"])
    beat_len = TARGET_SR // 4  # quarter note
    rhythm_audio = torch.zeros(bars * 4 * beat_len)
    for i, beat in enumerate(patterns["kick"] * bars):
        if beat:
            rhythm_audio[i*beat_len:(i+1)*beat_len] += 0.5 * torch.sin(2*np.pi*60*torch.arange(beat_len)/TARGET_SR)
    for i, beat in enumerate(patterns["snare"] * bars):
        if beat:
            rhythm_audio[i*beat_len:(i+1)*beat_len] += 0.5 * torch.sin(2*np.pi*180*torch.arange(beat_len)/TARGET_SR)
    return rhythm_audio.unsqueeze(0)

def load_dali_lyrics(dali_annotation_path):
    with open(dali_annotation_path, 'r', encoding='utf-8') as f:
        ann = json.load(f)
    words = ann['annotations']['annot']['words']
    return " ".join(w['text'] for w in words)

# --- Flask Routes ---
@app.route("/generate", methods=["POST"])
def generate_music():
    prompt = request.form.get("prompt", "a chill lo-fi beat with piano")
    duration = float(request.form.get("duration", 10))
    style = request.form.get("style", "pop")
    dali_ann_path = request.form.get("dali_annotation_path", None)

    # Load lyrics if DALI annotation provided
    if dali_ann_path:
        lyrics = load_dali_lyrics(dali_ann_path)
        prompt += " | Lyrics: " + lyrics

    print(f"🎶 Generating music with prompt: {prompt} ({duration}s)")
    model.set_generation_params(duration=duration)

    # Check if any melodies uploaded
    uploaded_files = request.files.getlist("melodies")
    melody_tensors = []
    if uploaded_files and any(f.filename for f in uploaded_files):
        for f in uploaded_files:
            with tempfile.NamedTemporaryFile(suffix=".wav") as tmp:
                f.save(tmp.name)
                waveform, sr = torchaudio.load(tmp.name)
                if sr != TARGET_SR:
                    waveform = F.resample(waveform, orig_freq=sr, new_freq=TARGET_SR)
                melody_tensors.append(waveform)

    if melody_tensors:
        combined = torch.cat(melody_tensors, dim=1)
        key_note = detect_key(combined, TARGET_SR)
        chord_prog = generate_chord_progression(key_note, style, length=4)
        print(f"🎵 Key: {key_note} | Chords: {chord_prog}")
        stitched_melody = harmonize_melodies(melody_tensors, chord_prog)
    else:
        stitched_melody = None

    # Always generate rhythm
    rhythm_audio = generate_rhythm(style, bars=int(duration / 2))

    # Combine melody + rhythm
    if stitched_melody is not None:
        input_melody = [stitched_melody + rhythm_audio]
    else:
        input_melody = [rhythm_audio]

    # Generate music
    final_wav = model.generate([prompt], input_melody=input_melody)

    # Save to temp file and return
    with tempfile.NamedTemporaryFile(suffix=".wav", delete=False) as tmp:
        torchaudio.save(tmp.name, final_wav[0].cpu(), TARGET_SR)
        file_path = tmp.name

    return send_file(file_path, mimetype="audio/wav", as_attachment=True, download_name="generated_music.wav")

@app.route("/")
def index():
    return app.send_static_file("index2.html")

if __name__ == "__main__":
    app.run(debug=True)
