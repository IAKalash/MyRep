#include <stdio.h>
#include <string.h>

void split(char *str) {
    int i = 0;
    int len = strlen(str);
    while (i < len) {
        if (str[i] == 34) {
            ++i;
            printf("[");
            while(str[i] != 34) {
                printf("%c", str[i]);
                ++i;
            }
            printf("]\n");
        }
        else if (str[i] != 32) {
            printf("[");
            if (str[i + 1] != 32) {
                while(str[i] != 32 && i < len) {
                    printf("%c", str[i]);
                    ++i;
                }
                printf("]\n");
            }
            else{
                printf("%c]\n", str[i]);
            }
        }
        ++i;
        fflush(stdout);
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