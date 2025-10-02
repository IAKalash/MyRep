import numpy as np

def aver(arr, win_size):
    cumsum = np.cumsum(np.insert(arr, 0, 0))
    res = (cumsum[win_size:] - cumsum[:-win_size]) / win_size
    return res


w_size = 4
a = np.random.randint(100, size=20)
print(a)
print(aver(a, w_size))