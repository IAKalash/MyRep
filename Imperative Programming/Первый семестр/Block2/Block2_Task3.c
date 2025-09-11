#include <stdio.h>

int main(void)
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    int num = 0, x = 0;
    double num1 = 0.0, num0 = 0.0, negnum = 0.0;

    fscanf(in, "%d", &num);
    for (int i = 0; i < num; ++i) {
        fscanf(in, "%d", &x);
        if (x > 0) {
            num1 += 1;
        }
        else if (x == 0) {
            num0 += 1;
        }
        else if (x < 0) {
            negnum += 1;
        }
    }
    fprintf(out, "%0.15lf %0.15lf %0.15lf", negnum / num, num0 / num, num1 / num);

    fclose(in);
    fclose(out);
}

