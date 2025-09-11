#include <stdio.h>
#include <malloc.h>

#define mod 1000000007

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

long long inv (long long a) {
    long long x, y;
    long long GCD = gcd(a, mod, &x, &y);
    if (GCD != 1) {
        return -1;
    }
    else {
        return ((x % mod + mod) % mod);
    }
}

long long bin(int n, int k, long long *arr) {
    return (arr[n] * inv(arr[k] * arr[n - k]) % mod);
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t, n, k;
    long long *arr = (long long *)calloc(1000001, sizeof(long long));
    arr[0] = 1;
    arr[1] = 1;

    for (int i = 2; i < 1000001; ++i) {
        arr[i] = i * arr[i - 1] % mod;
    }

    scanf("%d", &t);

    for (int i = 0; i < t; ++i) {
        scanf("%d %d", &n, &k);
        printf("%lld\n", bin(n, k, arr));
    }

    fclose(stdin);
    fclose(stdout);
}