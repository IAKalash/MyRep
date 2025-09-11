#include <stdio.h>
#include <stdlib.h>
// #include "func.c"

extern double Function (double x);

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int M;
    double delta = 0.0000001, p;
    scanf ("%d", &M);

    for (int i = 0; i < M; ++i) {
        scanf ("%lf", &p);
        if (p >= 0.5) {
            printf("%0.10g\n", (Function(p) - Function(p - delta)) / delta);
        }
        else {
            printf("%0.10g\n", (Function(p + delta) - Function(p)) / delta);
        }
    }

    fclose(stdin);
    fclose(stdout);
}