#include <stdio.h>

double sinus(double num) {
    double res = 0, x = num, x2 = num * num;
    int fact = 1;

    for (int i = 3; i <= 19; i += 2) {
        res += x / fact;
        x *= x2 * -1;
        fact *= i * (i - 1);
    }
    return res;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    double num;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%lf", &num);
        printf("%0.15lf\n",sinus(num));
    }
    
    fclose(stdin);
    fclose(stdout);
}