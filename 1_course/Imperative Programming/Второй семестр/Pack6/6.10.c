#include <stdlib.h>
#include <stdio.h>

int find(int *nums, int n, int *res, int *ind) {
    int *prev = malloc(sizeof(int) * n);
    int *d = malloc(sizeof(int) * n);

    for (int i = 0; i < n; ++i) {
        d[i] = 1;
        prev[i] = -1;
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i] && d[j] + 1 > d[i]) {
                d[i] = d[j] + 1;
                prev[i] = j;
            }
        }
    }
    int pos = 0;
    int len = d[0];

    for (int i = 0; i < n; ++i) {
        if (d[i] > len) {
            pos = i;
            len = d[i];
        }
    }

    for (int i = len - 1; pos != -1; --i) {
        res[i] = nums[pos];
        ind[i] = pos + 1;
        pos = prev[pos];
    }

    free(prev);
    free(d);

    return len;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    int *nums = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &nums[i]);
    }

    int *indexes = (int *)calloc(n, sizeof(int));
    int *res = (int *)calloc(n, sizeof(int));
    int len = find(nums, n, res, indexes);

    printf("%d\n", len);
    for (int i = 0; i < len; ++i) {
        if (indexes[i]) printf("A[%d] = %d\n", indexes[i], res[i]);
    }

    free(nums);
    free(res);
    free(indexes);

    fclose(stdin);
    fclose(stdout);
    return 0;
}