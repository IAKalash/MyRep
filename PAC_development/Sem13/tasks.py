import torch
import torch.nn as nn

# class SimpleModel(nn.Module):
#     def __init__(self, in_ch, out_ch):
#         """Регистрация блоков"""
#         super().__init__()
#         self.fci = nn.Linear(in_ch, 32)  # Полносвязный слой 1
#         self.fc2 = nn.Linear(32, out_ch, bias=False)  # Полносвязный слой 2
#         self.relu = nn.ReLU()  # Функция активации
        
#     def forward(self, x):
#         """Прямой проход"""
#         h = self.fc1(x)
#         h = self.relu(h)
#         h = self.fc2(h)
#         y = self.relu(h)
#         return y

in_ch = 64
out_ch = 10

model = nn.Sequential(
    nn.Linear(in_ch, 32),
    nn.ReLU(),
    nn.Linear(32, out_ch, bias=False),
    nn.ReLU()
)

# x = torch.rand(4, 64)
# y_pred = model(x)

# print(y_pred)



class Model2 (nn.Module):
    def __init__(self):
        super().__init__()
        self.fc1 = nn.Linear(256, 64)
        self.fc2 = nn.Linear(64, 16)
        self.fc3 = nn.Linear(16, 4)

        self.relu = nn.ReLU()
        self.tanh = nn.Tanh()
        self.softmax = nn.Softmax(dim=1)
        
    def forward(self, x):
        x = self.fc1(x)
        x = self.relu(x)
        x = self.fc2(x)
        x = self.tanh(x)
        x = self.fc3(x)
        x = self.softmax(x)
        return x
    
# model2 = Model2()

# test_input = torch.randn(5, 256)
# res = model2(test_input)
# print(res)



class Model3(nn.Module):
    def __init__(self):
        super().__init__()
        
        self.conv1 = nn.Conv2d(in_channels=3, out_channels=8, kernel_size=2, stride=1, padding=0)
        self.conv2 = nn.Conv2d(in_channels=8, out_channels=16, kernel_size=2, stride=1, padding=0)

        self.pool = nn.MaxPool2d(kernel_size=2, stride=2)
        self.relu = nn.ReLU()

    def forward(self, x):
        x = self.conv1(x)
        x = self.relu(x)
        x = self.pool(x)
        x = self.conv2(x)
        x = self.relu(x)
        x = self.pool(x)

        return x
    

# model3 = Model3()

# test_input = torch.randn(4, 3, 19, 19)
# res = model3(test_input)
# print(res.shape)



class CombinedModel(nn.Module):
    def __init__(self):
        super().__init__()

        self.conv1 = nn.Conv2d(in_channels=3, out_channels=8, kernel_size=2, stride=1, padding=0)
        self.conv2 = nn.Conv2d(in_channels=8, out_channels=16, kernel_size=2, stride=1, padding=0)

        self.pool = nn.MaxPool2d(kernel_size=2, stride=2)
        self.relu = nn.ReLU()


        self.fc1 = nn.Linear(256, 64)
        self.fc2 = nn.Linear(64, 16)
        self.fc3 = nn.Linear(16, 4)

        self.relu = nn.ReLU()
        self.tanh = nn.Tanh()
        self.softmax = nn.Softmax(dim=1)

    def forward(self, x):
        x = self.conv1(x)
        x = self.relu(x)
        x = self.pool(x)
        x = self.conv2(x)
        x = self.relu(x)
        x = self.pool(x)

        x = x.view(x.size(0), -1)

        x = self.fc1(x)
        x = self.relu(x)
        x = self.fc2(x)
        x = self.tanh(x)
        x = self.fc3(x)
        x = self.softmax(x)

        return x
    
model4 = CombinedModel()
test_input = torch.randn(4, 3, 19, 19)
res = model4(test_input)
print(res.shape)