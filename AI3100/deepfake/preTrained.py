# deepfake/generate_me_waveglow_local.py

import torch
import torch.nn as nn
import torchaudio
import librosa
import numpy as np
import os

# -------------------------------
# Speaker Encoder
# -------------------------------
class SpeakerEncoder(nn.Module):
    def __init__(self, embedding_size=128):
        super().__init__()
        self.conv = nn.Sequential(
            nn.Conv1d(80, 256, 5, padding=2), nn.ReLU(),
            nn.Conv1d(256, 256, 5, padding=2), nn.ReLU()
        )
        self.gru = nn.GRU(256, 256, batch_first=True)
        self.fc = nn.Linear(256, embedding_size)

    def forward(self, mel):
        x = self.conv(mel)
        x = x.transpose(1, 2)
        _, h = self.gru(x)
        emb = self.fc(h[-1])
        emb = emb / emb.norm(dim=-1, keepdim=True)
        return emb

# -------------------------------
# Synthesizer
# -------------------------------
class Synthesizer(nn.Module):
    def __init__(self, vocab_size=50, embed_dim=256, mel_dim=80):
        super().__init__()
        self.text_embed = nn.Embedding(vocab_size, embed_dim)
        self.lstm = nn.LSTM(embed_dim + 128, 512, batch_first=True)
        self.fc = nn.Linear(512, mel_dim)

    def forward(self, text_seq, speaker_emb):
        x = self.text_embed(text_seq)
        speaker_emb = speaker_emb.unsqueeze(1).expand(-1, x.size(1), -1)
        x = torch.cat([x, speaker_emb], dim=-1)
        mel_seq = self.lstm(x)[0]
        mel_seq = self.fc(mel_seq)
        mel_seq = mel_seq.transpose(1, 2)
        return mel_seq

# -------------------------------
# Text preprocessing
# -------------------------------
def text_to_sequence(text):
    return torch.tensor([ord(c) % 50 for c in text], dtype=torch.long).unsqueeze(0)

# -------------------------------
# Load local WaveGlow
# -------------------------------
def load_waveglow_local(path, device):
    checkpoint = torch.load(path, map_location=device)
    if 'model' in checkpoint:
        waveglow = checkpoint['model']
    else:
        waveglow = checkpoint
    waveglow.to(device).eval()
    # Necessary fix for Conv layers
    for m in waveglow.modules():
        if 'Conv' in str(type(m)):
            setattr(m, 'padding_mode', 'zeros')
    return waveglow

# -------------------------------
# Main generation
# -------------------------------
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# Load models
encoder = SpeakerEncoder().to(device)
synthesizer = Synthesizer(vocab_size=50).to(device)

encoder.load_state_dict(torch.load("models/encoder_finetuned.pth", map_location=device))
synthesizer.load_state_dict(torch.load("models/synthesizer_finetuned.pth", map_location=device))
encoder.eval()
synthesizer.eval()

# Load local WaveGlow
waveglow_path = "models/waveglow_256channels.pt"  # <- put your downloaded file here
vocoder = load_waveglow_local(waveglow_path, device)

# Pick first wav in training data for speaker embedding
wav_path = "data/wavs/" + os.listdir("data/wavs")[0]
wav, sr = torchaudio.load(wav_path)
if wav.shape[0] > 1:
    wav = wav.mean(dim=0)
wav = wav.squeeze().numpy()
wav = wav / (np.max(np.abs(wav)) + 1e-9)

mel = librosa.feature.melspectrogram(
    y=wav,
    sr=sr,
    n_mels=80,
    fmax=8000,
    hop_length=256
)
mel_tensor = torch.tensor(mel, dtype=torch.float32).unsqueeze(0).to(device)
speaker_emb = encoder(mel_tensor)

# Input text
text = input("Enter text to synthesize: ")
text_seq = text_to_sequence(text).to(device)

# Generate mel
with torch.no_grad():
    mel_out = synthesizer(text_seq, speaker_emb)  # [1, 80, T]

# WaveGlow expects [1, T, 80]
mel_for_voc = mel_out.transpose(1, 2).unsqueeze(0).to(device)

# Generate audio
with torch.no_grad():
    audio = vocoder.infer(mel_for_voc)

# Save
os.makedirs("generated", exist_ok=True)
out_path = os.path.join("generated", "output_waveglow.wav")
torchaudio.save(out_path, audio.cpu(), 22050)
print(f"Generated audio saved to {out_path}")
