#include <stdio.h>
#include <malloc.h>

typedef struct node
{
    int key;
    char data[7];
    struct node *next;
} list;

list *addlist(list *head) {
    list *node = (list *)malloc(sizeof(list));
    scanf("%d %s", &node->key, &node->data);
    
    list *prev = NULL;
    list *next = head;

    while (1) {
        if (next == NULL || node->key < next->key) {
            if (prev != NULL) {
                prev->next = node;
                node->next = next;
                return head;
            }
            else {
                node->next = head;
                return node;
            }
        }
        else {
            prev = next;
            next = next->next;
        }
    }
}

void printlist(list *head)
{
    for (list *node = head; node != NULL; node = node->next)
    {
        printf("%d %s\n", node->key, node->data);
    }
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
    list1.next = NULL;

    for (int i = 0; i < num - 1; ++i) {
        head = addlist(head);
    }

    printlist(head);

    fclose(stdin);
    fclose(stdout);
}