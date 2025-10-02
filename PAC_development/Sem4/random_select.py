import numpy as np
import argparse

def readfile(path):
    f = open(path)
    strs = f.readline()

    f.close()
    return np.array(strs.split(' '))

def rselect1(path1, path2, chance):
    l1 = readfile(path1)
    l2 = readfile(path2)
    chance = float(chance)

    ind = (np.random.rand(len(l1)) < chance).astype(int)

    return np.choose(ind, choices=np.stack((l1, l2)))


def rselect2(path1, path2, chance):
    l1 = readfile(path1)
    l2 = readfile(path2)
    chance = float(chance)

    mask = np.random.rand(len(l1)) < chance

    return np.where(mask, l1, l2)

def rselect3(path1, path2, chance):
    l1 = readfile(path1).astype(int)
    l2 = readfile(path2).astype(int)
    chance = float(chance)

    mask = np.random.rand(len(l1)) < chance

    l1[mask] = l2[mask]
    return l1

def main():
    parser = argparse.ArgumentParser(
                    prog='random_select.py',
                    description='Shuffles synthetic and real data',
                    epilog='')

    parser.add_argument('path1')
    parser.add_argument('path2')
    parser.add_argument('chance')
    args = parser.parse_args()

    print(readfile(args.path1), readfile(args.path2), '\n')

    print(rselect1(args.path1, args.path2, args.chance))
    print(rselect2(args.path1, args.path2, args.chance))
    print(rselect3(args.path1, args.path2, args.chance))


main()