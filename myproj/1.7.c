#include <stdio.h>

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    

    fclose(stdin);
    fclose(stdout);
}