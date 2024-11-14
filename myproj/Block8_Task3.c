#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct file {
    char name[20];
    long long size;
    char dir;
    long long time;
    long long change;
    char hid;
    struct file *next;
} file;

void readfile(file *fl, FILE *in) {
    fread(&fl->name, 21, 1, in);
    fread(&fl->size, 8, 1, in);
    fread(&fl->dir, 1, 1, in);
    fread(&fl->time, 8, 1, in);
    fread(&fl->change, 8, 1, in);
    fread(&fl->hid, 1, 1, in);
    fl->next = NULL;
}

void writefile(file *fl, FILE *out)
{
    fwrite(fl, 47, 1, out);
}

int checkfile(file *fl, long long A, long long B) {
    if (fl->dir == 0) {
        if (fl->hid == 0) {
            if (fl->time >= A) {
                if (fl->change <= B) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

file *addfile(file *head, FILE *in, long long A, long long B)
{
    file *node = (file *)malloc(sizeof(file));
    readfile(node, in);

    file *prev = NULL;
    file *next = head;
    if (checkfile(node, A, B)) {
        while (1)
        {
            if (next == NULL || strcmp(node->name, next->name) < 0) {
                if (prev == NULL) {
                    node->next = next;
                    return node;
                }
                else {
                    prev->next = node;
                    node->next = next;
                    return head;
                }
            }
            else {
                prev = next;
                next = next->next;
            }
        }
    }
}

void printfiles(file *head, FILE *out)
{
    for (file *node = head; node != NULL; node = node->next)
    {
        writefile(node, out);
    }
}

void reverse(int *num)
{
    *num = (*num >> 24 & 0b00000000000000000000000011111111) | (*num << 24 & 0b11111111000000000000000000000000) | (*num >> 8 & 0b00000000000000001111111100000000) | (*num << 8 & 0b00000000111111110000000000000000);
}

void printfile (file *fl) { //TEST!!!!!!!!!!!!!!!!!!!
    printf("!!!!!!!!!!!!!!!!");
    printf("%s\n", fl->name);
}

int main(void)
{
    FILE *in = fopen("1.in", "rb");
    FILE *out = fopen("output.txt", "wb");

    int n;
    long long A, B;

    fread(&n, 4, 1, in);
    fread(&A, 8, 1, in);
    fread(&B, 8, 1, in);

    file fl1;
    fl1.dir = 49;
    int count = 0;

    for (int i = 0; i < n; ++i) {
        readfile(&fl1, in);
        ++count;
        if (checkfile(&fl1, A, B)) {
            break;
        }
    }

    file *head = &fl1;

    for (int i = count; i < n; ++i) {
        head = addfile(head, in, A, B);
    }

    printfiles(head, out);

    fclose(in);
    fclose(out);
}