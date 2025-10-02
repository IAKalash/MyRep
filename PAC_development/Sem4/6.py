import numpy as np

A = np.matrix("1 0 1; 0 1 0; 1 0 1")

print(np.linalg.svd(A))