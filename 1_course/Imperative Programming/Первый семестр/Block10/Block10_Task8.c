#include <stdio.h>
#include <malloc.h>

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, fl = 1;
    scanf("%d", &n);

    char **arr = (char **)malloc(sizeof(char **) * n);

    for (int i = 0; i < n; ++i) {
        char *str = (char *)malloc(n);
        scanf("%s", str);
        arr[i] = str;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (arr[i][j] == '1')
            {
                for (int k = 0; k < n; ++k) {
                    if (arr[j][k] == '1') {
                        arr[i][k] = '1';
                    }
                }
            }
        }
        arr[i][i] = '1';
    }

    for (int i = 0; i < n; ++i) {
        printf("%s\n", arr[i]);
    }

    free(arr);

    fclose(stdin);
    fclose(stdout);
}