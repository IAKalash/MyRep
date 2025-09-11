#include <stdio.h>
#include <malloc.h>

long long gcd(long long a, long long b, long long *x, long long *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    long long x1, y1; 
    long long num = gcd(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return num;
}

long long inv (long long a, long long MOD) {
    long long x, y;
    long long GCD = gcd(a, MOD, &x, &y);
    if (GCD != 1) {
        return 0;
    }
    else {
        return ((x % MOD + MOD) % MOD);
    }
}

long long pmult(long long n1, long long n2, long long m) {
    n1 = n1 % m;
    n2 = n2 % m;
    long long res = 0;
    while (n2 > 0) {
        if (n2 & 1) {
            res = (res + n1) % m;
        }
        n1 = (n1 << 1) % m;
        n2 = n2 >> 1;
    }
    return res;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int k;
    long long mul = 1, res = 0;
    scanf ("%d", &k);

    long long *m = (long long *)malloc(sizeof(long long) * k);
    long long *M = (long long *)malloc(sizeof(long long) * k);
    long long *Mi = (long long *)malloc(sizeof(long long) * k);
    long long *A = (long long *)malloc(sizeof(long long) * k);

    for (int i = 0; i < k; ++i) {
        scanf("%lld", &m[i]);
        mul *= m[i];
    }
    for (int i = 0; i < k; ++i) {
        scanf("%lld", &A[i]);
        M[i] = mul / m[i];
        Mi[i] = inv(M[i], m[i]);
    }
    
    for (int i = 0; i < k; ++i) {
        res = (res + pmult(M[i], pmult(Mi[i], A[i], mul), mul)) % mul;
    }
    
    printf("%lld", res);

    free(m);
    free(M);
    free(Mi);
    free(A);

    fclose(stdin);
    fclose(stdout);
}