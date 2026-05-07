import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torch.utils.data import Dataset, DataLoader
import numpy as np
import random
import matplotlib.pyplot as plt

# -------------------------------
# 1. Color Synthetic Dataset
# -------------------------------

class ColorNoisyDataset(Dataset):
    def __init__(self, size=5000):
        self.size = size

    def __len__(self):
        return self.size

    def __getitem__(self, idx):
        # Pick a basic color randomly
        colors = {
            'red': [1,0,0],
            'green': [0,1,0],
            'blue': [0,0,1],
            'yellow': [1,1,0],
            'cyan': [0,1,1],
            'magenta': [1,0,1]
        }
        color_name = random.choice(list(colors.keys()))
        base_color = torch.tensor(colors[color_name], dtype=torch.float32).view(3,1,1)
        img = base_color.repeat(1,32,32)  # 32x32 solid color

        # Apply noise randomly
        choice = random.choice([0, 1])  # 0=clean, 1=noisy
        noise_type = None
        if choice == 1:
            noise_type = random.choice(['gaussian','salt_pepper'])
            if noise_type == 'gaussian':
                img += torch.randn_like(img) * 0.1
                img = torch.clamp(img,0.,1.)
            else:
                c,h,w = img.shape
                num_salt = int(0.05*h*w)
                coords = [np.random.randint(0,i,num_salt) for i in (h,w)]
                img[:,coords[0],coords[1]] = 1.0
                coords = [np.random.randint(0,i,num_salt) for i in (h,w)]
                img[:,coords[0],coords[1]] = 0.0

        return img, choice, noise_type

# -------------------------------
# 2. Visualization Function
# -------------------------------

def show_random_images(dataset, num_images=8):
    indices = np.random.choice(len(dataset), num_images, replace=False)
    plt.figure(figsize=(15,3))
    for i, idx in enumerate(indices):
        img, label, noise_type = dataset[idx]
        img_np = img.permute(1,2,0).numpy()
        plt.subplot(1,num_images,i+1)
        plt.imshow(img_np)
        if label == 0:
            plt.title("Clean")
        else:
            plt.title(f"Noisy\n({noise_type})")
        plt.axis('off')
    plt.show()

# Show some examples
example_dataset = ColorNoisyDataset(size=1000)
show_random_images(example_dataset, num_images=8)

# -------------------------------
# 3. Data Loaders
# -------------------------------

def dataset_for_training(dataset):
    class TrainDataset(Dataset):
        def __init__(self, dataset):
            self.dataset = dataset

        def __len__(self):
            return len(self.dataset)

        def __getitem__(self, idx):
            img, label, _ = self.dataset[idx]
            return img, label

    return TrainDataset(dataset)

train_loader = DataLoader(dataset_for_training(example_dataset), batch_size=64, shuffle=True)
test_loader = DataLoader(dataset_for_training(ColorNoisyDataset(size=1000)), batch_size=64, shuffle=False)

# -------------------------------
# 4. Pooling CNN Model
# -------------------------------

class NoiseDetectorCNN(nn.Module):
    def __init__(self):
        super(NoiseDetectorCNN, self).__init__()
        
        self.conv1 = nn.Conv2d(3, 32, 3, padding=1)
        self.bn1 = nn.BatchNorm2d(32)
        self.pool1 = nn.MaxPool2d(2,2)
        
        self.conv2 = nn.Conv2d(32, 64, 3, padding=1)
        self.bn2 = nn.BatchNorm2d(64)
        self.pool2 = nn.MaxPool2d(2,2)
        
        self.conv3 = nn.Conv2d(64, 128, 3, padding=1)
        self.bn3 = nn.BatchNorm2d(128)
        self.pool3 = nn.MaxPool2d(2,2)
        
        self.fc1 = nn.Linear(128*4*4, 128)
        self.dropout = nn.Dropout(0.5)
        self.fc2 = nn.Linear(128, 1)

    def forward(self, x):
        x = self.pool1(F.relu(self.bn1(self.conv1(x))))
        x = self.pool2(F.relu(self.bn2(self.conv2(x))))
        x = self.pool3(F.relu(self.bn3(self.conv3(x))))
        x = x.view(-1, 128*4*4)
        x = F.relu(self.fc1(x))
        x = self.dropout(x)
        x = torch.sigmoid(self.fc2(x))
        return x

# -------------------------------
# 5. Training Setup
# -------------------------------

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model = NoiseDetectorCNN().to(device)
criterion = nn.BCELoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)
num_epochs = 5

# -------------------------------
# 6. Training Loop
# -------------------------------

for epoch in range(num_epochs):
    model.train()
    running_loss = 0.0
    correct = 0
    total = 0
    
    for images, labels in train_loader:
        images, labels = images.to(device), labels.float().to(device)
        optimizer.zero_grad()
        outputs = model(images).squeeze()
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()
        
        running_loss += loss.item() * images.size(0)
        predicted = (outputs > 0.5).int()
        total += labels.size(0)
        correct += (predicted == labels).sum().item()
    
    epoch_loss = running_loss / len(train_loader.dataset)
    epoch_acc = 100 * correct / total
    print(f"Epoch {epoch+1}/{num_epochs} | Loss: {epoch_loss:.4f} | Accuracy: {epoch_acc:.2f}%")

# -------------------------------
# 7. Test Evaluation
# -------------------------------

model.eval()
correct = 0
total = 0

with torch.no_grad():
    for images, labels in test_loader:
        images, labels = images.to(device), labels.to(device)
        outputs = model(images).squeeze()
        predicted = (outputs > 0.5).int()
        total += labels.size(0)
        correct += (predicted == labels).sum().item()

print(f"Test Accuracy: {100 * correct / total:.2f}%")
