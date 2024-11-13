#include <stdio.h>
#include <malloc.h>

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

file *addfile(file *head, FILE *in)
{
    file *node = (file *)malloc(sizeof(file));
    readfile(node, in);

    file *prev = NULL;
    file *next = head;

    while (1)
    {
        if (next == NULL) //|| node->key < next->key)
        {
            if (prev != NULL)
            {
                prev->next = node;
                node->next = next;
                return head;
            }
            else
            {
                node->next = head;
                return node;
            }
        }
        else
        {
            prev = next;
            next = next->next;
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

int checkfile(file *fl, long long A, long long B) {
    if (fl->dir == '0') {
        printf("1");
        if (fl->hid == 48) {
            printf("2");
            if (fl->time >= A) {
                printf("3");
                if (fl->change <= B) {
                    printf("4\n");
                    return 1;
                }
            }
        }
    }
    printf("fuckup\n");
    return 0;
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

    printf("1\n");

    for (int i = 0; i < n; ++i) {
        printf("cycle\n");
        readfile(&fl1, in);
        printf("%c", fl1.dir);
        ++count;
        if (checkfile(&fl1, A, B)) {
            break;
        }
    }

    printf("2\n");

    file *head = &fl1;

    for (int i = count; i < n; ++i) {
        addfile(head, in);
    }

    printf("3\n");

    printfiles(head, out);

    printf("4\n");

    fclose(in);
    fclose(out);
}