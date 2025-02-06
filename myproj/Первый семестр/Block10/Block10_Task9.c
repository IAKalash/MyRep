#include <stdio.h>
#include <malloc.h>

int len(char* str) {
    int c = 0;
    char sym = str[0];
    while (sym != '\0') {
        ++c;
        sym = str[c];
    }
    return c;
}

int check (char *str, int len) {
    for (int i = 0; i < len; ++i) {
        for (int j = len - 1; j >= i; --j) {
            if (str[i] == '0') {
                break;
            }
            if (i == j) {
                return 0;
            }
            else if (str[i] == '(') {
                if (str[j] == ')') {
                    str[j] = '0';
                    break;
                }
            }
            else if (str[i] == '[') {
                if (str[j] == ']') {
                    str[j] = '0';
                    break;
                }
            }
            else if (str[i] == '{') {
                if (str[j] == '}') {
                    str[j] = '0';
                    break;
                }
            }
            else if (str[i] == '<') {
                if (str[j] == '>') {
                    str[j] = '0';
                    break;
                }
            }
        }
    }
    return 1;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    char str[1000];

    scanf("%d", &n);

    for (int c = 0; c < n; ++c) {
        scanf("%s", str);
        if (check(str, len(str))) {
            printf("T\n");
        }
        else {
            printf("NIL\n");
        }
    }

    fclose(stdin);
    fclose(stdout);
}
