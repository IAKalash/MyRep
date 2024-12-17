#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

uint64_t func(uint64_t s, int a, int b, int c, int M)
{
    return (s * s * a + s * b + c) % M;
}

uint32_t jenkins( unsigned char *key, size_t len)
{
    uint32_t hash, i;
    for(hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int a, b, c, M;
    uint64_t state = 1;
    uint64_t hash[10000000];

    for (int i = 0; i < 10000001; ++i) {
        hash[i] = 0;
    }

    scanf("%d", &M);
    scanf("%d %d %d", &a, &b, &c);

    for (uint64_t count = 0; 1; ++count) {
        if (hash[jenkins(state, sizeof(state))] == 1) {
            printf("%lld ", count);
            while (hash[jenkins(state, sizeof(state))] == 1) {
                state = func(state, a, b, c, M);
                ++count;
            }
            printf("%lld", count);
            fflush(stdout);
            break;
        }
        else {
            hash[jenkins(state, sizeof(state))] = 1;
        }
        state = func(state, a, b, c, M);
    }

    fclose(stdin);
    fclose(stdout);
}
