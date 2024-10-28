#include <stdio.h>
#include <stdlib.h>



int main(void)
{
    FILE *out = fopen("output.txt", "w");
    for (int i = 0; i < 1000; ++i) {
        fprintf(out, "%d %d\n", rand()%1000, rand()%10000);
    }
}