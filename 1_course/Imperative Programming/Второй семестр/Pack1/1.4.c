#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int q = 0, n = 0, k = 0, mod = 0;

    scanf("%d %d\n", &mod, &q);

    int **bin = (int **)malloc(sizeof(int *) * 2001);

    for (int i = 0; i < 2001; ++i) {
        bin[i] = (int *)malloc(sizeof(int) * (i + 1));
    }

    for (int i = 0; i < 2001; ++i) {
        bin[i][0] = 1;
        bin[i][i] = 1;
    }

    for (int i = 2; i < 2001; ++i) {
        for (int j = 1; j < i; ++j) {
            bin[i][j] = (bin[i - 1][j] + bin[i - 1][j - 1]) % mod;
        }
    }
    
    for (int i = 0; i < q; ++i) {
        scanf("%d %d\n", &n, &k);
        if (k < 0 || k > n) {
            printf ("0\n");
        }
        else {
            printf("%d", bin[n][k]);
            if (i != q - 1) {
                printf("\n");
            }
        }
    }

    fclose(stdin);
    fclose(stdout);
    for(int k = 0; k < 2001; k++){
        free(bin[k]);
    }
    free(bin);
    return 0;
}