#include <stdio.h>
#include <math.h>

// Структура для хранения коэффициентов многочлена и границ спана
typedef struct {
    double l, r;          // Границы спана [l, r]
    double x[4], y[4], z[4]; // Коэффициенты для x(t), y(t), z(t): c0, c1, c2, c3
} Span;

// Производная многочлена p(t) = c0 + c1(t-l) + c2(t-l)^2 + c3(t-l)^3
double derivative(double t, double l, double c[4]) {
    double u = t - l;
    return c[1] + 2 * c[2] * u + 3 * c[3] * u * u;
}

// Подынтегральная функция: sqrt(dx/dt^2 + dy/dt^2 + dz/dt^2)
double integrand(double t, Span span) {
    double dx = derivative(t, span.l, span.x);
    double dy = derivative(t, span.l, span.y);
    double dz = derivative(t, span.l, span.z);
    return sqrt(dx * dx + dy * dy + dz * dz);
}

// Правило Симпсона для численного интегрирования
double simpson(double a, double b, int n, Span span) {
    if (n % 2 != 0) {
        printf("Ошибка: n должно быть чётным!\n");
        return 0.0;
    }
    double h = (b - a) / n;
    double sum = integrand(a, span) + integrand(b, span);

    for (int i = 1; i < n; i++) {
        double t = a + i * h;
        sum += (i % 2 == 0) ? 2 * integrand(t, span) : 4 * integrand(t, span);
    }
    return sum * h / 3.0;
}

int main() {
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    if (!fin || !fout) {
        printf("Ошибка открытия файлов\n");
        return 1;
    }

    int N;
    fscanf(fin, "%d", &N);
    Span spans[1000]; // Максимум 1000 спанов

    // Чтение данных
    for (int i = 0; i < N; i++) {
        fscanf(fin, "%lf %lf", &spans[i].l, &spans[i].r);
        for (int j = 0; j < 4; j++) fscanf(fin, "%lf", &spans[i].x[j]);
        for (int j = 0; j < 4; j++) fscanf(fin, "%lf", &spans[i].y[j]);
        for (int j = 0; j < 4; j++) fscanf(fin, "%lf", &spans[i].z[j]);
    }

    // Вычисление общей длины
    double total_length = 0.0;
    int n = 100; // Число разбиений для правила Симпсона (чётное)
    for (int i = 0; i < N; i++) {
        total_length += simpson(spans[i].l, spans[i].r, n, spans[i]);
    }

    // Вывод результата с высокой точностью
    fprintf(fout, "%.20f\n", total_length);

    fclose(fin);
    fclose(fout);
    return 0;
}