#include <stdio.h>
#include <malloc.h>

void radixSort(unsigned long long *arr, int len) {
    
    
}

int main(void)
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int n;
    fread(&n, 4, 1, in);

    unsigned long long *arr = (unsigned long long *)malloc(8 * n);

    for (int i = 0; i < n; ++i)
    {
        fread(&arr[i], 8, 1, in);
    }

    radixSort(arr, n);

    for (int i = 0; i < n; ++i) {
        fwrite(&arr[i], 8, 1, out);
    }

    fclose(in);
    fclose(out);
}