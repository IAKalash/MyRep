import torch
import torch.nn as nn
import torchvision
from torch.utils.data import DataLoader
import torch.optim as optim

transform = torchvision.transforms.Compose([
        torchvision.transforms.ToTensor(),
        torchvision.transforms.Normalize((0.5), (0.5))
    ])

train_dataset = torchvision.datasets.MNIST(
    root="../Sem10/MNIST/train", train=True,
    transform=torchvision.transforms.ToTensor(),
    download=False)

test_dataset = torchvision.datasets.MNIST(
    root="../Sem10/MNIST/test", train=False,
    transform=torchvision.transforms.ToTensor(),
    download=False)



class Model(nn.Module):
    def __init__(self):
        super().__init__()

        self.conv1 = nn.Conv2d(in_channels=1, out_channels=16, kernel_size=5)
        self.conv2 = nn.Conv2d(in_channels=16, out_channels=32, kernel_size=5)
        self.fc = nn.Linear(512, 10)

        self.pool = nn.MaxPool2d(kernel_size=2)
        self.relu = nn.ReLU()
        self.softmax = nn.LogSoftmax(dim=1)

    def forward(self, x):
        x = self.conv1(x)
        x = self.relu(x)
        x = self.pool(x)

        x = self.conv2(x)
        x = self.relu(x)
        x = self.pool(x)

        x = x.view(x.size(0), -1)

        x = self.fc(x)
        x = self.softmax(x)

        return x
    


train_loader = DataLoader(train_dataset, batch_size=64, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=1000, shuffle=False)

model = Model()
optimizer = optim.Adam(model.parameters(), lr=0.001)
mist_func = nn.NLLLoss()

def train(model, train_loader, optimizer):
    model.train()
    for batch_idx, (data, target) in enumerate(train_loader):
        data, target = data, target
        
        optimizer.zero_grad()
        output = model(data) 
        loss = mist_func(output, target)
        loss.backward()
        optimizer.step()
        
        if batch_idx % 100 == 0:
            print(f'[{batch_idx * len(data)}/{len(train_loader.dataset)}]\tLoss: {loss.item():.6f}')

def test(model, test_loader):
    model.eval()
    test_loss = 0
    correct = 0

    for data, target in test_loader:
        data, target = data, target
        output = model(data)
        test_loss += mist_func(output, target).item()
        pred = output.argmax(dim=1, keepdim=True)
        correct += pred.eq(target.view_as(pred)).sum().item()

    test_loss /= len(test_loader.dataset)
    accuracy = 100 * correct / len(test_loader.dataset)
    print(f'\nTest:\n Loss: {test_loss:.6f}, Accuracy: {correct}/{len(test_loader.dataset)} '
          f'({accuracy:.2f}%)\n')



for epoch in range(1, 4):
    print(f"Train (Epoch {epoch}):")
    train(model, train_loader, optimizer)
    test(model, test_loader)