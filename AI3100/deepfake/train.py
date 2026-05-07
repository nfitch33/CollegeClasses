# deepfake/train.py
import torch
import torch.nn as nn
import torchaudio
import librosa
import numpy as np
import os
from torch.utils.data import Dataset, DataLoader

# -------------------------------
# Dataset for voice cloning
# -------------------------------
class VoiceDataset(Dataset):
    def __init__(self, wav_folder, transcript_file):
        self.data = []
        with open(transcript_file, 'r') as f:
            for line in f:
                fname, text = line.strip().split('|')
                self.data.append((os.path.join(wav_folder, fname), text))

    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        wav_path, text = self.data[idx]
        wav, sr = torchaudio.load(wav_path)
        if wav.shape[0] > 1:
            wav = wav.mean(dim=0)  # stereo → mono
        wav = wav.squeeze().numpy()
        wav = wav / (np.max(np.abs(wav)) + 1e-9)

        # Mel spectrogram: shape [n_mels, n_frames]
        mel = librosa.feature.melspectrogram(y=wav, sr=sr, n_mels=80, fmax=8000)
        mel = torch.tensor(mel, dtype=torch.float32)  # [80, frames]

        # Text sequence (simple char->int mapping)
        text_seq = torch.tensor([ord(c) % 50 for c in text], dtype=torch.long)
        return mel, text_seq

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

    def forward(self, mel):  # mel: [batch, 80, seq_len]
        x = self.conv(mel)           # [batch, 256, seq_len]
        x = x.transpose(1, 2)        # [batch, seq_len, 256]
        _, h = self.gru(x)           # h: [1, batch, 256]
        emb = self.fc(h[-1])         # [batch, embedding_size]
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
        """
        text_seq: [batch, seq_len]
        speaker_emb: [batch, 128]
        returns: [batch, mel_dim, seq_len]
        """
        x = self.text_embed(text_seq)                   # [batch, seq_len, embed_dim]
        speaker_emb = speaker_emb.unsqueeze(1).expand(-1, x.size(1), -1)  # [batch, seq_len, 128]
        x = torch.cat([x, speaker_emb], dim=-1)        # [batch, seq_len, embed+128]
        mel_seq = self.lstm(x)[0]                      # [batch, seq_len, 512]
        mel_seq = self.fc(mel_seq)                     # [batch, seq_len, mel_dim]
        mel_seq = mel_seq.transpose(1, 2)              # [batch, mel_dim, seq_len]
        return mel_seq

# -------------------------------
# Training loop
# -------------------------------
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

dataset = VoiceDataset("data/wavs", "data/transcripts.txt")
loader = DataLoader(dataset, batch_size=1, shuffle=True)

encoder = SpeakerEncoder().to(device)
synthesizer = Synthesizer().to(device)

optimizer = torch.optim.Adam(list(encoder.parameters()) + list(synthesizer.parameters()), lr=1e-3)
criterion = nn.MSELoss()

print("Starting fine-tuning...")
for epoch in range(50):
    total_loss = 0
    for mel, text_seq in loader:
        mel = mel.to(device)           # [80, seq_len] or [batch, 80, seq_len]
        text_seq = text_seq.to(device) # [seq_len] or [batch, seq_len]

        # Ensure batch dimension
        if mel.dim() == 2:
            mel = mel.unsqueeze(0)      # [1, 80, seq_len]
        if text_seq.dim() == 1:
            text_seq = text_seq.unsqueeze(0)  # [1, seq_len]

        optimizer.zero_grad()
        emb = encoder(mel)              # [batch, 128]
        mel_out = synthesizer(text_seq, emb)  # [batch, 80, seq_len_out]

        # Align time dimension
        min_frames = min(mel_out.shape[2], mel.shape[2])
        loss = criterion(mel_out[:, :, :min_frames], mel[:, :, :min_frames])

        loss.backward()
        optimizer.step()
        total_loss += loss.item()

    print(f"Epoch {epoch+1}: loss={total_loss/len(loader):.6f}")

os.makedirs("models", exist_ok=True)
torch.save(encoder.state_dict(), "models/encoder_finetuned.pth")
torch.save(synthesizer.state_dict(), "models/synthesizer_finetuned.pth")
print("Fine-tuning complete! Models saved in 'models/'")
