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

void splWords(char *iStr){
    int Upper = 0, Lower = 0, fl = 0, i = 0;
    char x;
    for (i = 0; i < len(iStr); ++i) {
        x = iStr[i];
        if (x >= 'a' && x <= 'z') {
            ++Lower;
            fl = 1;
        }
        else if (x >= 'A' && x <= 'Z') {
            ++Upper;
            fl = 1;
        }
        else {
            if (fl == 1) {
                printf("%d/%d ", Upper, Lower + Upper);
                for (int j = i - Lower - Upper; j < i; ++j) {
                    printf("%c",iStr[j]);
                }
                printf("\n");
            }
            fl = 0, Upper = 0, Lower = 0;
        }

    }
    if (fl == 1) {
        printf("%d/%d ", Upper, Lower + Upper);
        for (int j = i - Lower - Upper; j < i; ++j)
        {
            printf("%c", iStr[j]);
        }
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    
    char Str[1000001] = {0};

    gets(Str);
    splWords(Str);

    fclose(stdin);
    fclose(stdout);
    }