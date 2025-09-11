#include <stdio.h>
#include <malloc.h>

int check (long long *arr, int max) {
    int count = 0;
    for (int i = 0; i < max; ++i) {
        for (int j = i + 1; j < max; ++j) {
            if ((arr[i] & arr[j]) == 0) {
                ++count;
            }
        }
    }
    return count;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;

    scanf("%d", &n);

    long long *arr = (long long *)malloc(sizeof(long long) * n);

    for (int i = 0; i < n; ++i) {
        scanf("%llx", &arr[i]);
    }

    printf("%d", check(arr, n));

    free(arr);

    fclose(stdin);
    fclose(stdout);
}
