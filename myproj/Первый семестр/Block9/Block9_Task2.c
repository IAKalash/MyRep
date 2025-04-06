#include <stdio.h>
#include <malloc.h>

int partition(int *a, int n, int pivot) {
    int i = 0, j = n - 1, k, temp;
    while (i != pivot) {
        if (a[i] > pivot) {
            if (a[j] < pivot) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
            else {
                --j;
            }
        }
        else if (a[j] < pivot) {
            if (a[i] > pivot) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
            else {
                ++i;
            }
        }
        else {
            ++i;
            --j;
        }
    }
    return j + 1;
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