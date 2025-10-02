import numpy as np

n = 10
matrix = np.random.randint(100, size=(n, 3))

matrix = np.sort(matrix, axis=1)
a = matrix[:, 0]
b = matrix[:, 1]
c = matrix[:, 2]

iftr = a + b > c

print(matrix)
print('\n', matrix[iftr])