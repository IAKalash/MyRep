#include <stdio.h>
#include <malloc.h>

typedef struct node
{
    char data[8];
    int next;
}list;

int add(char *str, int ind, list *arr, int *last, int *ind1) {
    for (int i = 0; i < 7; ++i) {
        arr[*last].data[i] = str[i];
    }
    if (ind == -1) {
        arr[*last].next = *ind1;
        *ind1 = *last;
    }
    else {
        arr[*last].next = arr[ind].next;
        arr[ind].next = *last;
    }
    ++*last;
    return *last - 1;
}

void deletef(int ind, list *arr, int *ind1) {
    if (ind == -1) {
        printf("%s\n", arr[*ind1].data);
        *ind1 = arr[*ind1].next;
    } 
    else {
        printf("%s\n", arr[arr[ind].next].data);
        arr[ind].next = arr[arr[ind].next].next;
    }
}

void printlist(list *arr, int ind1) {
    for (int i = ind1; i != -1; i = arr[i].next)
    {
        printf("%s\n", arr[i].data);
    }
}

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, ind1, tests, q, op, ind;
    char str[8] = {0};

    scanf("%d", &tests);

    for (int k = 0; k < tests; ++k) {

        scanf("%d %d %d", &n, &ind1, &q);

        list *arr = (list *)malloc(sizeof(list) * 200001);

        for (int i = 0; i < n; ++i) {
            scanf("%s %d", &arr[i].data, &arr[i].next);
        }

        for (int i = 0; i < q; ++i)
        {
            scanf("%d %d ", &op, &ind);
            if (op == 0) {
                gets(str);
                printf("%d\n", add(str, ind, arr, &n, &ind1));
            }
            else {
                deletef(ind, arr, &ind1);
            }
        }

        printf("===\n");
        printlist(arr, ind1);
        printf("===\n");

        free(arr);
    }

    fclose(stdin);
    fclose(stdout);
}