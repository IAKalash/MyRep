#include <stdio.h>
#include <malloc.h>

void sort(int els, int *array) // Пузырёк
{
    int x;
    for (int i = 0; i < els; ++i)
    {
        for (int j = i + 1; j < els; ++j)
        {
            if (array[i] > array[j])
            {
                x = array[j];
                array[j] = array[i];
                array[i] = x;
            }
        }
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    long long res = 0;

    scanf("%d", &n);

    int *arr = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    sort(n, arr);

    for (int i = 0; i < n - 1; ++i) {
        res += arr[i] * (n - i - 1);
    }

    printf("%lld", res);

    fclose(stdin);
    fclose(stdout);
}