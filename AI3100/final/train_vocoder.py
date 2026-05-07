import os
import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import Dataset, DataLoader
import librosa
import numpy as np
import torch.nn.functional as F

# ============================================================
# Dataset: Generate mel spectrograms if missing
# ============================================================
class VocoderDataset(Dataset):
    def __init__(self, wav_dir, mel_dir, n_mels=80, sr=22050):
        self.wav_dir = wav_dir
        self.mel_dir = mel_dir
        self.n_mels = n_mels
        self.sr = sr

        os.makedirs(mel_dir, exist_ok=True)

        wav_files = [f for f in os.listdir(wav_dir) if f.endswith(".wav")]
        self.files = []

        for wav_file in wav_files:
            wav_path = os.path.join(wav_dir, wav_file)
            mel_path = os.path.join(mel_dir, wav_file.replace(".wav", ".npy"))

            if not os.path.exists(mel_path):
                wav, _ = librosa.load(wav_path, sr=sr)
                mel = librosa.feature.melspectrogram(y=wav, sr=sr, n_mels=n_mels)
                mel = librosa.power_to_db(mel)
                np.save(mel_path, mel.T)

            if os.path.exists(mel_path):
                self.files.append(wav_file)

        if len(self.files) == 0:
            raise ValueError("No valid WAV files found.")

    def __len__(self):
        return len(self.files)

    def __getitem__(self, idx):
        wav_file = self.files[idx]
        wav_path = os.path.join(self.wav_dir, wav_file)
        mel_path = os.path.join(self.mel_dir, wav_file.replace(".wav", ".npy"))

        wav, _ = librosa.load(wav_path, sr=self.sr)
        mel = np.load(mel_path)

        return torch.tensor(mel).float(), torch.tensor(wav).float()

# ============================================================
# Collate function for variable-length sequences
# ============================================================
def pad_vocoder_collate(batch):
    mels = [item[0] for item in batch]
    wavs = [item[1] for item in batch]

    max_mel_len = max(m.size(0) for m in mels)
    max_wav_len = max(w.size(0) for w in wavs)

    padded_mels = [F.pad(m, (0, 0, 0, max_mel_len - m.size(0))) for m in mels]
    padded_wavs = [F.pad(w, (0, max_wav_len - w.size(0))) for w in wavs]

    return torch.stack(padded_mels), torch.stack(padded_wavs)

# ============================================================
# Fully Convolutional Vocoder
# ============================================================
class ConvVocoder(nn.Module):
    def __init__(self, n_mels=80):
        super().__init__()
        self.conv1 = nn.Conv1d(n_mels, 256, kernel_size=5, padding=2)
        self.conv2 = nn.Conv1d(256, 512, kernel_size=5, padding=2)
        self.conv3 = nn.Conv1d(512, 512, kernel_size=5, padding=2)
        self.conv4 = nn.Conv1d(512, 1, kernel_size=5, padding=2)

    def forward(self, mel):
        """
        mel: [B, T, n_mels]
        output: [B, T*hop_length] -> waveform
        """
        x = mel.transpose(1, 2)  # [B, n_mels, T]
        x = torch.relu(self.conv1(x))
        x = torch.relu(self.conv2(x))
        x = torch.relu(self.conv3(x))
        x = self.conv4(x)
        return x.squeeze(1)  # [B, T]

# ============================================================
# Training setup
# ============================================================
wav_dir = "data/wavs"
mel_dir = "data/mels"
batch_size = 4
num_epochs = 20
learning_rate = 1e-4

dataset = VocoderDataset(wav_dir, mel_dir)
loader = DataLoader(dataset, batch_size=batch_size, shuffle=True,
                    collate_fn=pad_vocoder_collate)

vocoder = ConvVocoder()
optimizer = optim.Adam(vocoder.parameters(), lr=learning_rate)
criterion = nn.MSELoss()

# ============================================================
# Training loop
# ============================================================
for epoch in range(num_epochs):
    epoch_loss = 0
    for mel_batch, wav_batch in loader:
        # Forward pass
        output = vocoder(mel_batch)  # [B, T]
        target = wav_batch[:, :output.size(1)]  # truncate to match output

        loss = criterion(output, target)

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        epoch_loss += loss.item()

    print(f"Epoch {epoch+1}/{num_epochs}, Avg Loss: {epoch_loss/len(loader):.4f}")

# ============================================================
# Save vocoder
# ============================================================
os.makedirs("models/vocoder", exist_ok=True)
torch.save(vocoder.state_dict(), "models/vocoder/vocoder.pt")
print("Vocoder saved at models/vocoder/vocoder.pt")
