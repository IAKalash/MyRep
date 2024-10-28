#include <stdio.h>
#include <malloc.h>

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    double **bin = (double **)malloc(sizeof(double *) * 1001);

    for (int i = 0; i < 1002; ++i) {
        bin[i] = (double *)malloc(sizeof(double) * (i + 1));
        bin[i][0] = 1;
        bin[i][i] = 1;
    }

    for (int i = 2; i < 1002; ++i) {
        for (int j = 1; j < i; ++j) {
            bin[i][j] = bin[i - 1][j] + bin[i - 1][j - 1];
        }
    }

    int q, n, k;

    scanf("%d", &q);
    
    for (int i = 0; i < q; ++i) {
        scanf("%d %d", &n, &k);
        printf("%0.10g\n", bin[n][k]);
    }

    fclose(stdin);
    fclose(stdout);

    free(bin);
}