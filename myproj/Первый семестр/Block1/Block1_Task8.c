#include <stdio.h>
#pragma warning(disable:4996)
int main(void)
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    int H, M, S, K, x;
    fscanf(in, "%d %d %d %d", &H, &M, &S, &K);
    H = (H + (K + S + M * 60) / 3600) % 24;
    M = (M + (K + S) % 3600 / 60) % 60;
    S = (S + K % 60) % 60;

    fprintf(out, "%d %d %d", H, M, S);

    fclose(in);
    fclose(out);
}