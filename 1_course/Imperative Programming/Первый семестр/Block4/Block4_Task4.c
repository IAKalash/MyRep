#include <stdio.h>

int len(char *string) // Длина строки
{
    char sym = ' ';
    int i = 0;
    while (sym != '\0')
    {
        sym = string[i];
        ++i;
    }
    return i - 1;
}

int calcLetters(char *iStr, int *oLowerCnt, int *oUpperCnt, int *oDigitsCnt){
    char x = ' ';
    int i;
    for (i = 0; i < len(iStr); ++i) {
        x = iStr[i];
        if (x >= 'a' && x <= 'z') {
            ++(*oLowerCnt);
        }
        else if (x >= 'A' && x <= 'Z')
        {
            ++(*oUpperCnt);
        }
        else if (x >= '0' && x <= '9')
        {
            ++(*oDigitsCnt);
        }
    }
    return i;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int Line = 1, Upper = 0, Lower = 0, Digits = 0;
    char Str[102] = {0};
    char *fl;

    fl = gets(Str);
    while (fl != NULL) {

        if (fl != NULL) {
            
            int n = calcLetters(Str, &Lower, &Upper, &Digits);
            printf("Line %d has %d chars: %d are letters (%d lower, %d upper), %d are digits.",
               Line, n - 1, Lower + Upper, Lower, Upper, Digits);
            Upper = 0, Lower = 0, Digits = 0, ++Line;
        }
        
        fl = gets(Str);
        if (fl != NULL) {
            printf("\n");
        }
    }

    fclose(stdin);
    fclose(stdout);
    }