# deepfake/generate_me.py
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
# Griffin-Lim vocoder with correct hop_length
# -------------------------------
def mel_to_wav(mel, n_iter=60, sr=22050, n_fft=1024, hop_length=256, fmax=8000):
    mel = mel.cpu().numpy().squeeze()  # [80, T]
    mel = mel.astype(np.float32)
    # Griffin-Lim expects **linear-scale** mel
    wav = librosa.feature.inverse.mel_to_audio(
        mel,
        sr=sr,
        n_fft=n_fft,
        hop_length=hop_length,
        n_iter=n_iter,
        fmax=fmax
    )
    return wav

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

# Pick first wav in training data for speaker embedding
wav_path = "data/wavs/" + os.listdir("data/wavs")[0]
wav, sr = torchaudio.load(wav_path)
if wav.shape[0] > 1:
    wav = wav.mean(dim=0)
wav = wav.squeeze().numpy()
wav = wav / (np.max(np.abs(wav)) + 1e-9)

# Generate mel for embedding
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
    mel_out = synthesizer(text_seq, speaker_emb)

# Convert to waveform
wav_out = mel_to_wav(mel_out[0])

# Save
os.makedirs("generated", exist_ok=True)
out_path = os.path.join("generated", "output.wav")
torchaudio.save(out_path, torch.tensor(wav_out).unsqueeze(0), 22050)
print(f"Generated audio saved to {out_path}")
