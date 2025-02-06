#include <stdio.h>

int main(void)
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int num = 0;
    long long res = 0;

    fscanf(in, "%d", &num);

    for (int a = 1; a * a * a <= num; ++a){
        for (int b = a; a * b * b <= num; ++b){
            res += num / (a * b) - b + 1;
        }
    }

    fprintf(out, "%lld",res);

    fclose(in);
    fclose(out);
}