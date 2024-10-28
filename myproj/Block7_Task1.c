#include <stdio.h>
#include <malloc.h>

typedef struct node
{
    int key;
    char data[7];
    struct node *next;
} list;

void addlist(list *head, int listnum) {
    //добавить в последовательность по ключу
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int num;
    list list1;
    list *head = &list1;

    scanf("%d", &num);
    scanf("%d %s", &list1.key, &list1.data);

    for (int i = 0; i < num - 1; ++i) {
        list list;
        scanf("%d %s", &list.key, &list.data);

    }

    fclose(stdin);
    fclose(stdout);
}