#include <stdio.h>
#include <malloc.h>
#include <string.h>

int cmp(const void *x1, const void *x2)
{
    return (*(int *)x1 - *(int *)x2);
}

int len(char *string) // Длина строки
{
    char sym = ' ';
    int i = 0;
    while (sym != '\0')
    {
        sym = string[i];
        ++i;
    }
    return i - 1;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int arrlen, strlen, qarr, qstr;
    long long num;
    char string[31];

    scanf("%d", &arrlen);
    long long *arr = (long long *)malloc(sizeof(long long) * arrlen);

    for (int i = 0; i < n; ++i) {
        scanf("%lld", &num);
        arr[i] = num;
    }

    qsort(arr, arrlen, sizeof(long long), cmp);

    scanf("%d", &strlen);
    char *strings = (char *)malloc(31 * strlen);

    for (int i = 0; i < n; ++i) {
        scanf("%s", &string);
        char *str = (char *)malloc(len(string));
        strcpy(str,string);
        strings[i] = str;
    }

    qsort(strings, strlen, 31, cmp)

    scanf("%d", &qarr);

    for (int i = 0; i < qarr; ++i) {

    }

    free(arr);
    free(strings);

    fclose(stdin);
    fclose(stdout);
}
