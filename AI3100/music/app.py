from flask import Flask, request, send_file
from audiocraft.models import MusicGen
import torchaudio
import tempfile
import os

app = Flask(__name__)

# Load the model once at startup
print("🎵 Loading MusicGen melody model... (this might take a minute)")
model = MusicGen.get_pretrained("facebook/musicgen-melody")
print("✅ Model loaded!")

@app.route("/generate", methods=["POST"])
def generate_music():
    prompt = request.form.get("prompt", "a chill lo-fi beat with piano")
    duration = float(request.form.get("duration", 10))
    melody_file = request.files.get("melody")  # Optional

    print(f"🎶 Generating music for prompt: {prompt} ({duration}s)")

    model.set_generation_params(duration=duration)

    if melody_file:
        # Load the uploaded melody
        melody_wav, sr = torchaudio.load(melody_file)
        # Ensure shape is (batch, samples)
        melody_wav = melody_wav.mean(dim=0, keepdim=True) if melody_wav.dim() > 1 else melody_wav.unsqueeze(0)
        # Generate conditioned on melody
        wav = model.generate_with_chroma(
            descriptions=[prompt],
            melody_wavs=melody_wav,
            sr=sr
        )
    else:
        # Generate without melody
        wav = model.generate([prompt])

    # Save audio temporarily
    with tempfile.NamedTemporaryFile(suffix=".wav", delete=False) as tmp:
        torchaudio.save(tmp.name, wav[0].cpu(), 32000)
        file_path = tmp.name

    return send_file(file_path, mimetype="audio/wav", as_attachment=True, download_name="generated_music.wav")

@app.route("/")
def index():
    return app.send_static_file("index.html")

if __name__ == "__main__":
    app.run(debug=True)
