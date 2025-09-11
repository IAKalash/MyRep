#include <stdio.h>
#include <malloc.h>

typedef struct node
{
    char data[7];
    struct node *next;
} array;

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, key, max = 0;
    array *adr;

    scanf("%d", &n);

    array *arr = (array *)calloc(1000000, sizeof(array));

    for (int i = 0; i < 1000001; ++i) {
        arr[i].next = NULL;
        arr[i].data[0] = '\0';
    }

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &key);
        if (arr[key].data[0] == '\0')
        {
            scanf("%s", &arr[key].data);
            if (key > max)
            {
                max = key;
            }
        }
        else
        {
            array *newarr = (array *)malloc(sizeof(array));
            newarr->next = NULL;
            scanf("%s", newarr->data);
            adr = &arr[key];
            while (adr->next != NULL) {
                adr = adr->next;
            }
            adr->next = newarr;
        }
    }

    for (int i = 0; i <= max; ++i) {
        if (arr[i].data[0] != '\0') {
            printf("%d %s\n", i, arr[i].data);
            adr = &arr[i];
            while (adr->next != NULL)
            {
                adr = adr->next;
                printf("%d %s\n", i, adr->data);
            }
        }
    }

    fclose(stdin);
    fclose(stdout);
}