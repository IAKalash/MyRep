#include <stdio.h>
#include <malloc.h>

int partition(int *a, int n, int pivot) {
    int i = 0, j = n - 1, k, temp;
    // while (a[i] >= pivot)
    //     ++i;
    // while (a[j] <= pivot)
    //     --j;
    while (i <= j) {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        ++i;
        --j;
    }
    return 0;
}

int main(void)
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int n, pivot;

    fread(&n, 4, 1, in);
    fread(&pivot, 4, 1, in);

    int *arr = (int *)malloc(4 * n);

    for (int i = 0; i < n; ++i) {
        fread(&arr[i], 4, 1, in);
    }

    int k = partition(arr, n, pivot);

    fwrite(&k, 4, 1, out);

    for (int i = 0; i < n; ++i)
    {
        fwrite(&arr[i], 4, 1, out);
    }

    fclose(in);
    fclose(out);
}