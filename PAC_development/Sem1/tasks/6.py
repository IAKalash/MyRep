print("Впишите начальную сумму и срок через пробел")
x, y = map(int, input().split())
for i in range(1, y + 1):
    x *= 1.1
print(x)