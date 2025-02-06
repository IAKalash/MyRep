#include <stdio.h>

int main(void)
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt","w");

    int len, count, min = 100000, max = -100000, num_min, num_max, innum;

    fscanf(in, "%d", &len);

    for (count = 1; count <= len; count++){
        fscanf(in,"%d", &innum);
        if (innum < min) {
            min = innum;
            num_min = count;
        }
        if (innum > max){
            max = innum;
            num_max = count;
        }
    }
    fprintf(out, "%d %d %d %d", min, num_min, max, num_max);
    

    fclose(in);
    fclose(out);
}