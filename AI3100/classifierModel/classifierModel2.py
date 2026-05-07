import os
import torch
from torch import nn, optim, amp
from torch.utils.data import DataLoader
from torchvision import datasets, transforms
from torchvision.models import resnet18, ResNet18_Weights

# Enable cuDNN autotuner for faster convolutions on fixed-size inputs
torch.backends.cudnn.benchmark = True

# Setup device
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# Dataset directories
data_dir = "./FishImgDataset"
train_dir = os.path.join(data_dir, "train")
val_dir = os.path.join(data_dir, "val")
test_dir = os.path.join(data_dir, "test")

# Check for existence of dataset folders
assert os.path.exists(train_dir), f"Train directory not found: {train_dir}"
assert os.path.exists(val_dir), f"Val directory not found: {val_dir}"
assert os.path.exists(test_dir), f"Test directory not found: {test_dir}"

# Data transforms
train_transforms = transforms.Compose([
    transforms.RandomResizedCrop(224),
    transforms.RandomHorizontalFlip(),
    transforms.ToTensor(),
    transforms.Normalize([0.485, 0.456, 0.406],
                         [0.229, 0.224, 0.225])
])

val_test_transforms = transforms.Compose([
    transforms.Resize(256),
    transforms.CenterCrop(224),
    transforms.ToTensor(),
    transforms.Normalize([0.485, 0.456, 0.406],
                         [0.229, 0.224, 0.225])
])

# Load datasets
train_dataset = datasets.ImageFolder(train_dir, transform=train_transforms)
val_dataset = datasets.ImageFolder(val_dir, transform=val_test_transforms)
test_dataset = datasets.ImageFolder(test_dir, transform=val_test_transforms)

# Data loaders
batch_size = 32
train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True, num_workers=4, pin_memory=True)
val_loader = DataLoader(val_dataset, batch_size=batch_size, num_workers=4, pin_memory=True)
test_loader = DataLoader(test_dataset, batch_size=batch_size, num_workers=4, pin_memory=True)

# Number of classes
num_classes = len(train_dataset.classes)
print(f"Number of fish classes: {num_classes}")

# Evaluate model
def evaluate_model(model, criterion, data_loader):
    model.eval()
    running_loss = 0.0
    running_corrects = 0

    with torch.no_grad():
        for inputs, labels in data_loader:
            inputs, labels = inputs.to(device, non_blocking=True), labels.to(device, non_blocking=True)
            outputs = model(inputs)
            _, preds = torch.max(outputs, 1)
            loss = criterion(outputs, labels)
            running_loss += loss.item() * inputs.size(0)
            running_corrects += torch.sum(preds == labels.data)

    loss = running_loss / len(data_loader.dataset)
    acc = running_corrects.double() / len(data_loader.dataset)
    return loss, acc

# Save checkpoint
def save_checkpoint(model, optimizer, epoch, filepath, class_to_idx):
    torch.save({
        'model_state_dict': model.state_dict(),
        'optimizer_state_dict': optimizer.state_dict(),
        'epoch': epoch,
        'class_to_idx': class_to_idx
    }, filepath)
    print(f"[Checkpoint] Epoch {epoch} saved to '{filepath}'")

# Load checkpoint
def load_checkpoint(filepath, num_classes):
    weights = ResNet18_Weights.DEFAULT
    model = resnet18(weights=weights)
    model.fc = nn.Linear(model.fc.in_features, num_classes)
    model = model.to(device)

    optimizer = optim.Adam(model.parameters(), lr=0.001)

    checkpoint = torch.load(filepath, map_location=device)
    model.load_state_dict(checkpoint['model_state_dict'])
    optimizer.load_state_dict(checkpoint['optimizer_state_dict'])

    # Move optimizer state to GPU
    for state in optimizer.state.values():
        for k, v in state.items():
            if isinstance(v, torch.Tensor):
                state[k] = v.to(device)

    start_epoch = checkpoint.get('epoch', 0)
    class_to_idx = checkpoint.get('class_to_idx', None)

    return model, optimizer, start_epoch, class_to_idx

# Training loop with AMP and checkpointing
def train_model(model, criterion, optimizer, train_loader, val_loader, start_epoch, num_epochs, checkpoint_path, class_to_idx):
    scaler = amp.GradScaler()

    for epoch in range(start_epoch, start_epoch + num_epochs):
        model.train()
        running_loss = 0.0
        running_corrects = 0

        for inputs, labels in train_loader:
            inputs, labels = inputs.to(device, non_blocking=True), labels.to(device, non_blocking=True)
            optimizer.zero_grad()

            with amp.autocast(device_type="cuda"):  # <-- Fixed line
                outputs = model(inputs)
                _, preds = torch.max(outputs, 1)
                loss = criterion(outputs, labels)

            scaler.scale(loss).backward()
            scaler.step(optimizer)
            scaler.update()

            running_loss += loss.item() * inputs.size(0)
            running_corrects += torch.sum(preds == labels.data)

        epoch_loss = running_loss / len(train_loader.dataset)
        epoch_acc = running_corrects.double() / len(train_loader.dataset)

        val_loss, val_acc = evaluate_model(model, criterion, val_loader)

        print(f"\nEpoch {epoch + 1}/{start_epoch + num_epochs}")
        print(f"Train Loss: {epoch_loss:.4f} | Acc: {epoch_acc:.4f}")
        print(f"Val   Loss: {val_loss:.4f} | Acc: {val_acc:.4f}")

        # Save checkpoint after each epoch
        save_checkpoint(model, optimizer, epoch + 1, checkpoint_path, class_to_idx)

    return model, optimizer, epoch + 1

# Test the model
def test_model(model, test_loader, criterion):
    loss, acc = evaluate_model(model, criterion, test_loader)
    print(f"\n[TEST RESULTS] Loss: {loss:.4f} | Accuracy: {acc:.4f}")

# Main
if __name__ == "__main__":
    model_path = "fish_classifier2.pth"
    criterion = nn.CrossEntropyLoss()
    epochs_to_train = 5

    if os.path.exists(model_path):
        print("[INFO] Loading checkpoint...")
        model, optimizer, start_epoch, class_to_idx = load_checkpoint(model_path, num_classes)
    else:
        print("[INFO] No checkpoint found. Initializing new model...")
        weights = ResNet18_Weights.DEFAULT
        model = resnet18(weights=weights)
        model.fc = nn.Linear(model.fc.in_features, num_classes)
        model = model.to(device)

        optimizer = optim.Adam(model.parameters(), lr=0.001)
        start_epoch = 0
        class_to_idx = train_dataset.class_to_idx

    model, optimizer, final_epoch = train_model(
        model, criterion, optimizer,
        train_loader, val_loader,
        start_epoch=start_epoch,
        num_epochs=epochs_to_train,
        checkpoint_path=model_path,
        class_to_idx=class_to_idx
    )

    test_model(model, test_loader, criterion)
