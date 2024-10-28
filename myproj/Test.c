#include <stdio.h>
#include <string.h>

typedef struct LongNum_s
{
    int len;       // сколько цифр в числе
    int arr[1001]; // массив десятичных цифр числа
} LongNum;

void sum(LongNum *num1, LongNum *num2, LongNum *res)
{
    for (int i = 0; i < num2->len; ++i)
    {
        res->arr[i + 1] = (num1->arr[i] + num2->arr[i] + res->arr[i]) / 10;
        res->arr[i] = (num1->arr[i] + num2->arr[i] + res->arr[i]) % 10;
    }
    res->len = (res->arr[num2->len] && 1) ? num2->len + 1 : num2->len;
}

void mult(LongNum *num, int num2)
{
    int carry = 0, x;
    for (int i = 0; i < num->len; ++i)
    {
        x = num->arr[i] * num2 + carry;
        num->arr[i] = x % 10;
        carry = x / 10;
    }
    int n = 0;
    while (carry >= 1)
    {
        num->arr[num->len + n] = carry % 10;
        ++n;
        carry /= 10;
    }
    num->len += n;
    while (num->arr[num->len] != 0)
    {
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

void longmult(LongNum *num1, LongNum *num2, LongNum *res)
{
    int x = 1;
    for (int i = 0; i < num2->len; ++i)
    {
        LongNum number = *num1;
        printf("%d", num2->arr[i]);
        mult(&number, (num2->arr[i]) * x);
        printstruct(&number);
        printf("\n");
        sum(res, &number, res);
        x *= 10;
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

    for (int i = num1.len; i >= 0; --i)
    {
        j = num1.len - i;
        num1.arr[i] = str[i] - 48;
    }

    mult(&num1, 3);

    printstruct(&num1);

    fclose(stdin);
    fclose(stdout);
}