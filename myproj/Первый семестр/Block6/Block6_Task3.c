#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, t, k, id = 0, count;
    char **arr = (char **)malloc(sizeof(char *) * 100);
    char sym;

    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d %d ", &t, &k);
        if (t == 0) {
            char *str = (char *)malloc(sizeof(char) * (n + 1));
            gets(str);
            arr[id] = str;
            ++id;
        }
        else if (t == 1) {
            free(arr[k]);
        }
        else if (t == 2) {
            printf("%s\n", arr[k]);
        }
        else {
            scanf("%c", &sym);
            count = 0;
            for (int i = 0; i < strlen(arr[k]); ++i) {
                if (arr[k][i] == sym) {
                    ++count;
                }
            }
            printf("%d\n", count);
        }
    }

    free(arr);

    fclose(stdin);
    fclose(stdout);
}