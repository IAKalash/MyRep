#include <stdio.h>
#include <malloc.h>

typedef struct node
{
    int data;
    int next;
    int prev;
} list;

int addnext(int num, int ind, list *arr, int *last, int *ind1, int *indlast)
{
    if (ind == -1)
    {
        arr[*last].next = *ind1;
        arr[*ind1].prev = *last;
        arr[*last].prev = -1;
        *ind1 = *last;
    }
    else
    {
        arr[*last].next = arr[ind].next;
        arr[arr[ind].next].prev = *last;
        arr[*last].prev = ind;
        arr[ind].next = *last;
    }
    if (ind == *indlast) {
        *indlast = *last;
    }
    arr[*last].data = num;
    ++*last;
    return *last - 1;
}

int addprev(int num, int ind, list *arr, int *last, int *ind1, int *indlast)
{
    if (ind == -1)
    {
        arr[*last].prev = *indlast;
        arr[*last].next = -1;
        arr[*indlast].next = *last;
        *indlast = *last;
    }
    else
    {
        arr[*last].next = ind;
        arr[arr[ind].prev].next = *last;
        arr[*last].prev = arr[ind].prev;
        arr[ind].prev = *last;
    }
    if (ind == *ind1)
    {
        *ind1 = *last;
    }
    arr[*last].data = num;
    ++*last;
    return *last - 1;
}

void deletef(int ind, list *arr, int *ind1, int *indlast)
{
    printf("%d\n", arr[ind].data);
    if (arr[ind].prev == -1) {
        arr[arr[ind].next].prev = -1;
        *ind1 = arr[ind].next;
    }
    else if (arr[ind].next == -1)
    {
        arr[arr[ind].prev].next = -1;
        *indlast = arr[ind].prev;
    }
    else {
        arr[arr[ind].prev].next = arr[ind].next;
        arr[arr[ind].next].prev = arr[ind].prev;
    }
}

void printlist(list *arr, int ind1)
{
    for (int i = ind1; i != -1; i = arr[i].next)
    {
        printf("%d\n", arr[i].data);
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, ind1, tests, q, op, ind, indlast, num;

    scanf("%d", &tests);

    for (int k = 0; k < tests; ++k)
    {

        scanf("%d %d %d %d", &n, &ind1, &indlast, &q);

        list *arr = (list *)malloc(sizeof(list) * (n + q + 2));

        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d %d", &arr[i].data, &arr[i].next, &arr[i].prev);
        }

        for (int i = 0; i < q; ++i)
        {
            scanf("%d %d", &op, &ind);
            if (op == 1)
            {
                scanf(" %d", &num);
                printf("%d\n", addnext(num, ind, arr, &n, &ind1, &indlast));
            }
            else if (op == -1) {
                scanf(" %d", &num);
                printf("%d\n", addprev(num, ind, arr, &n, &ind1, &indlast));
            }
            else
            {
                deletef(ind, arr, &ind1, &indlast);
            }
        }

        printf("===\n");
        printlist(arr, ind1);
        printf("===\n");
        fflush(stdout);

        free(arr);
    }

    fclose(stdin);
    fclose(stdout);
}