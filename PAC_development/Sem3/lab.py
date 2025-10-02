class Worker:
    def __init__(self):
        self.salary = 0

    def take_salary(self, num):
        self.salary += int(num)

    def read_matrixes(self, filename1, filename2):
        f1 = open(filename1)
        f2 = open(filename2)

        m1 = []
        m2 = []

        while(True):
            str1 = f1.readline()
            str2 = f2.readline()
            if (str1 == '' and str2 == ''):
                break
            else:
                m1.append(list(map(int, str1.split(' '))))
                m2.append(list(map(int, str2.split(' '))))

        f1.close()
        f2.close()

        return m1,m2

class Pupa(Worker):
    def __init__(self):
        super().__init__()

    def do_work(self, filename1, filename2):
        m1, m2 = super().read_matrixes(filename1, filename2)

        m = len(m1)
        n = len(m1[0])
        res = [[0 for _ in range(n)] for _ in range(m)]

        for i in range(m):
            for j in range(n):
                res[i][j] = m1[i][j] + m2[i][j]

        return res

        

class Lupa(Worker):
    def __init__(self):
        super().__init__()

    def do_work(self, filename1, filename2):
        m1, m2 = super().read_matrixes(filename1, filename2)

        m = len(m1)
        n = len(m1[0])
        res = [[0 for _ in range(n)] for _ in range(m)]

        for i in range(m):
            for j in range(n):
                res[i][j] = m1[i][j] - m2[i][j]

        return res

class Accountant:
    def __init__(self):
        pass

    def give_salary(self, worker):
        if isinstance(worker, Worker):
            worker.take_salary(100)
            return True
        else:
            print("Not a worker")
            return False


pupa = Pupa()
lupa = Lupa()

acc = Accountant()

res1 = pupa.do_work('./m1.txt', './m2.txt')
res2 = lupa.do_work('./m1.txt', './m2.txt')

for i in range(len(res1)):
    print(*res1[i])

print()

for i in range(len(res2)):
    print(*res2[i])

acc.give_salary(pupa)
acc.give_salary(pupa)

acc.give_salary(lupa)

print()
print(lupa.salary)
print(pupa.salary)