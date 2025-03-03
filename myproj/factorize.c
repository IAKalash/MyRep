typedef struct Factors {
    int k ; //сколько различных простых в разложении
    int primes [32]; //различные простые в порядке возрастания
    int powers [32]; //в какие степени надо эти простые возводить
} Factors;

void Factorize ( int X , Factors * res ) {
    for (int i = 2; i * i < )
    


    for (int i = 2; i * i <= n; i++) {
        fl = 1;
        for (int d = 2; d < i; d++) {
            if (i % d == 0) {
                fl = 0;
                break;
            }
        }
        if (fl == 1) {
            fprintf(out, "%d\n", i);
        }
    }
}