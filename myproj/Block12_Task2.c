#include <stdio.h>
#include <malloc.h>

void addEl(int *arr, int root, int num) {
    if (arr[root] >= num) {
        root *= 2;
        if (arr[root] == NULL) {
            arr[root] = num;
        }
        else {
            addEl(arr, root, num);
        }
    }
    else {
        root = root * 2 + 1;
        if (arr[root] == NULL) {
            arr[root] = num;
        }
        else {
            addEl(arr, root, num);
        }
    }
}

int main(void)
{
    FILE *in = fopen("input.txt", "rb");
    freopen("output.txt", "w", stdout);

    int n, num;
    fread(&n, 4, 1, in);

    int *tree = (int *)malloc(4 * (n ^ 2));

    for (int i = 0; i < n ^ 2 - 1; ++i) {
        tree[i] = NULL;
    }

    fread(&num, 4, 1, in);

    tree[1] = num;
    printf("%d ", num);

    for (int i = 0; i < n - 1; ++i) {
        fread(&num, 4, 1, in);
        printf("%d ", num);
        fflush(stdout);
        addEl(tree, 1, num);
    }

    printf("   1   ");
    fflush(stdout);

    printf("\n");

    for (int i = 0; i < n ^ 2 - 1; ++i) {
        printf("%d ", tree[i]);
        fflush(stdout);
    }

    fclose(in);
    fclose(stdout);
}
