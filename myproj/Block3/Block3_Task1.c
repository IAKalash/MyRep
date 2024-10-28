#include <stdio.h>

int main(void)
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int mass[100] = {0}, num, n, sum;

    fscanf(in, "%d", &num);
    
    for (int i = 0; i < num; ++i) {
        fscanf(in, "%d", &n);
        mass[i] = n;
    }

    for (int i = 0; i < num; ++i) {
        sum = 0;
        for (int k = i; k < num; ++k) {
            if (mass[i] > mass[k]) {
                ++sum;
            }
        }
        fprintf(out, "%d", sum);
        if (i != num - 1) {
            fprintf(out, " ");
        }
        else if (i == num - 1) {
            fprintf(out, "\n");
        }
    }

    fclose(in);
    fclose(out);
}