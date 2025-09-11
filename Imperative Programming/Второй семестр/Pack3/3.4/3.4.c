#include <stdio.h>
#include <math.h>

#define parts 100

double derivative(double *x, double t, double l) {
    double u = t - l;
    return (x[1] + 2 * x[2] * u + 3 * x[3] * u * u);
}

double integrate(double t, double *x, double *y, double *z, double l) {
    return sqrt(pow(derivative(x, t, l), 2) + pow(derivative(y, t, l), 2) + pow(derivative(z, t, l), 2));
}

double simpson(double *x, double *y, double *z, double l, double r) {
    double h = (r - l) / parts;
    double res = integrate(l, x, y, z, l) + integrate(r, x, y, z, l);
    for (int i = 1; i < parts; i++) {
        double t = l + i * h;
        res += (i % 2 == 0) ? 2 * integrate(t, x, y, z, l) : 4 * integrate(t, x, y, z, l);
    }
    return res * h / 3;
}

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    double l, r, res = 0;
    double x[4], y[4], z[4];
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%lf %lf", &l, &r);
        scanf("%lf %lf %lf %lf", &x[0], &x[1], &x[2], &x[3]);
        scanf("%lf %lf %lf %lf", &y[0], &y[1], &y[2], &y[3]);
        scanf("%lf %lf %lf %lf", &z[0], &z[1], &z[2], &z[3]);
        res += simpson(x, y, z, l, r);
    }

    printf("%0.20f", res);
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}