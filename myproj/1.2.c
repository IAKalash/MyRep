#include <stdio.h>

int gcd(int a, int b, int *x, int *y) { 
    if (b == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int x1, y1;
    int n = gcd(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return n;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int tests, mod, num, x, y;
    scanf ("%d %d", &tests, &mod);

    for (int i = 0; i < tests; ++i) {
        scanf("%d", &num);
        gcd(num, mod, &x, &y);
        printf("%d\n", x);
    }

    fclose(stdin);
    fclose(stdout);
}
