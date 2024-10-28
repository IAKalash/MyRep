#include <stdio.h>

int Isalpha(char let){ 
    return (let >= 'A' && let <= 'Z') || (let >= 'a' && let <= 'z');
}

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

int len(char *string) // Длина строки
{
    char sym = ' ';
    int i = 0;
    while (sym != '\0')
    {
        sym = string[i];
        ++i;
    }
    return i - 1;
}

int main(void)
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int sys, nsys, n, power = 0, sum = 0, i = 0, num, lenght;
    char res[30] = {0}, nums[20] = {0};

    fscanf(in, "%d %d %s", &sys, &nsys, &nums);
    lenght = len(nums);

    while (lenght != 0) // перевод в десятичную
    {
        num = nums[lenght - 1];
        nums[lenght - 1] = 0;
        lenght -= 1;

        if (Isalpha(num) == 1)
        {
            num -= 87;
        }
        else
            num -= 48;

        sum += num * pow(sys, power);
        ++power;
    }
    num = sum;

    while (num >= nsys){ //перевод в n-ную 
        n = num % nsys;
        res[i] = n;
        i++;
        num /= nsys;
    }
    res[i] = num;

    for (int x = i; x >= 0; --x) {
        if (res[x] > 9) {
            fprintf(out, "%c", res[x] + 87);
        }
        else {
            fprintf(out, "%d", res[x]);
        }
    }

    fclose(in);
    fclose(out);
    }