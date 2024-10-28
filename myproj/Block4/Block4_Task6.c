#include <stdio.h>

int readTime(char *iStr, int *oHours, int *oMinutes, int *oSeconds)
{
    if (sscanf(iStr, "%d:%d:%d", oHours, oMinutes, oSeconds) != 1) {
        if (*oHours < 24 && *oHours >= 0 && *oMinutes >= 0 && 
            *oMinutes < 60 && *oSeconds >= 0 && *oSeconds < 60) {
            return 1;
        }
        else {
            *oHours = -1, *oMinutes = -1, *oSeconds = -1;
            return 0;
        }
    }
    else
    {
        *oHours = -1, *oMinutes = -1, *oSeconds = -1;
        return 0;
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int Hours = 0, Minutes = 0, Seconds = 0;
    char Str[16] = {0};

    gets(Str);
    if (readTime(Str, &Hours, &Minutes, &Seconds) == 1) {
        printf("1 %d %d %d\n", Hours, Minutes, Seconds);
        printf("1 %d %d\n", Hours, Minutes);
        printf("1 %d", Hours);
    }
    else {
        printf("0 %d %d %d\n", Hours, Minutes, Seconds);
        printf("0 %d %d\n", Hours, Minutes);
        printf("0 %d", Hours);
    }

    fclose(stdin);
    fclose(stdout);
}