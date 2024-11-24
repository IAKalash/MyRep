#include <stdio.h>
#include <malloc.h>

void reverse(int *num)
{
    *num = (*num >> 24) | (*num << 24) | (*num >> 8 & 0b00000000000000001111111100000000) | (*num << 8 & 0b00000000111111110000000000000000);
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int a = 0b00000001;
    a >>= 1;
    printf("%llx", a);

    fclose(stdin);
    fclose(stdout);
}

int lenL = m - l + 1, lenR = r - m + 1;

int *Left = (int *)malloc(4 * lenL);
int *Right = (int *)malloc(4 * lenR);

for (int i = 0; i < lenL; ++i)
{
    Left[i] = a[l + i];
}
for (int i = 0; i < lenR; ++i)
{
    Right[i] = a[m + 1 + i];
}
