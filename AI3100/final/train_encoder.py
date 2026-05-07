import os
import torch
import librosa
from torch import nn, optim
from torch.utils.data import DataLoader, Dataset

# ============================================================
# Dataset that loads WAV files
# ============================================================
class SpeakerDataset(Dataset):
    def __init__(self, wav_dir):
        self.paths = [
            os.path.join(wav_dir, p)
            for p in os.listdir(wav_dir)
            if p.endswith('.wav')
        ]

    def __getitem__(self, idx):
        wav, sr = librosa.load(self.paths[idx], sr=16000)
        return torch.tensor(wav).float()

    def __len__(self):
        return len(self.paths)


# ============================================================
# Mel Spectrogram Function
# ============================================================
def mel_spectrogram(wav):
    mel = librosa.feature.melspectrogram(
        y=wav.numpy(),
        sr=16000,
        n_mels=40
    )
    mel = librosa.power_to_db(mel)  # optional but recommended
    return torch.tensor(mel.T).float()  # shape: [T, 40]


# ============================================================
# Collate Function (Pads variable-length audio/mels)
# ============================================================
def pad_mel_collate(batch):
    mels = [mel_spectrogram(w) for w in batch]  # each: [T, 40]
    max_len = max(m.size(0) for m in mels)

    padded = [
        torch.nn.functional.pad(m, (0, 0, 0, max_len - m.size(0)))
        for m in mels
    ]
    return torch.stack(padded)  # [B, T, 40]


# ============================================================
# Simple LSTM Speaker Encoder
# ============================================================
class SpeakerEncoder(nn.Module):
    def __init__(self):
        super().__init__()
        self.lstm = nn.LSTM(40, 256, batch_first=True)
        self.linear = nn.Linear(256, 256)

    def forward(self, mels):
        out, _ = self.lstm(mels)
        embed = self.linear(out[:, -1, :])
        embed = embed / torch.norm(embed, p=2, dim=1, keepdim=True)
        return embed


# ============================================================
# Training Setup
# ============================================================
dataset = SpeakerDataset("data/wavs")

batch_size = 4
num_epochs = 20
learning_rate = 1e-4

encoder = SpeakerEncoder()
optimizer = optim.Adam(encoder.parameters(), lr=learning_rate)


# ============================================================
# Training Loop
# ============================================================
for epoch in range(num_epochs):
    loader = DataLoader(
        dataset,
        batch_size=batch_size,
        shuffle=True,
        collate_fn=pad_mel_collate
    )

    epoch_loss = 0
    for mel_batch in loader:
        embed = encoder(mel_batch)

        # Placeholder loss — replace with GE2E or triplet loss for real training
        loss = 1 - embed.mean()

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        epoch_loss += loss.item()

    print(f"Epoch {epoch+1}/{num_epochs}  Avg Loss: {epoch_loss/len(loader):.4f}")


# ============================================================
# Save Encoder
# ============================================================
os.makedirs("models/encoder", exist_ok=True)
torch.save(encoder.state_dict(), "models/encoder/encoder.pt")
print("Encoder saved to models/encoder/encoder.pt")
