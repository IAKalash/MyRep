#include <stdio.h>
#include <malloc.h>

int main(void)
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int n, num, count = 0;
    fread(&n, 4, 1, in);

    int *nums = (int *)malloc(4 * 10000000);
    int *ids = (int *)malloc(4 * n);

    for (int i = 0; i < n; ++i) {
        fread(&num, 4, 1, in);
        if (nums[num % 10000000] != 1)
        {
            nums[num % 10000000] = 1;
            ids[count] = num;
            ++count;
        }
    }

    fwrite(&count, 4, 1, out);
    for (int i = 0; i < count; ++i) {
        fwrite(&ids[i], 4, 1, out);
    }

    fclose(in);
    fclose(out);
}
