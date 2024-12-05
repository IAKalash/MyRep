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
    uint64_t hash[100000];

    scanf("%d", &M);
    scanf("%d %d %d", &a, &b, &c);

    for (int i = 0; i != -1; ++i) {
        if (hash[state % 100000] == 0) {
            hash[state % 100000] = i;
            state = func(state, a, b, c, M);
        }
        else {
            printf("%d %d", hash[state % 100000], i);
            break;
        }
    }

    fclose(stdin);
    fclose(stdout);
}
