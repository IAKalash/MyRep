
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long fact (long long num) {
    if (num == 0 || num == 1) {
        return 1;
    }
    else {
        return (num * fact(num - 1) % 1000000007);
    }
}

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

int main(void) {
    long long num = 10, x, y;
    printf("%lld\n", gcd(fact(5) * fact(3), 1000000007, &x, &y));
    printf("%lld", x);
}
