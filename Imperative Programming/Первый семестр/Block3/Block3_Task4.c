#include <stdio.h>

int main(void)
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int mass[5000] = {0}, num, n, sum = 0, max = -10000, L, R;

    fscanf(in, "%d", &num);

    for (int i = 0; i < num; ++i)
    {
        fscanf(in, "%d", &n);
        mass[i] = n;
    }

    for (int i = 0; i < num; ++i) {
        sum = 0;
        for (int k = i; k < num; ++k) {
            sum += mass[k];
            n = k;
        
            if (sum > max) {
                max = sum;
                L = i;
                R = n;
            }
        }
    }

    fprintf(out, "%d %d %d\n", L, R, max);

    fclose(in);
    fclose(out);
}