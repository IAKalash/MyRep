#include <stdio.h>

int pow(int base, int power)
{
    if (power == 0)
    {
        return 1;
    }
    else
    {
        return base * pow(base, power - 1);
    }
}

int main(void)
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    int binnum = 0, len, nums[12501], lennum;
    char num[100001];

    fscanf(in,"%d %s", &len,&num);

    lennum = len / 8 + (1 && len % 8);

    for (int count = 0; count < lennum; ++count){
        if (count == lennum - 1 && len % 8 != 0){
            binnum = 0;
            for (int i = 0; i < len % 8; ++i){
                binnum += (num[i + 8 * count] - '0') * pow(2, i);
            }
        }
        else {
            binnum = (num[8 * count] - '0') + (num[1 + 8 * count] - '0') * 2 + 
                     (num[2 + 8 * count] - '0') * 4 + (num[3 + 8 * count] - '0') * 8 +
                     (num[4 + 8 * count] - '0') * 16 + (num[5 + 8 * count] - '0') * 32 + 
                     (num[6 + 8 * count] - '0') * 64 + (num[7 + 8 * count] - '0') * 128;
        }
       nums[count] = binnum;
        }

    for (int i = 0; i < lennum; ++i)
    {
        fprintf(out,"%d ", nums[i]);
    }

    fclose(in);
    fclose(out);
}