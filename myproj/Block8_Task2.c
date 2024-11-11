#include <stdio.h>


int main(void)
{
    FILE *in = fopen("4.in", "rb");
    FILE *out = fopen("output.txt", "wb");

    

    fclose(in);
    fclose(out);
}