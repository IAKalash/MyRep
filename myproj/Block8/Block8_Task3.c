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
    fwrite(&fl->name, 21, 1, out);
    fwrite(&fl->size, 8, 1, out);
    fwrite(&fl->dir, 1, 1, out);
    fwrite(&fl->time, 8, 1, out);
    fwrite(&fl->change, 8, 1, out);
    fwrite(&fl->hid, 1, 1, out);
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

    if (checkfile(node, A, B)) {
        file *next;
        file *curr = NULL;
        for (file *next = head; next != NULL; next = next->next)
        {
            if (strcmp(node->name, next->name) <= 0)
                break;
            else
                curr = next;
        }
        if (curr == NULL) {
            node->next = head;
            return node;
        }
        else if (next == NULL) {
            node->next = NULL;
            curr->next = node;
            return head;
        }
        else {
            node->next = curr->next;
            curr->next = node;
            return head;
        }
    }
    return head;
}

void printfiles(file *head, FILE *out)
{
    for (file *node = head; node != NULL; node = node->next)
    {
        writefile(node, out);
    }
}

int main(void)
{
    FILE *in = fopen("input.txt", "rb");
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

    for (int i = count; i < n; ++i) {
        head = addfile(head, in, A, B);
    }

    printfiles(head, out);

    fclose(in);
    fclose(out);
}