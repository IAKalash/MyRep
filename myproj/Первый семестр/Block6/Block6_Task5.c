#include <stdio.h>
#include <malloc.h>

typedef struct node
{
    char data[7];
    struct node *next;
    int fl;
} list;

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, key;
    list *adr;

    scanf("%d", &n);

    list *arr = (list *)malloc(sizeof(list) * 1000001);

    for (int i = 0; i < n; ++i) {
        scanf("%d ", &key);
        if (arr[key].fl != 1) {
            scanf("%s", arr[key].data);
            arr[key].fl = 1;
        }
        else {
            list *str = (list *)malloc(sizeof(list));
            scanf("%s", str->data);
            str->next = 0000000000000000;
            str->fl = 1;
            if (arr[key].next == 0000000000000000)
            {
                arr[key].next = str;
            }
            else {
                adr = arr[key].next;
                while (adr->next != 0000000000000000)
                {
                    adr = adr->next;
                }
                adr->next = str;
            }
        }
    }

    for (int i = 0; i < 1000000; ++i) {
        if (arr[i].fl == 1) {
            printf("%d %s\n", i, arr[i].data);
            adr = arr[i].next;
            while (adr != 0) {
                printf("%d %s\n", i, adr->data);
                adr = adr->next;
            }
        }
    }

    free(arr);

    fclose(stdin);
    fclose(stdout);
}