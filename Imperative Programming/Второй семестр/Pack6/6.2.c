#include <stdlib.h>
#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    long long **table = (long long **)malloc(sizeof(long long *) * (n + 1));

    long long *fst_line = (long long *)malloc(sizeof(long long) * (n + 1));
    table[0] = fst_line;

    for (int j = 0; j <= n; ++j) {
        table[0][j] = 1;
    }

    for (int i = 1; i <= n; ++i) {
        table[i] = (long long *)calloc((n + 1), sizeof(long long));
        table[i][0] = 0;
        for (int j = 1; j <= n; ++j) {
            if (i >= j) table[i][j] = (table[i][j - 1] + table[i - j][j]) % 1000000007;
            else table[i][j] = table[i][j - 1];
        }
    }

    printf("%lld", table[n][n]);

    fclose(stdin);
    fclose(stdout);
    return 0;
}