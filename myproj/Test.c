
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long CharToLL (char *str) {
    int st = 1;
    long long res = 0;
    for (int i = strlen(str) - 1; i >= 0; --i) {
        res += (str[i] - '0') * st;
        st *= 10;
    }
    return res;
}

int main(void) {
    char num[20] = "17345";
    printf("%lld", CharToLL(num));
}
