#include <stdio.h>
#include <malloc.h>

// какой-нибудь целочисленный тип (желательно беззнаковый)
typedef unsigned short bitword;
// инициализирует массив битов длины num, устанавливая все его биты в ноль
bitword *bitsetZero(bitword *arr, int num) {
    free(arr);
    bitword *arr2 = (bitword *)malloc(sizeof(bitword) * (num / 8 / sizeof(bitword) + 1));
    for (int i = 0; i < num / 8; ++i) {
        arr2[i] = 0;
    }
    return arr2;
}
// возвращает значение idx-ого бита (0 или 1)
int bitsetGet(bitword *arr, int idx) {
    bitword mask = 0b1000000000000000;
    mask >>= (idx % 16);
    mask &= arr[idx / 16];
    if (mask) {
        return 1;
    }
    else {
        return 0;
    }
}
// устанавливает значение idx-ого бита в newval (которое равно 0 или 1)
void bitsetSet(bitword *arr, int idx, int newval) {
    bitword mask = 0b1000000000000000;
    mask >>= (idx % 16);
    if (newval == 1) {
        arr[idx / 16] |= mask;
    }
    else {
        arr[idx / 16] &= ~mask;
    }
}
// возвращает 1, если среди битов с номерами k
// для left <= k < right есть единичный, и 0 иначе
int bitsetAny(const bitword *arr, int left, int right) {
    bitword maskl = 0b1111111111111111;
    bitword maskm = 0b1111111111111111;
    bitword maskr = 0b1111111111111111;
    maskl >>= (left % 16);
    maskr <<= (17 - right % 16);
    if (left / 16 == right / 16) {
        if (arr[left / 16] & maskl & maskr)
            return 1;
        else
            return 0;
    }
    else {
        maskl &= arr[left / 16];
        maskr &= arr[right / 16];
        if (right / 16 - left / 16 == 1)
            maskm = 0;
        for (int i = left / 16 + 1; i < right / 16; ++i) {
            if (maskm &= arr[i])
                break;
        }
        if (maskl | maskm | maskr)
            return 1;
        else
            return 0;
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, op, idx, newval;
    bitword *arr = NULL;

    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &op, &idx);
        if (op == 0) {
            arr = bitsetZero(arr, idx);
        }
        else if (op == 1) {
            printf("%d\n", bitsetGet(arr, idx));
        }
        else if (op == 2) {
            scanf(" %d", &newval);
            bitsetSet(arr, idx, newval);
        }
        else {
            scanf(" %d", &newval);
            if (bitsetAny(arr, idx, newval)) {
                printf("some\n");
            }
            else {
                printf("none\n");
            }
        }
    }

    free(arr);

    fclose(stdin);
    fclose(stdout);
}
