#include <stdio.h>
#include <malloc.h>
#include <math.h>

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

void printTree(int *Tree, int root, FILE *out) {
    if (Tree[root * 2] != NULL)
        printTree(Tree, root *2, out);
    
    fwrite(&Tree[root], 4, 1, out);
    
    if (Tree[root * 2 + 1] != NULL)
        printTree(Tree, root * 2 + 1, out);
}

int main(void)
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int n, num;
    fread(&n, 4, 1, in);

    int *tree = (int *)malloc(4 * (pow(2,n)));

    for (int i = 0; i < n * n; ++i) {
        tree[i] = NULL;
    }

    fread(&num, 4, 1, in);

    tree[1] = num;

    for (int j = 0; j < n - 1; ++j) {
        fread(&num, 4, 1, in);
        addEl(tree, 1, num);
    }

    printTree(tree, 1, out);

    fclose(in);
    fclose(out);
}
