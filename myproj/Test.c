#include <stdio.h>
#include <malloc.h>

typedef unsigned short bitword;

bitword* bitsetZero(bitword *arr, int num)
{
    free(arr);
    return (bitword *)malloc(sizeof(bitword) * (num / 8 / sizeof(bitword) + 1));
}
// // возвращает значение idx-ого бита (0 или 1)
int bitsetGet(bitword *arr, int idx)
{
    bitword mask = 0b1000000000000000;
    mask >>= (idx % 16);
    mask &= arr[idx / 16];
    if (mask)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, op, idx, newval;
    bitword *arr = NULL;

    printf("%p\n", arr);

    arr = bitsetZero(arr, 100);

    printf("%p", arr);
    fflush(stdout);

    arr[1] = 0b11110000;

    printf("%d",arr[1]);

    fclose(stdin);
    fclose(stdout);
}