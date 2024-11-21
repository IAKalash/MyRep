#include <stdio.h>
#include <malloc.h>

int partition(int *a, int l, int r) {
    int i = l, j = r, temp;
    int pivot = a[l];
    while (i < j) {
        while (a[i] < pivot && i <= r - 1) {
            ++i;
        }
        while (a[j] > pivot && i >= l + 1) {
            --j;
        }
        if (i < j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    temp = a[l];
    a[l] = a[j];
    a[j] = temp;
    return j;
}

void quicksort (int* arr, int left, int right) {
    if (left < right) {
        int k = partition(arr, left, right);

        quicksort(arr, left, k - 1);
        quicksort(arr, k + 1, right);
    }
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

    quicksort(arr, 0, n - 1);

    for (int i = 0; i < n; ++i)
    {
        fwrite(&arr[i], 4, 1, out);
    }

    fclose(in);
    fclose(out);
}