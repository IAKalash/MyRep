#include <stdio.h>

void bubble(int els, int *array)
{
    int x;
    for (int i = 0; i < els; ++i)
    {
        for (int j = i + 1; j < els; ++j)
        {
            if (array[i] > array[j])
            {
                x = array[j];
                array[j] = array[i];
                array[i] = x;
            }
        }
    }
}

int main(void)
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int mass[100] = {0}, nums = 0, n;

    fscanf(in, "%d", &nums);

    for (int i = 0; i < nums; ++i) // ввод массива
    {
        fscanf(in, "%d", &n);
        mass[i] = n;
    }

    bubble(nums, mass);

    for (int i = 0; i < nums; ++i){
        fprintf(out, "%d ", mass[i]);
    }

    fclose(in);
    fclose(out);
    }