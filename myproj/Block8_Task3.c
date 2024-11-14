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

file *addfile(file *last, FILE *in, long long A, long long B)
{
    file *node = (file *)malloc(sizeof(file));
    readfile(node, in);

    if (checkfile(node, A, B)) {
        node->next = last->next;
        last->next = node;
        return node;
    }
    return last;
}

void printfiles(file *head, FILE *out)
{
    for (file *node = head; node != NULL; node = node->next)
    {
        writefile(node, out);
    }
}

void sort(file *head) {
    file 
    file *next = head->next;
    while (next != NULL) {
        if (strcmp)
    }
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
    fl1.next = NULL;
    int count = 0;

    for (int i = 0; i < n; ++i) {
        readfile(&fl1, in);
        ++count;
        if (checkfile(&fl1, A, B)) {
            break;
        }
    }

    file *head = &fl1;
    file *last = &fl1;

    for (int i = count; i < n; ++i) {
        last = addfile(last, in, A, B);
    }

    sort(head);

    printfiles(head, out);

    fclose(in);
    fclose(out);
}