#include <stdio.h>

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int tests;
    long long int m, num;
    double numd, p, q;

    scanf("%d", &tests);

    for (int i = 0; i < tests; ++i) {
        scanf("%d/%d xor %llx", &p, &q, &m);

        numd = p / q;
        num = *((long long int*)&(numd));

        printf("%0.15g\n", num^m);
    }

    fclose(stdin);
    fclose(stdout);
}