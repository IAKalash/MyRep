#include <stdio.h>
#include <malloc.h>

void quickSort(int *arr, int left, int right)
{
    int l = left, r = right;
    int temp, pivot = arr[(left + right) / 2];

    while (l <= r)
    {
        while (arr[l] < pivot)
            ++l;
        while (arr[r] > pivot)
            --r;

        if (l <= r)
        {
            if (arr[l] > arr[r])
            {
                temp = arr[l];
                arr[l] = arr[r];
                arr[r] = temp;
            }

            ++l;
            --r;
        }
    };

    if (left < r)
        quickSort(arr, left, r);
    if (l < right)
        quickSort(arr, l, right);
}

int main(void)
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int n, pivot;

    fread(&n, 4, 1, in);

    int *arr = (int *)malloc(4 * n);

    for (int l = 0; l < n; ++l) {
        fread(&arr[l], 4, 1, in);
    }

    quickSort(arr, 0, n - 1);

    for (int l = 0; l < n; ++l)
    {
        fwrite(&arr[l], 4, 1, out);
    }

    free(arr);

    fclose(in);
    fclose(out);
}