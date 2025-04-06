#include <stdio.h>

int main(void)
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int mass[100000] = {0}, num, n, sum;

    fscanf(in, "%d", &num);

    for (int i = 0; i < num; ++i)
    {
        fscanf(in, "%d", &n);
        ++mass[n];
    }

    for (int i = 0; i < 100000; ++i) {
        if (mass[i] != 0) {
            fprintf(out, "%d: %d\n", i, mass[i]);
        }
    }

    fclose(in);
    fclose(out);
}