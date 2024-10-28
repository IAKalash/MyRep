#include <stdio.h>

int main(void)
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    int n, fl = 1;

    fscanf(in, "%d", &n);
    for (int i = 2; i <= n; i++) {
        fl = 1;
        for (int d = 2; d < i; d++) {
            if (i % d == 0) {
                fl = 0;
                break;
            }
        }
        if (fl == 1) {
            fprintf(out, "%d\n", i);
        }
    }

    fclose(in);
    fclose(out);
}

