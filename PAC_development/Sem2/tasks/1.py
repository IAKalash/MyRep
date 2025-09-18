str = input()
fl = True
n = len(str) - 1
for i in range(0, n // 2 + 2):
    if str[i] != str[n - i]:
        fl = False

if fl: print("Palindrom")
else: print("Not a palindrom")