import numpy as np

a = np.random.randint(2, 5, size=100)
print (a)

unq, freq = np.unique(a, return_counts=True)
print(unq, freq)

sortnums = unq[np.argsort(freq)[::-1]]
sortfreq = np.sort(freq)[::-1]

print(sortnums, sortfreq)

for i in range(len(sortnums)):
    print(*([sortnums[i]] * sortfreq[i]))