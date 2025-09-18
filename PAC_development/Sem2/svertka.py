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

def convolution(m1, m2):
    h1, h2 = len(m1), len(m2)
    w1, w2 = len(m1[0]), len(m2[0])
    
    h = h1 - h2 + 1
    w = w1 - w2 + 1
    
    res = [[0 for _ in range(w)] for _ in range(h)]
    
    for i in range(h):
        for j in range(w):
            sum_val = 0
            for v in range(h2):
                for u in range(w2):
                    sum_val += m1[i + v][j + u] * m2[v][u]
            res[i][j] = sum_val
            
    return res

def main():
    infile = input()
    outfile = input()

    try:
        m1, m2 = read_matrixes(infile)
    except ValueError as e:
        print(f"Error: ", e)
        return 0

    res = convolution(m1, m2)

    f = open(outfile, "w")
    for i in res:
        print(*i, file=f)

    f.close()

main()