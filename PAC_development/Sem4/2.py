import numpy as np

h = 800
w = 800

matrix = np.random.randint(0 , 256, size=(h, w, 3), dtype='uint8')
print(matrix)

res = len(np.unique(matrix.reshape(-1, 3), axis=0))
print (res)