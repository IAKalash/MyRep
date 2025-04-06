#include <stdio.h>
#include <malloc.h>

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int m, n, key, val;

    scanf("%d %d", &n, &m);
    int arr[n][n];
    int res[n];

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            arr[i][j] = 0;
        }
    }

    for (int i = 0; i < m; ++i)
    {
        scanf("%d %d", &key, &val);
        arr[--val][--key] = 1;
    }

    int fl, c = 0, prev = -1;
    while (c != n)
    {
        for (int i = 0; i < n; ++i)
        {
            fl = 1;
            for (int j = 0; j < n; ++j)
            {
                if (arr[i][j] == 1)
                {
                    fl = 0;
                    break;
                }
            }
            if (fl == 1)
            {
                res[c] = i + 1;
                ++c;
                for (int k = 0; k < n; ++k)
                {
                    arr[k][i] = 0;
                }
                arr[i][0] = 1;
            }
        }
        if (prev == c)
        {
            printf("bad course");
            return 0;
        }
        prev = c;
    }

    for (int i = 0; i < n; ++i)
    {
        printf("%d ", res[i]);
    }

    fclose(stdin);
    fclose(stdout);
}