#include <stdio.h>
#include <malloc.h>

int read(FILE *in, int size) {
    int type, count = 2;
    fread(&type, 1, 1, in);
    char sym = 0;
    printf("    \"");
    fread(&sym, 1, 1, in);
    do {
        printf("%c", sym);
        ++count;
        fread(&sym, 1, 1, in);
    } while (sym != 0);
    printf("\": ");
    if (type == 1) {       //double
        double num;
        fread(&num, 8, 1, in);
        printf("%0.15g", num);
        count += 8;
    }
    else if (type == 2) {  //string
        int len;
        fread(&len, 4, 1, in);
        printf("\"");
        char *str = (char *)malloc(len);
        fread(str, len, 1, in);
        printf("%s", str);
        printf("\"");
        count += len + 4;
        free(str);
    }
    else if (type == 8) {  //bool
        fread(&sym, 1, 1, in);
        (sym == 1) ? printf("true") : printf("false");
        ++count;
    }
    else if (type == 10) { //null
        printf("null");
    }
    else if (type == 16) { //int32
        int num;
        fread(&num, 4, 1, in);
        printf("%d", num);
        count += 4;
    }
    else {                 //int64
        long long num;
        fread(&num, 8, 1, in);
        printf("%lld", num);
        count += 8;
    }
    if (size != count)
        printf(",");
    return count;
}

int main(void)
{
    FILE *in = fopen("1.in", "rb");
    freopen("output.txt", "w", stdout);

    int size;
    fread(&size, 4, 1, in);
    size -= 5;

    printf("{\n");

    while (size != 0) {
        size -= read(in, size);
        printf("\n");
    }

    printf("}");

    fclose(in);
    fclose(stdout);
}