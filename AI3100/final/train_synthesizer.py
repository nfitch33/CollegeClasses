import os
import torch
import torch.nn as nn
from torch.utils.data import Dataset, DataLoader
import pandas as pd
import librosa
import torch.nn.functional as F

# ============================================================
# Dataset (Loads WAV + Text)
# ============================================================
class TTSDataset(Dataset):
    def __init__(self, metadata_path, wav_dir):
        self.meta = pd.read_csv(metadata_path, sep='|', header=None)
        self.wav_dir = wav_dir

    def __getitem__(self, idx):
        wav_file, text = self.meta.iloc[idx, 0], self.meta.iloc[idx, 1]
        # Replace spaces in filenames to match actual files if needed
        wav_file = wav_file.strip()
        wav_path = os.path.join(self.wav_dir, wav_file)
        wav, _ = librosa.load(wav_path, sr=22050)
        mel = librosa.feature.melspectrogram(y=wav, sr=22050, n_mels=80)
        mel = librosa.power_to_db(mel)
        mel = torch.tensor(mel).transpose(0, 1).float()   # [T, 80]
        return mel, text

    def __len__(self):
        return len(self.meta)


# ============================================================
# Collate Function (Pad variable-length mel spectrograms)
# ============================================================
def pad_mel_collate(batch):
    mels = [item[0] for item in batch]  # shape: [T_i, 80]
    texts = [item[1] for item in batch]

    max_len = max(m.size(0) for m in mels)

    padded_mels = [
        F.pad(m, (0, 0, 0, max_len - m.size(0)))  # pad time dimension
        for m in mels
    ]

    return torch.stack(padded_mels), texts  # [B, T, 80], list of strings


# ============================================================
# Simple Synthesizer Model
# ============================================================
class SimpleSynth(nn.Module):
    def __init__(self):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(256, 512),
            nn.ReLU(),
            nn.Linear(512, 80)
        )

    def forward(self, x):
        return self.net(x)  # output shape: [B, 80]


# ============================================================
# Training Setup
# ============================================================
batch_size = 4
num_epochs = 20
learning_rate = 1e-4

# Paths (adjust if needed)
metadata_path = "data/metadata.csv"
wav_dir = "data/wavs"

dataset = TTSDataset(metadata_path, wav_dir)
loader = DataLoader(dataset, batch_size=batch_size, shuffle=True,
                    collate_fn=pad_mel_collate)

synth = SimpleSynth()
optimizer = torch.optim.Adam(synth.parameters(), lr=learning_rate)
criterion = nn.L1Loss()


# ============================================================
# Training Loop
# ============================================================
for epoch in range(num_epochs):
    epoch_loss = 0

    for mel_batch, _ in loader:
        B, T, M = mel_batch.shape  # [batch, time, 80]

        # Simplified target: average over time dimension
        mel_target = mel_batch.mean(dim=1)  # [B, 80]

        # Dummy input vector (replace with speaker encoder embeddings later)
        inp = torch.randn(B, 256)

        pred = synth(inp)  # [B, 80]

        loss = criterion(pred, mel_target)

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        epoch_loss += loss.item()

    print(f"Epoch {epoch+1}/{num_epochs}  Avg Loss: {epoch_loss/len(loader):.4f}")


# ============================================================
# Save Model
# ============================================================
os.makedirs("models/synthesizer", exist_ok=True)
torch.save(synth.state_dict(), "models/synthesizer/synth.pt")
print("Synthesizer saved at models/synthesizer/synth.pt")
