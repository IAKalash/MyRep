import argparse
import random

parser = argparse.ArgumentParser(
                    prog='bubble_sort.py',
                    description='Bubble sort of a random list of lenght N',
                    epilog='')

parser.add_argument('list_len')
args = parser.parse_args()
list_len = int(args.list_len)

list = []
for i in range (list_len):
    list.append(random.random())

print(list)

for i in range(list_len - 1):
    for j in range(list_len - 1 - i):
        if (list[j] > list[j + 1]):
            list[j], list[j + 1] = list[j + 1], list[j]

print(list)



