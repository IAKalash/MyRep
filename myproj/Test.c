#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Расширенный алгоритм Евклида для нахождения НОД и коэффициентов Безу
// Возвращает НОД, а через указатели x и y — коэффициенты: ax + by = НОД(a, b)
int64_t gcd_extended(int64_t a, int64_t b, int64_t *x, int64_t *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int64_t x1, y1;
    int64_t gcd = gcd_extended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

// Нахождение обратного элемента a по модулю m (a * x ≡ 1 (mod m))
int64_t mod_inverse(int64_t a, int64_t m) {
    int64_t x, y;
    int64_t gcd = gcd_extended(a, m, &x, &y);
    if (gcd != 1) {
        return -1; // Обратного элемента не существует
    }
    // Убедимся, что x положительный
    return (x % m + m) % m;
}

// Модульное умножение для больших чисел
int64_t mod_mul(int64_t a, int64_t b, int64_t m) {
    a = a % m;
    b = b % m;
    int64_t res = 0;
    while (b > 0) {
        if (b & 1) {
            res = (res + a) % m;
        }
        a = (a * 2) % m;
        b = b >> 1;
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int k;
    scanf("%d", &k);

    int64_t *M = (int64_t *)malloc(k * sizeof(int64_t));
    int64_t *A = (int64_t *)malloc(k * sizeof(int64_t));

    // Читаем модули
    for (int i = 0; i < k; i++) {
        scanf("%lld", &M[i]);
    }

    // Читаем остатки
    for (int i = 0; i < k; i++) {
        scanf("%lld", &A[i]);
    }

    // Вычисляем общий модуль M
    int64_t M_prod = 1;
    for (int i = 0; i < k; i++) {
        M_prod = mod_mul(M_prod, M[i], 1000000000000000000LL); // Ограничение 10^17
    }

    // Вычисляем X
    int64_t X = 0;
    for (int i = 0; i < k; i++) {
        int64_t P_i = M_prod / M[i]; // Частный модуль
        int64_t Q_i = mod_inverse(P_i, M[i]); // Обратный элемент
        int64_t term = mod_mul(A[i], P_i, M_prod); // A_i * P_i
        term = mod_mul(term, Q_i, M_prod); // A_i * P_i * Q_i
        X = (X + term) % M_prod;
    }

    // Выводим минимальное неотрицательное X
    printf("%lld\n", X);

    free(M);
    free(A);
    fclose(stdin);
    fclose(stdout);
    return 0;
}