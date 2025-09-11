import argparse

parser = argparse.ArgumentParser(
                    prog='pascal_triangle.py',
                    description='Builds a pascal triangle of height H',
                    epilog='')

parser.add_argument('height')
args = parser.parse_args()
height = int(args.height)

triangle = []
triangle.append([1])
triangle.append([1, 1])
for i in range(2, height + 1):
    triangle.append([1,1])
    for j in range(1, i):
        triangle[i].insert(j, triangle[i - 1][j - 1] + triangle[i - 1][j])

for i in triangle:
    print(*[f"{x:>4}" for x in i])





