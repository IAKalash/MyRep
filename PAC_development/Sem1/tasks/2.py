import random

a = random.randint(1, 999999) 
res = 0
for i in range (len(str(a)) - 1, -1, -1):
    res += a // 10**i % 10

print(a, res)