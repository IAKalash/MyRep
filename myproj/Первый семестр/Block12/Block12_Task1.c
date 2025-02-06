#include <stdio.h>
#include <malloc.h>

int min (int *arr, int len) {
    int min = 2147483647, num, adr;
    for (int i = 0; i < len; ++i) {
        num = arr[i];
        if (num < min) {
            min = num;
            adr = i;
        }
    }
    arr[adr] = 2147483647; 
    return min;
}

int main(void)
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int len, temp = -2137483647;
    fread(&len, 4, 1, in);

    int *arr = (int *)malloc(4 * len);
    int *res = (int *)malloc(4 * len);

    for (int i = 0; i < len; ++i) {
        fread(&arr[i], 4, 1, in);
    }

    for (int i = 0; i < len; ++i) {
        temp = min(arr, len);
        res[i] = temp;
    }

    for (int i = 0; i < len; ++i) {
        fwrite(&res[i], 4, 1, out);
    }

    fclose(in);
    fclose(out);
}
