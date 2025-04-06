#include <stdio.h>

int main(void)
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt","w");

    int count = 1,num1,num2;

    fscanf(in, "%d %d", &num1, &num2);

    if (num1 > 0){
        fprintf(out, "%d", num1 / num2);
        fprintf(out, " %d", num1 / num2 + (1 && (num1 % num2)));
        fprintf(out, " %d", num1 / num2);
        fprintf(out, " %d", num1 % num2);
    }
    else if (num1 < 0){
        fprintf(out, "%d", num1 / num2 - (1 && (num1 % num2)));
        fprintf(out, " %d", num1 / num2);
        fprintf(out, " %d", num1 / num2);
        if ((num1 % num2) != 0){
            fprintf(out, " %d", num1 % num2 + num2);
        }
        else {
            fprintf(out, " %d", num1 % num2);
        }
    }
    else {
        fprintf(out, "%d", 0);
        fprintf(out, " %d", 0);
        fprintf(out, " %d", 0);
        fprintf(out, " %d", 0);
    }
    
    fclose(in);
    fclose(out);
}