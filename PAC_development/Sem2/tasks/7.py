def fun_iter(st, val):
    yield st
    n = st
    while True:
        n *= val
        yield n

it = fun_iter(2, 2)

for _ in range(10):
    print(next(it))