#include <stdio.h>
#include <malloc.h>
#include <string.h>

int compare(const void *x1, const void *x2)
{
    int r;
    if (x1 >= x2) r = 1;
    else if (x1 == x2) r = 0;
    else r = -1;
    return r;
}

int lower_bound (void *elem, void *arr, int elemsize, int len, int compare(const void *x1, const void *x2)) {
    int count = 0;
    
    while (count != len) {
        if (compare(arr[count], elem) >= 0) {
            return count;
        }
        else {
            ++count;
        }
    }
    return count;
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

    for (int i = 0; i < arrlen; ++i) {
        scanf("%lld", &num);
        arr[i] = num;
    }

    qsort(arr, arrlen, sizeof(long long), compare);

    scanf("%d", &strlen);
    char *strings = (char *)malloc(31 * strlen);

    for (int i = 0; i < strlen; ++i) {
        scanf("%s", &strings[i]);
    }

    qsort(strings, strlen, 31, compare);

    scanf("%d", &qarr);

    for (int i = 0; i < qarr; ++i) {
        scanf("%lld", &num);
        printf("0");
        fflush(stdout);
        printf("%d", lower_bound((void *)num, (void *)arr, 8, arrlen, compare));
        printf("1\n");
        fflush(stdout);
    }

    scanf("%d", &qstr);

    for (int i = 0; i < qarr; ++i) {
        scanf("%s", &string);
        printf("%d", lower_bound((void *)string, (void *)strings, 31, strlen, compare));
    }

    fflush(stdout);

    free(arr);
    free(strings);

    fclose(stdin);
    fclose(stdout);
}
