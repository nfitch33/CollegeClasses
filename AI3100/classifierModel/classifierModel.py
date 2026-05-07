import os
import torch
from torch import nn, optim
from torch.utils.data import DataLoader
from torchvision import datasets, transforms
from torchvision.models import resnet18, ResNet18_Weights

# Device setup
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# Dataset paths
data_dir = "./FishImgDataset"
train_dir = os.path.join(data_dir, "train")
val_dir = os.path.join(data_dir, "val")
test_dir = os.path.join(data_dir, "test")

# Check dataset folders
assert os.path.exists(train_dir), f"Train directory not found: {train_dir}"
assert os.path.exists(val_dir), f"Val directory not found: {val_dir}"
assert os.path.exists(test_dir), f"Test directory not found: {test_dir}"

# Transforms
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

# Datasets and loaders
train_dataset = datasets.ImageFolder(train_dir, transform=train_transforms)
val_dataset = datasets.ImageFolder(val_dir, transform=val_test_transforms)
test_dataset = datasets.ImageFolder(test_dir, transform=val_test_transforms)

train_loader = DataLoader(train_dataset, batch_size=16, shuffle=True)
val_loader = DataLoader(val_dataset, batch_size=16)
test_loader = DataLoader(test_dataset, batch_size=16)

# Class count
num_classes = len(train_dataset.classes)
print(f"Number of fish classes: {num_classes}")

# Evaluation function
def evaluate_model(model, criterion, data_loader):
    model.eval()
    running_loss = 0.0
    running_corrects = 0

    with torch.no_grad():
        for inputs, labels in data_loader:
            inputs, labels = inputs.to(device), labels.to(device)
            outputs = model(inputs)
            _, preds = torch.max(outputs, 1)
            loss = criterion(outputs, labels)
            running_loss += loss.item() * inputs.size(0)
            running_corrects += torch.sum(preds == labels.data)

    loss = running_loss / len(data_loader.dataset)
    acc = running_corrects.double() / len(data_loader.dataset)
    return loss, acc

# Training function
def train_model(model, criterion, optimizer, train_loader, val_loader, start_epoch, num_epochs):
    for epoch in range(start_epoch, start_epoch + num_epochs):
        model.train()
        running_loss = 0.0
        running_corrects = 0

        for inputs, labels in train_loader:
            inputs, labels = inputs.to(device), labels.to(device)

            optimizer.zero_grad()
            outputs = model(inputs)
            _, preds = torch.max(outputs, 1)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()

            running_loss += loss.item() * inputs.size(0)
            running_corrects += torch.sum(preds == labels.data)

        epoch_loss = running_loss / len(train_loader.dataset)
        epoch_acc = running_corrects.double() / len(train_loader.dataset)
        val_loss, val_acc = evaluate_model(model, criterion, val_loader)

        print(f"Epoch {epoch+1}")
        print(f"Train Loss: {epoch_loss:.4f} Acc: {epoch_acc:.4f}")
        print(f"Val   Loss: {val_loss:.4f} Acc: {val_acc:.4f}\n")

    return model, optimizer, epoch + 1  # Return updated state

# Test function
def test_model(model, test_loader, criterion):
    loss, acc = evaluate_model(model, criterion, test_loader)
    print(f"Test Loss: {loss:.4f} Acc: {acc:.4f}")

# Save model function
def save_checkpoint(model, optimizer, epoch, filepath, class_to_idx):
    torch.save({
        'model_state_dict': model.state_dict(),
        'optimizer_state_dict': optimizer.state_dict(),
        'epoch': epoch,
        'class_to_idx': class_to_idx
    }, filepath)
    print(f"Model saved to '{filepath}'")

# Load model function
def load_checkpoint(filepath, num_classes):
    weights = ResNet18_Weights.DEFAULT
    model = resnet18(weights=weights)
    model.fc = nn.Linear(model.fc.in_features, num_classes)
    model = model.to(device)

    optimizer = optim.Adam(model.parameters(), lr=0.001)

    checkpoint = torch.load(filepath, map_location=device)
    model.load_state_dict(checkpoint['model_state_dict'])
    optimizer.load_state_dict(checkpoint['optimizer_state_dict'])

    # Move optimizer tensors to correct device
    for state in optimizer.state.values():
        for k, v in state.items():
            if isinstance(v, torch.Tensor):
                state[k] = v.to(device)

    start_epoch = checkpoint.get('epoch', 0)
    class_to_idx = checkpoint.get('class_to_idx', None)

    return model, optimizer, start_epoch, class_to_idx

# Main block
if __name__ == "__main__":
    model_path = "fish_classifier.pth"
    criterion = nn.CrossEntropyLoss()
    epochs_to_train = 5  # Train for x more epochs each time

    if os.path.exists(model_path):
        print("Loading existing model...")
        model, optimizer, start_epoch, class_to_idx = load_checkpoint(model_path, num_classes)
    else:
        print("No saved model found. Initializing new model...")
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
        num_epochs=epochs_to_train
    )

    test_model(model, test_loader, criterion)

    save_checkpoint(model, optimizer, final_epoch, model_path, class_to_idx)
