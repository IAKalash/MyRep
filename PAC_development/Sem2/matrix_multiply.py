def read_matrixes(infile):
    f = open(infile)

    m1 = []
    while(True):
        str = f.readline()
        if (str == '\n'):
            break
        else:
            m1.append(list(map(int, str.split(' '))))

    m2 = []
    while(True):
        str = f.readline()
        if (str == ''):
            break
        else:
            m2.append(list(map(int, str.split(' '))))

    f.close()

    return m1, m2

def matrix_multiply(m1, m2):
    m = len(m1)
    n = len(m2[0])
    p = len(m2)
    if (len(m1[0]) != p):
        return 0
    res = [[0 for _ in range(n)] for _ in range(m)]
    for i in range(m):
        for j in range(n):
            for k in range(p):
                res[i][j] += m1[i][k] * m2[k][j]

    return res



def main():
    infile = input()
    outfile = input()

    try:
        m1, m2 = read_matrixes(infile)
    except ValueError as e:
        print(f"Error: ", e)
        return 0

    res = matrix_multiply(m1, m2)

    if (not res):
        print("Wrong matrixes")
        return 0
    
    f = open(outfile, "w")
    for i in res:
        print(*i, file=f)

    f.close()

main()