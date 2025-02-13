#include <stdio.h>
#include <malloc.h>

long long fact (long long num) {
    if (num == 0 || num == 1) {
        return 1;
    }
    else {
        return (num * fact(num - 1) % 1000000007);
    }
}

long long bin(int n, int k) {
    
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int tests;
    int n, k;

    scanf("%d", &tests);

    for (int i = 0; i < tests; ++i) {
        scanf("%d %d", &n, &k);
        printf("%lld\n", bin(n,k));
    }

    fclose(stdin);
    fclose(stdout);
}