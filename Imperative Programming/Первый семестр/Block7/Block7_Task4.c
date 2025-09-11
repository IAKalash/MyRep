#include <stdio.h>
#include <malloc.h>

int binsearch(int *arr, int num, int len) {
    int M, L = 0, R = len - 1;

    while (arr[M] != num) {
        M = (L + R) / 2;
        if (L == M) {
            return -1;
        }
        else if (arr[M] <= num) {
            L = M;
        }
        else {
            R = M;
        }
    }
    return M;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, q, num, res;
    scanf("%d", &n);

    int *arr = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    scanf("%d", &q);

    for (int i = 0; i < q; ++i) {
        scanf("%d", &num);
        res = binsearch(arr, num + res, n);
        printf("%d\n", res);
        fflush(stdout);
    }

    fclose(stdin);
    fclose(stdout);
}