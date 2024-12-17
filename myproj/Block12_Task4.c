
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        
    }

    scanf("%d", &m);

    for (int i = 0; i < m; ++i) {
        
    }

    for (int i = 0; i < n; ++i) {
        
    }

    fclose(stdout);
    fclose(stdin);
}
