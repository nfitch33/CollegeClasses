import os
import torch
import numpy as np
from scipy.io.wavfile import write
import sounddevice as sd
import random

# ----------------------------
# Fix randomness
# ----------------------------
torch.manual_seed(42)
np.random.seed(42)
random.seed(42)

# ----------------------------
# Placeholder models
# ----------------------------
class SpeakerEncoder(torch.nn.Module):
    def __init__(self):
        super().__init__()
        self.lstm = torch.nn.LSTM(40, 256, batch_first=True)
        self.linear = torch.nn.Linear(256, 256)

    def forward(self, mels):
        out, _ = self.lstm(mels)
        embed = self.linear(out[:, -1, :])
        embed = embed / torch.norm(embed, p=2, dim=1, keepdim=True)
        return embed

class Synthesizer(torch.nn.Module):
    def __init__(self):
        super().__init__()
        self.net = torch.nn.Sequential(
            torch.nn.Linear(256, 512),
            torch.nn.ReLU(),
            torch.nn.Linear(512, 80)
        )

    def forward(self, embedding):
        mel = self.net(embedding)
        return mel.unsqueeze(0) if len(mel.shape) == 2 else mel

class Vocoder(torch.nn.Module):
    def __init__(self):
        super().__init__()
        self.net = torch.nn.Sequential(
            torch.nn.Linear(80, 256),
            torch.nn.ReLU(),
            torch.nn.Linear(256, 512),
            torch.nn.ReLU(),
            torch.nn.Linear(512, 1024),
            torch.nn.ReLU(),
            torch.nn.Linear(1024, 22050 // 10)
        )

    def forward(self, mel):
        mel_flat = mel.view(-1, mel.size(-1))
        audio = self.net(mel_flat)
        return audio

# ----------------------------
# Load models
# ----------------------------
def load_models():
    encoder = SpeakerEncoder()
    synth = Synthesizer()
    vocoder = Vocoder()

    encoder_ckpt = "models/encoder/encoder.pt"
    synth_ckpt = "models/synthesizer/synth.pt"
    vocoder_ckpt = "models/vocoder/vocoder.pt"

    if os.path.exists(encoder_ckpt):
        encoder.load_state_dict(torch.load(encoder_ckpt))
    if os.path.exists(synth_ckpt):
        synth.load_state_dict(torch.load(synth_ckpt))
    if os.path.exists(vocoder_ckpt):
        try:
            vocoder.load_state_dict(torch.load(vocoder_ckpt))
        except RuntimeError:
            print("Warning: Vocoder checkpoint incompatible, using random weights.")

    encoder.eval()
    synth.eval()
    vocoder.eval()

    return encoder, synth, vocoder

# ----------------------------
# Text → Mel
# ----------------------------
def text_to_mel(encoder, synth, text):
    # Placeholder: random embedding
    embedding = torch.randn(1, 256)
    mel = synth(embedding)
    return mel

# ----------------------------
# Mel → waveform
# ----------------------------
def mel_to_waveform(vocoder, mel):
    try:
        audio = vocoder(mel)
        audio = audio.detach().cpu().numpy().flatten()
        # normalize
        audio = audio / np.max(np.abs(audio)) * 0.5
        audio = (audio * 32767).astype(np.int16)
    except:
        # fallback: sine wave
        mel_len = mel.size(0) * 50
        t = np.linspace(0, mel_len / 22050, mel_len)
        freq = 220
        audio = 0.1 * np.sin(2 * np.pi * freq * t)
        audio = (audio * 32767).astype(np.int16)
    return audio

# ----------------------------
# Main
# ----------------------------
def main():
    encoder, synth, vocoder = load_models()

    print("Enter sentences (separate by '|'):")
    sentences_input = input().strip()
    if not sentences_input:
        print("No text entered. Exiting.")
        return

    sentences = [s.strip() for s in sentences_input.split('|') if s.strip()]

    full_audio = np.array([], dtype=np.int16)
    for i, sentence in enumerate(sentences):
        print(f"Synthesizing sentence {i+1}/{len(sentences)}: {sentence}")
        mel = text_to_mel(encoder, synth, sentence)
        audio = mel_to_waveform(vocoder, mel)
        full_audio = np.concatenate([full_audio, audio])

    # Play audio immediately
    print("Playing audio...")
    sd.play(full_audio, samplerate=22050)
    sd.wait()

    # Save WAV
    os.makedirs("outputs", exist_ok=True)
    output_path = os.path.join("outputs", "full_output.wav")
    write(output_path, 22050, full_audio)
    print(f"Full speech saved to {output_path}")

if __name__ == "__main__":
    main()
