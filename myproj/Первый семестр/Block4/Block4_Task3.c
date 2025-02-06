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

char* concat(char *pref, char *suff) {
    int n = 0;
    for (int i = len(pref); i < len(pref) + len(suff); ++i) {
        pref[i] = suff[n];
        ++n;
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    char str[100] = { 0 }, res[1000] = { 0 };


    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", &str);
        concat(res, str);
    }
    printf("%s",res);

    fclose(stdin);
    fclose(stdout);
}

