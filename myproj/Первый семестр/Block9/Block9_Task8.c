#include <stdio.h>
#include <malloc.h>

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, q, C, min, num, count;
    scanf("%d", &n);

    int *arr = (int *)calloc(n, 4);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    scanf("%d", &q);

    for (int i = 0; i < q; ++i) {
        scanf("%d", &C);
        min = 10000000;
        for (int j = 0; j < n; ++j) {
            num = arr[j] + C * j;
            if (num < min) {
                min = num;
                count = j;
            }
        }
        printf("%d\n", count);
    }

    fclose(stdin);
    fclose(stdout);
}