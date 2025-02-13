#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long CharToLL (char *str) {
    int st = 1;
    long long res = 0;
    for (int i = strlen(str) - 1; i >= 0; --i) {
        res += (str[i] - '0') * st;
        st *= 10;
    }
    return res;
} 

long long func(char* n10, char* n20, char command[4], char* mod0) {
    long long res;
    long long n1 = CharToLL(n10);
    long long n2 = CharToLL(n20);
    if (mod0 == NULL) {
        if (strcmp(command, "add") == 0) {
            res = n1 + n2;
        }
        else if (strcmp(command, "sub") == 0) {
            res = n1 - n2;
        }
        else {
            res = n1 * n2;
        }
    }
    else {
        long long mod = CharToLL(mod0);
        if (strcmp(command, "add") == 0) {
            res = (n1 % mod + n2 % mod) % mod;
        }
        else if (strcmp(command, "sub") == 0) {
            res = (n1 % mod - n2 % mod + mod) % mod;
        }
        else {
            res = (n1 % mod) * (n2 % mod) % mod;
        }
    }
    return res;
}

int main(int argc, char* argv[])
{
    if (argc <= 1) {
		fprintf(stderr, "No parameters specified.\n");
		return 13;
	}
    else if (argc == 4) {
        printf ("%lld", func(argv[2], argv[3], argv[1], NULL));
    }
    else if (strcmp(argv[1], "-m") == 0) {
        printf("%lld", func(argv[4], argv[5], argv[3], argv[2]));
    }
    else{
        printf("%lld", func(argv[2], argv[3], argv[1], argv[5]));
    }
    return 0;
}