import random
import matplotlib.pyplot as plt
import math
import pseudorandom

# def gen_point():
#     x = random.uniform (0 , 1)
#     y = random.uniform (0 , 1)
#     return(x, y)

def my_gen_point(gen):
    x = next(gen)
    y = next(gen)
    return(x, y)


def main():
    iterations = 10000000
    in_circle = 0

    iters = []
    values = []

    gen = pseudorandom.generator()      #######################

    for i in range(1, iterations + 1):

        # point = gen_point()
        point = my_gen_point(gen)

        distance = (point[0] - 0.5) ** 2 + (point[1] - 0.5) ** 2
        if (distance <= 0.25):
            in_circle += 1

        if (i % 10000 == 100):
            iters.append(i)
            values.append(abs(in_circle / i * 4 - math.pi))

    print("Pi:", in_circle / iterations * 4)   

    plt.figure()
    plt.plot(iters, values, color='red')
    plt.xlabel("Количество точек")
    plt.ylabel("Приближённое значение π")
    plt.grid(True)
    plt.ylim(-0.1, 0.1)
    plt.show()
    
main()