#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int peekToken(char *str, char *token, int *adr) {
    int new_adr = *adr;
    while (str[new_adr] == ' ')
        new_adr++;
    *adr = new_adr;
    char sym = str[new_adr];
    if (sym == '\0') {
        token[0] = '\0';
        return 0;
    }
    else if (sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '(' || sym == ')') {
        token[0] = sym;
        token[1] = '\0';
        return 1;
    }
    int i = 0;
    while (str[new_adr + i] >= '0' && str[new_adr + i] <= '9') {
        token[i] = str[new_adr + i];
        i++;
    }
    token[i] = '\0';
    return i;
}

void readToken(char *str, char *token, int *adr) {
    *adr += peekToken(str, token, adr);
}

double expr(char *str, int *adr);

double atom(char *str, int *adr) {
    char token[5] = {0};
    peekToken(str, token, adr);

    if (token[0] == '-') {
        readToken(str, token, adr);
        return -atom(str, adr);
    }
    
    if (token[0] == '(') {
        readToken(str, token, adr);
        double res = expr(str, adr);
        readToken(str, token, adr);
        return res;
    }
    
    readToken(str, token, adr);
    return atof(token);
}

double monome(char *str, int *adr) {
    double res = atom(str, adr);
    char token[5];
    while (1) {
        peekToken(str, token, adr);
        if (token[0] == '*') {
            readToken(str, token, adr);
            double next = atom(str, adr);
            res *= next;
        }
        else if (token[0] == '/') {
            readToken(str, token, adr);
            double next = atom(str, adr);
            res /= next;
        }
        else {
            break;
        }
    }
    return res;
}

double expr(char *str, int *adr) {
    double res = monome(str, adr);
    char token[5];
    while (1) {
        peekToken(str, token, adr);
        if (token[0] == '+') {
            readToken(str, token, adr);
            double next = monome(str, adr);
            res += next;
        }
        else if (token[0] == '-') {
            readToken(str, token, adr);
            double next = monome(str, adr);
            res -= next;
        }
        else {
            break;
        }
    }
    return res;
}

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char *str = (char *)calloc(500001, sizeof(char));
    gets(str);

    int adr = 0;

    char token[5];
    double result = expr(str, &adr);

    printf("%.20lf", result);
    
    free(str);
    fclose(stdin);
    fclose(stdout);
}