#include <stdio.h>
#pragma warning (disable:4996)

int main(void)
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt","w");

    int count,num;

    fscanf(in, "%d", &num);
    if (num == 1) {
        fprintf(out, "NO");
        return 0;
    }
    for (count = 2; count < num; count++) {
        if (num % count == 0) {
            fprintf(out, "NO");
            return 1;
        }
    }
    fprintf(out, "YES");
    

    fclose(in);
    fclose(out);
}