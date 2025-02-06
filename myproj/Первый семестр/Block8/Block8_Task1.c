#include <stdio.h>


int main(void)
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    long a, b;

    fread(&a, 4, 1, in);
    fread(&b, 4, 1, in);

    if (a > 0) {
        a = ((long long)a + b) / 2;
    }
    else {
        a = ((long long)a + b) / 2 - (1 && ((a + b) % 2));
    }
    printf("%d", a);

    fwrite(&a, 4, 1, out);

    fclose(in);
    fclose(out);
}