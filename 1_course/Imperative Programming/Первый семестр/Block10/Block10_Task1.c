#include <stdio.h>
#include <malloc.h>

int cmp(const void *x1, const void *x2)
{
    return (*(int *)x1 - *(int *)x2);
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int lenA, lenB;
    scanf("%d", &lenA);
    int *A = (int *)malloc(4 * lenA);

    for (int i = 0; i < lenA; ++i) {
        scanf("%d", &A[i]);
    }

    scanf("%d", &lenB);
    int *B = (int *)malloc(4 * lenB);

    for (int i = 0; i < lenB; ++i)
    {
        scanf("%d", &B[i]);
    }

    qsort(A, lenA, 4, cmp);
    qsort(B, lenB, 4, cmp);

    int i = 0, j = 0, count = 0, prev;
    int *res = (int *)malloc(4 * lenB);

    while (i < lenA || j < lenB) {
        if (A[i] == B[j]) {
            ++i;
        }
        else if (A[i] < B[j]){
            if (A[i] != prev) {
                res[count] = A[i];
                prev = A[i];
                ++count;
            }
            ++i;
        }
        else {
            ++j;
        }
    }

    printf("%d\n", count);

    for (int i = 0; i < count; ++i) {
        printf("%d ", res[i]);
    }

    free(A);
    free(B);
    free(res);

    fclose(stdin);
    fclose(stdout);
}