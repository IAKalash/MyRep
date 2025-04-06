#include <stdio.h>
#include <string.h>

void split(char *str) {
    int i = 0, fl = 0, c = 0;
    int len = strlen(str);
    while (str[i] == ' ' || str[i] == '\t') {
        ++i;
    }
    --len;
    while (str[len] == ' ' || str[len] == '\t') {
        --len;
    }
    ++len;
    if (len != 0) {
        printf("[");
        while (i <= len) {
            if (((str[i] == ' ' || str[i] == '\t') && fl == 0) || i == len) {
                while (str[i + 1] == ' ' || str[i] == '\t') {
                    ++i;
                }
                printf("]\n");
                ++i;
                if (i < len) {
                    printf("[");
                }
            }
            else if (str[i] == '\\') {
                c = 0;
                while (str[i] == '\\') {
                    ++c;
                    ++i;
                }
                if (str[i] == '\"') {
                    if (c % 2 == 0) {
                        for (int x = 0; x < c / 2; ++x) {
                            printf("\\");
                        }
                    }
                    else {
                        for (int x = 0; x < (c - 1) / 2; ++x) {
                            printf("\\");
                        }
                        printf("%c",str[i]);
                        ++i;
                    }
                }
                else {
                    for (int x = 0; x < c; ++x) {
                        printf("\\");
                    }
                }
            }
            else if (str[i] == '\"') {
                if (str[i + 1] == '\"' && fl == 1) {
                    printf("\"");
                    i += 2;
                }
                else if (str[i + 1] == '\"') {
                    i += 2;
                }
                else {
                    if (fl == 0) {
                        ++fl;
                        ++i;
                    }
                    else {
                        --fl;
                        ++i;
                    }
                }
            }
            else {
                printf("%c", str[i]);
                ++i;
            }
        }
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char str[101] = {0};

    gets(str);
    split(str);

    fclose(stdin);
    fclose(stdout);
    }