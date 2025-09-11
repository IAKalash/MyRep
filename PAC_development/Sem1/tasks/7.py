import os

def indir(dir, pth):
    list = os.listdir(pth)
    print(" ", dir, ":", list)
    for i in list:
        if(os.path.isdir(os.path.join(pth, i))):
            indir(i, os.path.join(pth, i))




dirs = os.listdir("./Imperative Programming")
print(dirs)
for i in dirs:
    if(os.path.isdir(os.path.join("./Imperative Programming", i))):
        indir(i, os.path.join("./Imperative Programming", i))