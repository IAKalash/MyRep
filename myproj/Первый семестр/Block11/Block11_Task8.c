#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, b, fl = 0;
    scanf("%d %d", &n, &b);

    int c = n - b + 1;

    char *str = (char *)malloc(n + 1);
    int *res = (int *)malloc(4 * c + 1);
    char **subs = (char **)malloc(c * sizeof(char *));

    for (int i = 0; i < c; ++i) {
        res[i] = -1;
    }

    scanf("%s", str);

    for (int i = 0; i < c; ++i) {
        char *sub = (char *)malloc(b + 1);
        sub[b] = '\0';
        for (int l = 0; l < b; ++l) {
            sub[l] = str[i + l];
        }
        subs[i] = sub;
    }

    for (int i = 0; i < c; ++i) {
        for (int j = i + 1; j < c; ++j) {
            if (strcmp(subs[i], subs[j]) == 0) {
                if (res[i] != -1) {
                    res[j] = res[i];
                }
                else {
                    res[i] = fl;
                    res[j] = fl;
                    ++fl;
                }
            }
        }
        if (res[i] == -1) {
            res[i] = fl;
            ++fl;
        }
    }
    
    for (int i = 0; i < c; ++i) {
        printf("%d ", res[i]);
    }

    fclose(stdin);
    fclose(stdout);
}
