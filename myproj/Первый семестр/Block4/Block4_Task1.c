#include <stdio.h>

void printTime(int h, int m, int s) {
    printf("%02d:%02d:%02d\n", h, m, s);
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, h, m, s;

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &h, &m, &s);
        printTime(h, m, s);
    }

    fclose(stdin);
    fclose(stdout);
}