#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

extern int Query (int l, int64_t sum);
extern void Init (long long *arr, int n);

long long *arr;
int n;
int64_t s;

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int m, l;
    scanf ("%d %d", &n, &m);

    arr = (long long *)malloc(sizeof(long long) * n);

    for (int i = 0; i < n; ++i) {
        scanf("%lld", &arr[i]);
    }

    Init(arr, n);

    for (int i = 0; i < m; ++i) {
        scanf("%d %lld", &l, &s);
        printf("%d\n", Query(l, s));
    }

    free(arr);

    fclose(stdin);
    fclose(stdout);
}