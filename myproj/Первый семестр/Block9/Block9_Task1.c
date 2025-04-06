#include <stdio.h>
#include <malloc.h>

int merge(const int *a, int ak, const int *b, int bk, int *res) {
    int rk = 0, fl = 1, countA = 0, countB = 0, n;
    while (fl) {
        if (a[countA] <= b[countB]) {
            res[rk] = a[countA];
            ++countA;
            ++rk;
        }
        else {
            res[rk] = b[countB];
            ++countB;
            ++rk;
        }

        if (countA == ak) {
            while (countB < bk) {
                res[rk] = b[countB];
                ++rk;
                ++countB;
            }
            fl = 0;
        }
        else if (countB == bk) {
            while (countA < ak)
            {
                res[rk] = a[countA];
                ++rk;
                ++countA;
            }
            fl = 0;
        }
    }
    return rk;
}

int main(void)
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int n, m;

    fread(&n, 4, 1, in);
    fread(&m, 4, 1, in);

    int *arr1 = (int *)malloc(4 * n);
    int *arr2 = (int *)malloc(4 * m);

    for (int i = 0; i < n; ++i) {
        fread(&arr1[i], 4, 1, in);
    }

    for (int i = 0; i < m; ++i)
    {
        fread(&arr2[i], 4, 1, in);
    }

    int *res = (int *)malloc(4 * (n + m));

    int rk = merge(arr1, n, arr2, m, res);

    for (int i = 0; i < rk; ++i)
    {
        printf("%x ", res[i]);
        fwrite(&res[i], 4, 1, out);
    }

    fclose(in);
    fclose(out);
}