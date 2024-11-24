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
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    int *arr = (int *)malloc(4 * n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    quickSort(arr, 0, n - 1);

    int *res = (int *)malloc(4 * n);

    int prev, count = 0;
    for (int i = 0; i < n; ++i) {
        if (prev != arr[i]){
            prev = arr[i];
            res[count] = arr[i];
            ++count;
        }
    }

    printf("%d\n", count);

    for (int i = 0; i < count; ++i) {
        printf("%d\n", res[i]);
    }

    free(arr);
    free(res);

    fclose(stdin);
    fclose(stdout);
}