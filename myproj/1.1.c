#include <stdio.h>
#include <string.h>

int func(int n1, int n2, char command[4], int mod) {
    int res;
    if (mod == 0) {
        if (strcmp(command, "add") == 0) {
            res = n1 + n2;
        }
        else if (strcmp(command, "sub") == 0) {
            res = n1 - n2;
        }
        else if (strcmp(command, "mul") == 0) {
            res = n1 * n2;
        }
    }
    else {
        if (strcmp(command, "add") == 0) {
            res = (n1 + n2) % mod;
        }
        else if (strcmp(command, "sub") == 0) {
            res = ((n1 - n2) % mod + mod) % mod;
        }
        else if (strcmp(command, "mul") == 0) {
            res = n1 * n2 % mod;
        }
    }
    return res;
}

int main(void)
{
    char str1[4], str2[4];
    int mod, num1, num2;

    if (scanf("%s", str1) == 0) {
        fprintf(stderr, "No parameters specified.");
        fclose(stdin);
        fclose(stdout);
        return 13;
    }
    else if (strcmp(str1, "-m") == 0) {
        scanf("%d %s %d %d", &mod, str2, &num1, &num2);
        printf("%d", func(num1, num2, str2, mod));
    }
    else {
        scanf("%d %d", &num1, &num2);
        if (scanf("%s %d", str2, &mod) == 0) {
            printf("%d", func(num1, num2, str1, 0));
        }
        else {
            printf("%d", func(num1, num2, str1, mod));
        }
    }
}
