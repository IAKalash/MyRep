#include "modular.h"

int MOD = 1;
int pnorm(int num){
    return((num % MOD + MOD) % MOD);
}

int padd(int n1, int n2){
    return pnorm(pnorm(n1) + pnorm(n2));
}

int psub(int n1, int n2){
    return pnorm(pnorm(n1) - pnorm(n2));
}

int pmul(int n1, int n2){
    int res = 0;
    n1 = pnorm(n1);
    n2 = pnorm(n2);

    while (n2 > 0) {
        if (n2 & 1) {
            res = (res + n1) % MOD;
        }
        n1 = (n1 * 2) % MOD;
        n2 = n2 >> 1;
    }
    return res;
}

int gcd(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1; 
    int num = gcd(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return num;
}

int inv (int a) {
    int x, y;
    int GCD = gcd(a, MOD, &x, &y);
    if (GCD != 1) {
        return -1;
    }
    else {
        return ((x % MOD + MOD) % MOD);
    }
}

int pdiv(int n1, int n2){
    return(pmul(n1, inv(pnorm(n2))));
}