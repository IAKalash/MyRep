#include <stdint.h>

extern long long *arr;
//выполнить подготовку массива: запускается один раз перед запусками Sum
//здесь arr[0..n) –- это массив A из входного файла
void Init (long long *arr, int n) {
    for (int i = 1; i < n; ++i) {
        arr[i] += arr[i-1];
    }
}
//найти сумму элементов A на отрезке [l..r)
//использует данные, посчитанные функцией Init
int64_t Sum(int l, int r) {
    return(l == 0 ? arr[r - 1] : arr[r-1] - arr[l - 1]);
}