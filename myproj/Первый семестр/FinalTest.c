#include <stdio.h>
#include <malloc.h>
#include <string.h>

int **create (int n, int m) {
    int **matrix = (int **)calloc(n, sizeof(int *));
    for (int i = 0; i < n; ++i) {
        int *str = (int *)calloc(m, sizeof(int));
        for (int j = 0; j < m; ++j) {
            str[j] = 0;
        }
        matrix[i] = str;
    }
    return matrix;
}

int **recreate (int ** oldmatrix, int n0, int m0, int n, int m) {
    int **matrix = (int **)realloc(oldmatrix,sizeof(int *) * n);
    for (int i = 0; i < n0; ++i) {
        int *str = (int *)realloc(matrix[i],sizeof(int) * m);
        matrix[i] = str;
    }
    for (int i = n0; i < n; ++i) {
        int *str = (int *)malloc(sizeof(int) * m);
        for (int j = 0; j < m; ++j) {
            str[j] = 0;
        }
        matrix[i] = str;
    }
    return matrix;
}

int **change (int **matrix, int n, int m, int num) {
    matrix[n][m] += num;
    return matrix;
}

void printMatrix (int **matrix, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n1, n2, n3, c, n, m;
    int **matrix = NULL;
    char command[10];
    
    do {
        c = scanf ("%s", &command);
        if (c == EOF) {
            break;
        }
        if (strcmp(command, "CREATE") == 0) {
            if (matrix == NULL) {
                scanf("%d %d", &n, &m);
                matrix = create(n, m);
            }
            else {
                n1 = n;
                n2 = m;
                scanf("%d %d", &n, &m);
                matrix = recreate(matrix, n1, n2, n, m);
            }
        }
        else if (strcmp(command, "CHANGE") == 0) {
            scanf("%d %d %d", &n1, &n2, &n3);
            change(matrix, n1, n2, n3);
        }
    } while (1);

    printMatrix(matrix, n, m);

    free(matrix);
    
    fclose(stdin);
    fclose(stdout);
}
