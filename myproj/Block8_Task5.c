#include <stdio.h>
#include <malloc.h>

typedef struct combination {
    char *data;
    int len;
} sym;

sym* createSym (int len, FILE *in) {
    sym *node = (sym *)malloc(sizeof(sym));
    node->len = len;
    char *data = (char *)malloc(len);
    char byte;

    for (int i = 0; i < len; ++i) {
        fread(&byte, 1, 1, in);
        data[i] = byte;
    }

    node->data = data;
    return node;
}

int main(void)
{
    FILE *in = fopen("1.in", "rb");
    FILE *out = fopen("output.txt", "wb");

    int n, len, txt;
    fread(&n, 4, 1, in);
    sym **arr = (sym **)malloc(sizeof(sym*) * n);

    for (int i = 0; i < n; ++i) {
        fread(&len, 4, 1, in);
        arr[i] = createSym(len, in);
    }

    fread(&txt, 4, 1, in);
    char mask = 0b10000000;

    for (int i = 0; i < txt; ++i) {
        fread(&len, 2, 1, in);
        //вывод по формату из arr
    }

    free(arr);

    fclose(in);
    fclose(out);
}