import numpy as np
import matplotlib.pyplot as plt
import torchvision
from sklearn.metrics import accuracy_score, precision_recall_fscore_support
from sklearn.manifold import TSNE

plt.rcParams['figure.figsize'] = 10, 10

transform = torchvision.transforms.Compose([
                    torchvision.transforms.ToTensor(),
                    torchvision.transforms.Normalize((0.5), (0.5))
                                            ])

train_dataset = torchvision.datasets.MNIST(
    root="./MNIST/train", train=True,
    transform=torchvision.transforms.ToTensor(),
    download=False)

test_dataset = torchvision.datasets.MNIST(
    root="./MNIST/test", train=False,
    transform=torchvision.transforms.ToTensor(),
    download=False)

def encode_label(j):
    e = np.zeros((10,1))
    e[j] = 1.0
    return e

def shape_data(data):
    features = [np.reshape(x[0][0].numpy(), (784,1)) for x in data]
    labels = [encode_label(y[1]) for y in data]
    return zip(features, labels)

train = list(shape_data(train_dataset))
test = list(shape_data(test_dataset))

def average_digit(data, digit):
    filtered_data = [x[0] for x in data if np.argmax(x[1]) == digit]
    filtered_array = np.asarray(filtered_data)
    return np.average(filtered_array, axis=0)

avg_digits = {}
Weights = {}
for i in range(10):
    avg_digits[i] = average_digit(train, i)
    Weights[i] = np.transpose(avg_digits[i])

W_matrix = np.vstack([Weights[i] for i in range(10)])

b = {
    0: -70,
    1: -70,
    2: -70,
    3: -70,
    4: -70,
    5: -70,
    6: -70,
    7: -70,
    8: -70,
    9: -70
} 

b_vector = np.array([b[i] for i in range(10)]).reshape(10, 1)

def binary_step(x):
    return 1.0 if x>=0 else 0

def predict(x, W, b):
    norm = np.linalg.norm(W)
    if norm == 0:
        norm = 1
    return binary_step((np.dot(W,x) + b)/ norm)

def get_logits(x, W_matrix, b_vector):
    logits = np.dot(W_matrix, x) + b_vector
    return logits

def unified_model(x, W_matrix, b_vector):
    logits = get_logits(x, W_matrix, b_vector)

    predicted_class_index = np.argmax(logits) 
    output_vector = encode_label(predicted_class_index)
    
    return output_vector

print('Точность Бинарных Классификаторов:')
for target_digit in range(10):
    W = Weights[target_digit]
    
    y_true = np.array([1.0 if np.argmax(x[1]) == target_digit else 0.0 for x in test])
    
    y_pred = []
    for x, y_label in test:
        prediction = predict(x, W, b[target_digit]) 
        y_pred.append(prediction)
        
    y_pred = np.array(y_pred)
    accuracy = accuracy_score(y_true, y_pred)
    
    print(f'Классификатор "{target_digit}" | Точность: {accuracy:.4f}')

print('\n---')

y_true_multi = []
y_pred_multi = []
all_logits = [] 

for x, y_label in test:
    true_class = np.argmax(y_label)
    y_true_multi.append(true_class)

    logits = get_logits(x, W_matrix, b_vector) 
    all_logits.append(logits.flatten())
    
    predicted_class = np.argmax(logits)
    y_pred_multi.append(predicted_class)

y_pred_multi = np.array(y_pred_multi)
all_logits = np.array(all_logits)

precision, recall, f1_score, _ = precision_recall_fscore_support(
    y_true_multi, y_pred_multi, average='macro', zero_division=0)

print(f'Macro Precision: {precision:.4f}')
print(f'Macro Recall:    {recall:.4f}')


X_raw_tsne = [] 
y_raw_tsne = [] 
counts = np.zeros(10)
target_count = 30

for x, y in train:
    digit = np.argmax(y)
    if counts[digit] < target_count:
        X_raw_tsne.append(x.flatten())
        y_raw_tsne.append(digit)
        counts[digit] += 1
    if np.sum(counts) == 10 * target_count:
        break

X_raw_tsne = np.array(X_raw_tsne)
y_raw_tsne = np.array(y_raw_tsne)

tsne_raw = TSNE(n_components=2, random_state=42, perplexity=30)
X_raw_2d = tsne_raw.fit_transform(X_raw_tsne)

plt.figure(figsize=(10, 8))
scatter_raw = plt.scatter(X_raw_2d[:, 0], X_raw_2d[:, 1], c=y_raw_tsne, cmap='Spectral', alpha=0.8)
plt.colorbar(scatter_raw, ticks=range(10), label='Цифра')
plt.title('t-SNE Визуализация Необработанных Векторов')
plt.xlabel('t-SNE Компонента 1')
plt.ylabel('t-SNE Компонента 2')
plt.grid(True)
plt.show()


X_logits_tsne = []

for x_vec in X_raw_tsne:
    x_input = x_vec.reshape(784, 1) 
    logits = get_logits(x_input, W_matrix, b_vector) 
    X_logits_tsne.append(logits.flatten())
    
X_logits_tsne = np.array(X_logits_tsne)

tsne_logits = TSNE(n_components=2, random_state=42, perplexity=30)
X_logits_2d = tsne_logits.fit_transform(X_logits_tsne)


plt.figure(figsize=(10, 8))
scatter_logits = plt.scatter(X_logits_2d[:, 0], X_logits_2d[:, 1], c=y_raw_tsne, cmap='Spectral', alpha=0.8)
plt.colorbar(scatter_logits, ticks=range(10), label='Цифра')
plt.title('t-SNE Визуализация Логитов Модели')
plt.xlabel('t-SNE Компонента 1')
plt.ylabel('t-SNE Компонента 2')
plt.grid(True)
plt.show()