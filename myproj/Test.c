#include <stdio.h>
#include <string.h>

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    long long int x = 1111111111111111, y = 11111111;

    printf("%lld %lld %llx", x, y, x & y);

    fclose(stdin);
    fclose(stdout);
}