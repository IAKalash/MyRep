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
    return node;
}

void count (list *head, int k) {
    list *node = head;
    int i = 1;
    while (node != node->next) {
        for (; i < k; ++i)
        {
            node = node->next;
        }
        printf("%d\n", node->data);
        node->prev->next = node->next;
        node->next->prev = node->prev;
        i = 0;
    }
}

void printlist(list *head)
{
    printf("%d\n", head->data);
    for (list *node = head->next; node != head; node = node->next)
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
    list *node = head;
    list1.data = 1;
    list1.next = &list1;
    list1.prev = NULL;
    scanf("%d %d", &n, &k);

    for (int i = 2; i <= n; ++i) {
        node = addlist(node, i);
    }

    head->prev = node;

    count(head, k);

    fclose(stdin);
    fclose(stdout);
}
