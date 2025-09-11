#include <stdio.h>

int gcd(int a, int b) { 
        return (b == 0 ? a : gcd(b, a%b));
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int tests, a, b;
    scanf ("%d", &tests);

    for (int i = 0; i < tests; ++i) {
        scanf("%d %d", &a, &b);
        printf("%d\n", gcd(a,b));
    }

    fclose(stdin);
    fclose(stdout);
}
