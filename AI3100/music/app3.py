from flask import Flask, request, send_file
from audiocraft.models import MusicGen
import torchaudio
import torch
import tempfile
import os
import json
from dotenv import load_dotenv

# --- Load environment variables ---
load_dotenv()
HUGGINGFACE_HUB_TOKEN = os.environ.get("HUGGINGFACE_HUB_TOKEN")
if not HUGGINGFACE_HUB_TOKEN:
    raise RuntimeError("HUGGINGFACE_HUB_TOKEN environment variable not set!")

app = Flask(__name__)

# --- Model Loading ---
print("🎵 Loading MusicGen model...")
# Use small model for prompt-only generation
model = MusicGen.get_pretrained("facebook/musicgen-small")
print("✅ Model loaded!")

TARGET_SR = 32000

# --- Helper to load DALI lyrics ---
def load_dali_lyrics(dali_annotation_path):
    """ Load lyrics text from DALI annotation JSON """
    with open(dali_annotation_path, 'r', encoding='utf-8') as f:
        ann = json.load(f)
    words = ann['annotations']['annot']['words']
    lyrics_text = " ".join(w['text'] for w in words)
    return lyrics_text

# --- Flask Routes ---
@app.route("/generate", methods=["POST"])
def generate_music():
    try:
        prompt = request.form.get("prompt", "a chill lo-fi beat with piano")
        duration = float(request.form.get("duration", 10))
        dali_ann_path = request.form.get("dali_annotation_path", None)

        # Append DALI lyrics if provided
        if dali_ann_path:
            lyrics = load_dali_lyrics(dali_ann_path)
            prompt += " | Lyrics: " + lyrics

        print(f"🎶 Generating music with prompt: {prompt} ({duration}s)")
        model.set_generation_params(duration=duration)

        # Check if any melody files uploaded
        uploaded_files = request.files.getlist("melodies")
        melody_tensors = []

        for f in uploaded_files:
            with tempfile.NamedTemporaryFile(suffix=".wav") as tmp:
                f.save(tmp.name)
                waveform, sr = torchaudio.load(tmp.name)
                if sr != TARGET_SR:
                    waveform = torchaudio.functional.resample(waveform, orig_freq=sr, new_freq=TARGET_SR)
                melody_tensors.append(waveform)

        # If no melody uploaded, generate prompt-only music
        if melody_tensors:
            # Concatenate multiple melodies if provided
            combined_melody = torch.cat(melody_tensors, dim=1)
            # Ensure batch dimension
            combined_melody = combined_melody.unsqueeze(0)
            final_wav = model.generate([prompt], melody=[combined_melody])
        else:
            final_wav = model.generate([prompt])

        # Save generated WAV to temp file
        with tempfile.NamedTemporaryFile(suffix=".wav", delete=False) as tmp:
            torchaudio.save(tmp.name, final_wav[0].cpu(), TARGET_SR)
            file_path = tmp.name

        return send_file(file_path, mimetype="audio/wav", as_attachment=True, download_name="generated_music.wav")

    except Exception as e:
        print("❌ Error during generation:", e)
        return str(e), 500

@app.route("/")
def index():
    return app.send_static_file("index3.html")

if __name__ == "__main__":
    app.run(debug=True)
