#include <stdio.h>

void bubble(int els,int *array) {
    int x;
    for (int i = 0; i < els; ++i) {
        for (int j = i + 1; j < els; ++j) {
            if (array[i] > array[j]) {
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

    int A[10001] = {0}, B[10001] = {0}, C[10001] = {0}, a, b, n, count = 0;
    int f1 = 1, f2 = 2, f3 = 3, f4 = 4, f5 = 5;

    fscanf(in, "%d", &a);

    for (int i = 0; i < a; ++i) // ввод массива A
    {
        fscanf(in, "%d", &n);
        A[i] = n;
    }

    fscanf(in, "%d", &b);

    for (int i = 0; i < b; ++i) // ввод массива B
    {
        fscanf(in, "%d", &n);
        B[i] = n;
    }

    for (int i = 0; i < a; ++i) { // проход по А
        n = 0;
        for (int j = 0; j < b; ++j) { // проход по В
            if (A[i] == B[j]) {
                n = 1;
                break;
            }
        }
        for (int j = 0; j < count; ++j) { // проверка на наличие в С
            if (A[i] == C[j]) {
                n = 1;
                break;
            }
        }

        if (n == 0){
            C[count] = A[i];
            ++count;
        }
    }

    bubble(count, C);

    fprintf(out, "%d\n", count);

    for (int i = 0; i < 1000; ++i) {
        if (C[i] != 0)
            fprintf(out, "%d ", C[i]);
    }

    fclose(in);
    fclose(out);
}