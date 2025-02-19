#include <stdio.h>

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

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int tests, mod, num, x, y;
    scanf ("%d %d", &tests, &mod);

    for (int i = 0; i < tests; ++i) {
        scanf("%d", &num);
        if (gcd(num, mod, &x, &y) != 1) {
            printf("-1\n");
        }
        else {
            printf("%d\n", (x % mod + mod) % mod);
        }
    }

    fclose(stdin);
    fclose(stdout);
}
