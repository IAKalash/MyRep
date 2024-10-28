#include <stdio.h>

int main(void)
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt","w");

    int count = 0, len, sum = 0, num;

    fscanf(in, "%d", &len);
    while (count++ < len)
    {
        fscanf(in, "%d", &num);
        if (num % 2 == 0)
            sum += num;
    }
    fprintf(out, "%d", sum);
    
    fclose(in);
    fclose(out);
}