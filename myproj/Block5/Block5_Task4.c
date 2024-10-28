#include <stdio.h>
#include <malloc.h>

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, q, x;
    int *nums;

    scanf("%d %d", &n, &q);

    nums = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; ++i) {
        nums[i] = 1;
    }

    nums[0] = 0;
    nums[1] = 0;
    for (int i = 2; i * i < n; ++i)
    {
        for (int j = 2; i * j < n; ++j)
        {
            nums[i * j] = 0;
        }
    }

    for (int i = 0; i < q; ++i)
    {
        scanf("%d", &x);
        if (nums[x] == 1)
        {
            printf("%d prime\n", x);
        }
        else
        {
            printf("%d not\n", x);
        }
    }

    free(nums);

    fclose(stdin);
    fclose(stdout);
}