#include <stdio.h>
#pragma warning(disable:4996)
int main(void)
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    int num, res, finish;
    fscanf(in,"%d", &finish);
    num = 0, res = 0;
    while (num++ < finish) {
        res = res + num;
    }
    fprintf(out,"%d", res);
    return 0;

    fclose(in);
    fclose(out);
}