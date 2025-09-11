n = int(input())
print("1")
for i in range(2, n + 1):
    fl = True
    for j in range(2, int(i**0.5) + 1):
        if(i % j == 0):
            fl = False
            break
    if(fl): print(i)