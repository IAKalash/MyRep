import random
import struct

# Генерация случайного массива
N = 100
array = [random.randint(-100, 100) for _ in range(N)]

# Запись в бинарный файл input.bin
with open("input.bin", "wb") as f:
    f.write(struct.pack('i', N))
    for num in array:
        f.write(struct.pack('i', num))

# Сортировка массива для проверки
sorted_array = sorted(array)

# Запись в бинарный файл output.bin
with open("output.bin", "wb") as f:
    for num in sorted_array:
        f.write(struct.pack('i', num))
