#include <stdio.h>

int main(void)
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    char a, b;

    fscanf(in, "%c%c", &a, &b);

    if (a == 'M' && b == 'o'){
        fprintf(out, "%d", 1);
    }

    else if (a == 'T' && b == 'u'){
        fprintf(out, "%d", 2);
    }

    else if (a == 'W' && b == 'e'){
        fprintf(out, "%d", 3);
    }

    else if (a == 'T' && b == 'h'){
        fprintf(out, "%d", 4);
    }

    else if (a == 'F' && b == 'r'){
        fprintf(out, "%d", 5);
    }

    else if (a == 'S' && b == 'a'){
        fprintf(out, "%d", 6);
    }

    else if (a == 'S' && b == 'u'){
        fprintf(out, "%d", 7);
    }

    fclose(in);
    fclose(out);
}


