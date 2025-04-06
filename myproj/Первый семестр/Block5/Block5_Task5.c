#include <stdio.h>
#include <malloc.h>

typedef struct LongNum_s
{
    int len;      // сколько цифр в числе
    int arr[500]; // массив десятичных цифр числа
} LongNum;

void sum(LongNum *num1, LongNum *num2, LongNum *res) {
    for (int i = 0; i < num2->len; ++i) {
        res->arr[i + 1] = (num1->arr[i] + num2->arr[i] + res->arr[i]) / 10;
        res->arr[i] = (num1->arr[i] + num2->arr[i] + res->arr[i]) % 10;
    }
    res->len = (res->arr[num2->len] && 1) ? num2->len + 1 : num2->len;
}

void printstruct(LongNum *num) {
    for (int i = num->len - 1; i >= 0; --i) {
        printf("%d", num->arr[i]);
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;

    scanf("%d", &n);

    LongNum *num = (LongNum *)malloc(sizeof(LongNum) * (n + 1));

    num[0].arr[0] = 1;
    num[0].len = 1;
    num[1].arr[0] = 1;
    num[1].len = 1;

    for (int i = 2; i < n + 1; ++i) {
        sum(&num[i - 2], &num[i - 1], &num[i]);
    }

    printstruct(&num[n - 1]);

    free(num);

    fclose(stdin);
    fclose(stdout);
}