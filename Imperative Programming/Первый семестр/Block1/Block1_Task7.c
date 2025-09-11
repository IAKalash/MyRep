#include <stdio.h>

int main(void)
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int flat, flat1, podezd, floor, floor_num, podezd_num,n,x;

    fscanf(in, "%d %d %d %d %d", &flat, &flat1, &podezd, &floor, &floor_num);

    x = flat1 / (floor_num * (podezd - 1) + floor) + (1 && flat1 % (floor_num * (podezd - 1) + floor));
    n = flat / x + (1 && flat % x);

    fprintf(out, "%d %d", n / floor_num + (1 && n % floor_num), (n - 1) % floor_num + 1);

    fclose(in);
    fclose(out);
}