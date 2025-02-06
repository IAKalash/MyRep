#include <stdio.h>
#include <malloc.h>

typedef struct node
{
    double data;
    int next;
}list;

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, ind1;
    
    scanf("%d %d", &n, &ind1);

    list *arr = (list *)malloc(sizeof(list) * n);

    for (int i = 0; i < n; ++i) {
        scanf("%lf %d", &arr[i].data, &arr[i].next);
    }

    for (int i = ind1; i != -1; i = arr[i].next)
    {
        printf("%0.3lf\n", arr[i].data);
    }

    fclose(stdin);
    fclose(stdout);
}