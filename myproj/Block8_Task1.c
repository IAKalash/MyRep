#include <stdio.h>

int main(void)
{
    FILE *in = fopen("1.in", "rb");
    FILE *out = fopen("output.txt", "wb");

    int a, b;

    fread(&a, 4, 1, in);

    printf("%d", a);

    fclose(in);
    fclose(out);
}