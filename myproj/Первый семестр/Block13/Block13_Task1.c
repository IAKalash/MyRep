#include <stdio.h>

double exp(double num) {
    if (num < 0) {
        return (1.0 / exp(-num));
    }

    double tailor = 1.0;  
    double res = 1.0;  
    int i = 1; 
    
    while (tailor > 1e-14) {
        tailor *= num;
        tailor /= i;  
        res += tailor; 
        ++i;
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
        printf("%0.15g\n", exp(num));
    }

    fclose(stdin);
    fclose(stdout);
}
