import numpy as np

class Neuron:
    def __init__(self, input_size):
        self._weights = np.random.randn(input_size + 1)
        
        self._input_x = None
        self._weighted_sum = None
        self._output = None

    def sigmoid(z):
        return 1.0 / (1.0 + np.exp(-z))
    
    def sigmoid_derivative(n):
        return n * (1.0 - n)

    def forward(self, x):
        bias_input = 1.0
        self._input_x = np.insert(x, 0, bias_input)
        
        self._weighted_sum = np.dot(self._input_x, self._weights)
        
        self._output = Neuron.sigmoid(self._weighted_sum)
        
        return self._output

    def backward(self, output_error, learning_rate=0.1):
        derivative_sigmoid = Neuron.sigmoid_derivative(self._output)
        delta = output_error * derivative_sigmoid
        
        gradient_weights = delta * self._input_x
        error_to_previous_layer = delta * self._weights[1:]
        self._weights -= learning_rate * gradient_weights
        
        return error_to_previous_layer
    


class Model:
    def __init__(self, learning_rate=0.1):
        self.neuron1 = Neuron(input_size=2)
        self.neuron2 = Neuron(input_size=2)
        
        self.neuron3 = Neuron(input_size=2)
        
        self.learning_rate = learning_rate

    def forward(self, x):
        h1_output = self.neuron1.forward(x)
        h2_output = self.neuron2.forward(x)
        
        self.hidden_output = np.array([h1_output, h2_output])
        
        output = self.neuron3.forward(self.hidden_output)
        
        return output

    def backward(self, x, err):
        hidden_layer_errors = self.neuron3.backward(err, self.learning_rate)
        
        n1_error = hidden_layer_errors[0]
        self.neuron1.backward(n1_error, self.learning_rate)
        
        n2_error = hidden_layer_errors[1]
        self.neuron2.backward(n2_error, self.learning_rate)



XOR = [
    (np.array([0, 0]), 0),
    (np.array([0, 1]), 1),
    (np.array([1, 0]), 1),
    (np.array([1, 1]), 0)
]

def mse_loss_derivative(y_pred, y_true):
    return y_pred - y_true

LEARNING_RATE = 5
EPOCHS = 5000

model = Model(learning_rate=LEARNING_RATE)

print(f"Обучение:")

for epoch in range(EPOCHS):
    total_loss = 0
    
    np.random.shuffle(XOR)

    for x, label in XOR:
        y = model.forward(x)
        
        err = mse_loss_derivative(y, label)
        
        total_loss += 0.5 * (y - label) ** 2
        
        model.backward(x, err)
        
    if (epoch + 1) % 1000 == 0:
        avg_loss = total_loss / len(XOR)
        print(f"Эпоха {epoch + 1}, Средняя ошибка (MSE): {avg_loss:.6f}")


TEST = [
    (np.array([1, 1]), 1),
    (np.array([0, 1]), 1),
    (np.array([1, 0]), 1),
    (np.array([1, 1]), 0)
]

print()

results = {}
for x, label in TEST:
    prediction = model.forward(x)
    rounded_pred = round(prediction) 
    
    results[f"({x[0]}, {x[1]})"] = f"{rounded_pred}"
    print(f"Вход {x}: Предсказание {prediction:.4f}.")

print('\n', results)