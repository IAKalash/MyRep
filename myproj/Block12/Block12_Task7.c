#include <stdio.h>
#include <malloc.h>

int max (int *arr, int L, int R) {
    int max = -2147483647;
    for (int i = L; i < R; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, L = 0, R = 0;
    char sym;
    scanf("%d", &n);

    int *arr = (int *)calloc(n, 4);

    for (int i = 0; i < n; ++i) {
        scanf("%d ", &arr[i]);
    }

    for (int i = 0; i < 2*n - 1; ++i) {
        scanf("%c", &sym);
        if (sym == 'R') {
            ++R;
        }
        else {
            ++L;
        }
        printf("%d\n", max(arr, L, R));
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}