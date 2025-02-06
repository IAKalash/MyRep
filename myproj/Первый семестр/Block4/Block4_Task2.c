#include <stdio.h>

int len(char* string) {
    char sym = ' ';
    int i = 0;
    while (sym != '\0') {
        sym = string[i];
        ++i;
    }
    return i - 1;
}

void reverse(char *start, int len) {
    for (int i = len - 1; i >= 0; --i) {
        printf("%c", start[i]);
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    char str[100] = {0};

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", &str);
        reverse(str,len(str));
        printf("\n");
    }

    fclose(stdin);
    fclose(stdout);
}

