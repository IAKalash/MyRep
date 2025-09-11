#include <stdio.h>

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int Hash[128] = {0}, max = 0;
    char sym, S[100000] = {'#'};

    do {
        sym = getchar();
        ++Hash[sym];
    } while (sym != EOF);

    for (int i = 0; i < 127; ++i) {
        if (Hash[i] != 0) {
            max = i;
        }
    }

    for (int i = 32; i <= 126; ++i)
        {
            if (Hash[i] != 0)
            {
                printf("%c %.*s", i, Hash[i], "################################################################################################");
                if (i != max)
                {
                    printf("\n");
                }
            }
            
        }

    fclose(stdin);
    fclose(stdout);
}