import time

def generator(a=6364136223846793005, b=1442695040888963407, m=2**64, seed=int(time.time_ns())):
    res = seed
    while True:
        res = (a * res + b) % m
        yield res / m

def main():

    it = generator()

    for _ in range(10):
        print(next(it))
if __name__ == "__main__":
    main()