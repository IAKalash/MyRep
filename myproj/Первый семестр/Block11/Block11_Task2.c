#include <stdio.h>
#include <malloc.h>

typedef struct List {
    int num;
    struct List *next;
}List;

void sum (int *sum, int value) {
    value % 2 == 0 ? *sum += value : 0;
}

// тип указателя на функцию, которую можно передавать как callback
typedef void (*callback)(int *, int);
// здесь ctx –- это контекст, который передаётся в func первым аргументом
// последние два параметра задают массив, по элементам которого нужно пройтись
void arrayForeach(int *ctx, callback func, int *arr, int n) {
    for(int i = 0; i < n; ++i) {
        func(ctx, arr[i]);
    }
}

void listForeach(int *ctx, callback func, List *head) {
    for (List* next = head; next != NULL ;next = next->next) {
        func(ctx, next->num);
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, num;
    scanf("%d", &n);

    int *arr = (int *)malloc(4 * n);
    List head;
    List *node, *prev = &head;
    head.next  = NULL;

    scanf("%d", &num);
    head.num = num;
    arr[0] = num;

    for (int i = 1; i < n; ++i) {
        scanf ("%d", &num);
        node = (List *)malloc(sizeof(List));
        node->num = num;
        node->next = NULL;
        prev->next = node;
        prev = node;
        arr[i] = num;
    }

    callback callback = sum;

    int arrSum = 0, listSum = 0;

    arrayForeach(&arrSum, callback, arr, n);
    printf("%d ", arrSum);

    listForeach(&listSum, callback, &head);
    printf("%d", listSum);

    fclose(stdin);
    fclose(stdout);
}
