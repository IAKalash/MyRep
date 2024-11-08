#include <stdio.h>

// какой-нибудь целочисленный тип (желательно беззнаковый)
typedef unsigned long long bitword;
// инициализирует массив битов длины num, устанавливая все его биты в ноль
void bitsetZero(bitword *arr, int num) {

}
// возвращает значение idx-ого бита (0 или 1)
int bitsetGet(const bitword *arr, int idx) {

}
// устанавливает значение idx-ого бита в newval (которое равно 0 или 1)
void bitsetSet(bitword *arr, int idx, int newval) {

}
// возвращает 1, если среди битов с номерами k
// для left <= k < right есть единичный, и 0 иначе
int bitsetAny(const bitword *arr, int left, int right) {

}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, op, idx, newval;

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &op, &idx);
        if (op == 0) {
            bitsetZero();
        }
        else if (op == 1) {
            bitsetGet();
        }
        else if (op == 2) {
            scanf(" %d", &newval);
            bitsetSet();
        }
        else {
            scanf(" %d", &newval);
            bitsetAny();
        }
    }

    fclose(stdin);
    fclose(stdout);
}
