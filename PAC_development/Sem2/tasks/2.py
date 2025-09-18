str = "It was a beautiful sunny day"

words = str.split(' ')
max_len = 0
for i in range(0, len(words)):
    if (len(words[i]) > max_len):
        max_len = len(words[i])
        n = i

print(words[n])
