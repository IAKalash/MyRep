#include <stdio.h>

typedef struct file {
    char name[20];
    long long size;
    char dir;
    long long time;
    long long change;
    char hid;
    struct file *next;
} file;

FILE *in = fopen("input.txt", "rb");
FILE *out = fopen("output.txt", "wb");

file readfile() {

}

void writefile(file *fl) {
    fwrite(fl, 47, 1, out);
}

list *addlist(list *head)
{
    list *node = (list *)malloc(sizeof(list));
    scanf("%d %s", &node->key, &node->data);

    list *prev = NULL;
    list *next = head;

    while (1)
    {
        if (next == NULL || node->key < next->key)
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

int main(void)
{
    int n, A, B;

    fread(&n, 4, 1, in);
    fread(&A, 8, 1, in);
    fread(&B, 8, 1, in);



    fclose(in);
    fclose(out);
}