#include <stdio.h>
#include <malloc.h>

typedef struct Tree {
    int node;
    struct Tree *left;
    struct Tree *right;
} Tree;

char addEl(Tree *Root, int num) {
    Tree *tree = Root;
    Tree *node = (Tree *)malloc(sizeof(Tree));
    node->node = num;
    node->left = NULL;
    node->right = NULL;
    while (1) {
        if (tree->node >= num) {
            if (tree->left == NULL) {
                tree->left = node;
                return 'l';
            }
            else {
                tree = tree->left;
            }
        }
        else {
            if (tree->right == NULL) {
                tree->right = node;
                return 'r';
            }
            else {
                tree = tree->right;
            }
        }
    }
}

void printTree(Tree *tree, FILE *out) {
    if (tree->left != NULL) 
        printTree(tree->left, out);
    
    fwrite(&tree->node, 4, 1, out);
    
    if (tree->right != NULL) 
        printTree(tree->right, out);
}

int main(void)
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int n, num;
    fread(&n, 4, 1, in);

    Tree Root;

    fread(&num, 4, 1, in);

    Root.node = num;
    Root.left = NULL;
    Root.right = NULL;

    for (int j = 0; j < n - 1; ++j) {
        fread(&num, 4, 1, in);
        addEl(&Root, num);
    }

    if (n != 0) {
        printTree(&Root, out);
    }
    
    fclose(in);
    fclose(out);
}
