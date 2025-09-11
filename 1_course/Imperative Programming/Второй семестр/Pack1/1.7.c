#include <stdio.h>
#include <malloc.h>

double **create (int m) {
    double **matrix = (double **)calloc(m, sizeof(double *));
    for (int i = 0; i < m; ++i) {
        matrix[i] = (double *)calloc(m + 1, sizeof(double));
    }
    return matrix;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int m;
    scanf("%d", &m);

    double *res = (double *)calloc(m, sizeof(double));
    double **matrix = create(m);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j <= m; ++j) {
            scanf("%lf", &matrix[i][j]);
        }
    }

    for(int k = 0; k < m - 1; ++k) {
        for(int i = k; i < m; ++i) {
            if (matrix[i][k] != 0) {
                for (int j = m; j >= k; --j) {
                    matrix[i][j] /= matrix[i][k];
                }
                if (i != k) {
                    for(int j = 0; j <= m; ++j) {
                        matrix[i][j] -= matrix[k][j];
                    }
                }
            }
        }
    }
    
    for(int i = m - 1; i >= 0; --i) {
        for (int j = i + 1; j < m; ++j) {
            matrix[i][m] -= matrix[i][j] * res[j];
        }
        res[i] = matrix[i][m] / matrix[i][i];
    }

    for (int i = 0; i < m; ++i) {
        printf("%0.10f\n", res[i]);
    }

    for (int i = 0; i < m; ++i) {
        free(matrix[i]);
    }
    free(matrix);
    free(res);

    fclose(stdin);
    fclose(stdout);
}