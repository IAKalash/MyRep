import numpy as np

sys = np.array([[3, 4, 2], [5, 2, 3], [4, 3, 2]])
nums = np.array([17, 23, 19])
print(sys)

invsys = np.linalg.inv(sys)
print(invsys)

print(invsys @ nums)

print(np.linalg.solve(sys, nums))