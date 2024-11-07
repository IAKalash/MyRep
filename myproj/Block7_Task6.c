#include <stdio.h>
#include <malloc.h>

typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
} list;

list *addlist(list *prevlist, int x) {
    list *node = (list *)malloc(sizeof(list));
    node->data = x;
    
    node->prev = prevlist;
    node->next = prevlist->next;
    prevlist->next = node;
}

void printlist(list *head)
{
    for (list *node = head; node != NULL; node = node->next)
    {
        printf("%d\n", node->data);
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, k;
    list list1;
    list *head = &list1;
    list1.data = 1;
    list1.next = &list1;
    list1.prev = NULL;
    scanf("%d %d", &n, &k);

    for (int i = 1; i < n; ++i) {
        addlist(head, i);
    }

    printlist(head);

    fclose(stdin);
    fclose(stdout);
}
