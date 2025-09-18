import random

list = [random.randint(0, 100000) for i in range(0,10)]
print (list)

odd, even = 0, 0

for i in list:
    if i % 2 == 0:
        even += 1
    else:
        odd += 1
    
print("Odd:", odd, "\nEven:", even)