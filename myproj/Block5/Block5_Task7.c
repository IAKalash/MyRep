#include <stdio.h>
#include <string.h>

typedef struct LongNum_s
{
    int len;      // сколько цифр в числе
    int arr[1001]; // массив десятичных цифр числа
} LongNum;

void sum(LongNum *num1, LongNum *num2, LongNum *res)
{
    int x = 0;
    for (int i = 0; i < num2->len; ++i)
    {
        x = (num1->arr[i] + num2->arr[i] + res->arr[i]);
        res->arr[i + 1] = x / 10;
        res->arr[i] = x % 10;
    }
    if (num1->len < num2->len) {
        res->len = (res->arr[num2->len] && 1) ? num2->len + 1 : num2->len;
    }
    else {
        res->len = (res->arr[num1->len] && 1) ? num1->len + 1 : num1->len;
    }
}

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

void printstruct(LongNum *num)
{
    for (int i = num->len - 1; i >= 0; --i)
    {
        printf("%d", num->arr[i]);
    }
}

void longmult(LongNum *num1, LongNum *num2, LongNum *res) {
    int x = 0;
    for (int i = 0; i < num2->len; ++i) {
        LongNum number = *num1;
        LongNum res1 = *res;
        LongNum n;
        res->arr[0] = 0;
        mult(&number, num2->arr[i]);
        for (int i = 0; i < number.len; ++i) {
            n.arr[i + x] = number.arr[i];
            n.arr[i] = i < x ? 0 : n.arr[i];
        }
        n.len = number.len + x;
        sum(&res1, &n, res);
        x += 1;
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    LongNum num1, num2, res;
    int j;
    char str[1000] = {0};

    for (int i = 0; i < 1000; ++i)
    {
        num1.arr[i] = 0;
        num2.arr[i] = 0;
        res.arr[i] = 0;
    }

    gets(str);

    num1.len = strlen(str);

    for (int i = num1.len; i > 0; --i) {
        j = num1.len - i;
        num1.arr[i - 1] = str[j] - 48;
    }

    gets(str);

    num2.len = strlen(str);

    for (int i = num2.len; i > 0; --i) {
        j = num2.len - i;
        num2.arr[i - 1] = str[j] - 48;
    }

    longmult(&num1, &num2, &res);

    printstruct(&res);
    printf("\n");

    fclose(stdin);
    fclose(stdout);
}