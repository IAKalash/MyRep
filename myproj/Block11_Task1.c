#include <stdio.h>
#include <malloc.h>

int main(void)
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int n, num;
    fread(&n, 4, 1, in);

    

    fclose(in);
    fclose(out);
}
