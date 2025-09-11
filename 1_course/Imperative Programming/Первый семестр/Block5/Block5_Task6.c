#include <stdio.h>

typedef struct LongNum_s
{
    int len;      // сколько цифр в числе
    int arr[3000]; // массив десятичных цифр числа
} LongNum;


void mult(LongNum *num, int num2) {
    int carry = 0, x;
    for (int i = 0; i < num->len; ++i) {
        x = num->arr[i] * num2 + carry;
        num->arr[i] = x % 10;
        carry = x / 10;
    }
    int n = 0;
    while (carry >= 1) {
        num->arr[num->len + n] = carry % 10;
        ++n;
        carry /= 10;
    }
    num->len += n;
    while (num->arr[num->len] != 0) {
        ++num->len;
    }
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

    LongNum num;
    
    for (int i = 0; i < 3000; ++i) {
        num.arr[i] = 0;
    }

    num.arr[0] = 1;
    num.len = 1;

    for (int k = 2; k < n + 1; ++k)
    {
        mult(&num, k);
    }

    printstruct(&num);

    fclose(stdin);
    fclose(stdout);
}