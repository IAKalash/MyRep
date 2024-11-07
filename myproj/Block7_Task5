#include <stdio.h>
#include <malloc.h>

int binsearch(int *arr, int num, int len, int *x) {
    int M, L = 0, R = len - 1;

    while (arr[M] != num) {
        M = (L + R) / 2;
        if (L == M) {
            if (num - arr[L] < arr[R] - num) {
                *x = num - arr[L];
                return L;
            }
            else {
                *x = arr[R] - num;
                return R;
            }
        }
        else if (arr[M] < num) {
            L = M;
        }
        else {
            R = M;
        }
    }
    if (arr[M-1] != num) {
        return M;
    }
    else {
        return --M;
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, q, num, res, x;
    scanf("%d", &n);

    int *arr = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    scanf("%d", &q);

    for (int i = 0; i < q; ++i) {
        scanf("%d", &num);
        x = 0;
        res = binsearch(arr, num, n, &x);
        printf("%d %d\n", res, x);
        fflush(stdout);
    }

    fclose(stdin);
    fclose(stdout);
}
