#include <stdio.h>
#pragma warning(disable:4996)
int main(void)
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    int num1, num2, num3;
    fscanf(in,"%d %d %d", &num1, &num2, &num3);
    if (num1 <= 0)
        fprintf(out,"-1");
    else if (num2 <= 0)
        fprintf(out,"-2");
    else if (num3 <= 0)
        fprintf(out,"-3");
    else
        fprintf(out,"%d", num1 * num2 * 2 + num2 * num3 * 2 + num1 * num3 * 2);
    return 0;

    fclose(in);
    fclose(out);
}