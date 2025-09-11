#include <stdio.h>

int main(void)
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int min,max,els,maxd,maxels,res = 0;

    fscanf(in,"%d %d %d", &min, &max, &els);

    maxels = (max - min + 1);
    maxd = (maxels - els) / (els - 1) + 1;

    for (int n = 1; n <= maxd; ++n){
        if (maxels >= els * n){
            res += n;
        } 
        else {
            for (int i = n - 2; i >= 0; --i){
                if (maxels == els + (els - 1) * (n - 1) + i) {
                    res += i + 1;
                    break;
                }
            }
        }
    }

    fprintf(out,"%d", res);

    fclose(in);
    fclose(out);
}
