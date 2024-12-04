#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

uint64_t func(uint64_t s, int a, int b, int c, int M)
{
    return (s * s * a + s * b + c) % M;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int a, b, c, M;
    uint64_t state = 1;
    uint64_t hash[1000];

    scanf("%d", &M);
    scanf("%d %d %d", &a, &b, &c);

    for (int i = 0; i < 50; ++i) {
        TEST[i] = state;
        state = func(state, a, b, c, M);
    }

    for (int i = 0; i < 50; ++i) {
        printf("%d ", TEST[i]);
    }

    fclose(stdin);
    fclose(stdout);
}
