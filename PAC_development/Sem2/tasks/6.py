file = open('input.txt')
strings = file.readlines()
file.close()

words = 0
symbols = 0

for line in strings:
    symbols += len(line)
    words += len(list(filter(lambda a: a != '', line.split(' '))))

print("Strings:", len(strings), "\nWords:", words, "\nSymbols:", symbols)