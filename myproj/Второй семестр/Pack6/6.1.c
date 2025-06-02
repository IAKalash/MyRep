#include <stdlib.h>
#include <stdio.h>

int place(char **field, int **attacked, int *places, int columns, int rows, int curr_row) {
    if (curr_row == rows) return 1;
    for (int i = 0; i < columns; ++i) {
        if (field[curr_row][i] == '?' && !attacked[curr_row][i]) {
            places[curr_row] = i;
            for (int j = 1; j + curr_row < rows; ++j) {
                attacked[curr_row + j][i]++;
                if (i + j < columns) attacked[curr_row + j][i + j]++;
                if (i - j >= 0) attacked[curr_row + j][i - j]++;
            }
            if (place(field, attacked, places, columns, rows, curr_row + 1)) 
                return 1;
            else {
                for (int j = 1; j + curr_row < rows; ++j) {
                    attacked[curr_row + j][i]--;
                    if (i + j < columns) attacked[curr_row + j][i + j]--;
                    if (i - j >= 0) attacked[curr_row + j][i - j]--;
                }
            }
        }    
    }
    return 0;
} 

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int m, n;
    scanf("%d %d", &m, &n);

    char **field = (char **)malloc(sizeof(char *) * m);
    int **attacked = (int **)malloc(sizeof(int *) * m);
    int buf;
    for (int i = 0; i < m; ++i) {
        char *row = (char *)malloc(n + 1);
        int *line = (int *)calloc(n + 1, sizeof(int));
        scanf("%d", &buf);
        fgets(row, n + 1, stdin);
        field[i] = row;
        attacked[i] = line;
    }

    int *places = (int *)malloc(sizeof(int) * m);

    if (place(field, attacked, places, n, m, 0)) {
        printf("YES\n");
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (places[i] == j) printf("X");
                else printf(".");
            }
            printf("\n");
        }
    }
    else printf("NO");

    for (int i = 0; i < m; ++i) {
        free(field[i]);
        free(attacked[i]);
    }
    free(field);
    free(attacked);

    fclose(stdin);
    fclose(stdout);
    return 0;
}