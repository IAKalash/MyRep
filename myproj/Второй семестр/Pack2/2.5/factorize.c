typedef struct Factors {
    int k ; //сколько различных простых в разложении
    int primes [32]; //различные простые в порядке возрастания
    int powers [32]; //в какие степени надо эти простые возводить
} Factors;

void Factorize(int X, Factors *res) {
    int c = 0;

    for (int i = 2; i * i <= X; i += 2) {
        if (X % i == 0) {
            res->primes[c] = i;
            while (X % i == 0) {
                res->powers[c]++;
                X /= i;
            }
            c++;
        }
        if (i == 2) {
            i = 1;
        }
    }

    if (X != 1) {
        res->primes[c] = X;
        res->powers[c] = 1;
        c++;
    }
    res->k = c;
}