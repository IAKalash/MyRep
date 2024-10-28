#include <stdio.h>

int Isalpha(char let) {
    return (let >= 'A' && let <= 'Z') || (let >= 'a' && let <= 'z');
}

int Not (int fl) {
    return (fl == 1) ? 0 : 1;
}

int main(void)
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int count = 0;
    char sym = '.', sym0 = '.', stat;
    
    do
    {
        stat = fscanf(in, "%c", &sym);
        if (Isalpha(sym0) && Not(Isalpha(sym))) 
        {
            count += 1;
        }
        sym0 = sym;
    } while (stat != EOF);

    fprintf(out, "%d", count);

    fclose(in);
    fclose(out);
}
