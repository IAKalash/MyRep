#include <stdio.h>

int main(void)
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int mass[10000] = {0}, razmer = 0, pairs = 0, n;
    int f1 = 1, f2 = 2, f3 = 3, f4 = 4, f5 = 5;

    fscanf(in, "%d %d", &razmer, &pairs);

    for (int i = 0; i < pairs * 2; ++i) // ввод массива
    {
        fscanf(in, "%d", &n);
        mass[i] = n;
    }

    if (pairs == 0 || razmer == 0)
    {
        fprintf(out, "0");
        return 0;
    }

    for (int i = 0; i <= pairs * 2; i += 2) // проход по Х
    {
        for (int k = i + 2; k <= pairs * 2; k += 2) // проход по Х следующей пары и далее
        {
            if (mass[i] == mass[k]) // проверка на функцию (выход)
            {
                fprintf(out, "0");
                f1 = 0;
                return 1;
            }
            if (mass[i + 1] == mass[k + 1]) // проход по Y, 3 условие
            {
                f3 = 0;
            }
        }
    }

    if (f1 == 0) {
        fprintf(out, "0");
        return 0;
    }

        if (razmer > pairs)
        {
            f2 = 0;
            f4 = 0;
        }
        else
        {
            for (int P = 1; P <= razmer; ++P) // проход по N
            {
                for (int i = 0; i <= pairs * 2; i += 2) // проход по Х
                {
                    if (P == mass[i])
                    {
                        f2 = 2;
                        break;
                    }
                    else
                        f2 = 0;
                }
            }

            for (int P = 1; P <= razmer; ++P)
            {
                for (int i = 1; i <= pairs * 2; i += 2) // проход по Y
                {
                    if (P == mass[i])
                    {
                        f4 = 4;
                        break;
                    }
                    else
                        f4 = 0;
                }
                if (f4 == 0)
                {
                    break;
                }
            }
        }

        if (f1 == 1)
        { // вывод
            fprintf(out, "%d", f1);
            if (f2 == 2)
            {
                fprintf(out, " %d", f2);
            }
            if (f3 == 3)
            {
                fprintf(out, " %d", f3);
            }
            if (f4 == 4)
            {
                fprintf(out, " %d", f4);
            }
            if (f3 == 3 && f4 == 4)
            {
                fprintf(out, " %d", f5);
            }
        }

        fclose(in);
        fclose(out);
    }