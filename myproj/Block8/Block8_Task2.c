#include <stdio.h>

void reverse(int *num) {
    *num = (*num >> 24 & 0b00000000000000000000000011111111) | (*num << 24 & 0b11111111000000000000000000000000)
     | (*num >> 8 & 0b00000000000000001111111100000000) | (*num << 8 & 0b00000000111111110000000000000000);
}

int main(void)
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int n, res, num;

    fread(&n, 4, 1, in);

    if (n > 10000) {
        reverse(&n);
        fread(&res, 4, 1, in);
        reverse(&res);
        for (int i = 1; i < n; ++i) {
            fread(&num, 4, 1, in);
            reverse(&num);
            res += num;
        }
        reverse(&res);
        fwrite(&res, 4, 1, out);
    }
    else{
        fread(&res, 4, 1, in);
        for (int i = 1; i < n; ++i)
        {
            fread(&num, 4, 1, in);
            res += num;
        }
        fwrite(&res, 4, 1, out);
    }

    fclose(in);
    fclose(out);
}