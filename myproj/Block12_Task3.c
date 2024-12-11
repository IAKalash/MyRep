#include <stdio.h>
#include <malloc.h>

int main(void)
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    
    
    fclose(in);
    fclose(out);
}
