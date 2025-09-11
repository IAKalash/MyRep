#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Tree {
    char Name[31];
    int BirthYear;
    char Country[11];
    struct Tree *left;
    struct Tree *right;
} Tree;

typedef struct ActorInMovie {
    char Name[31];
    char MovieName[21];
} Movie;

char addEl(Tree *Root) {
    Tree *tree = Root;
    Tree *node = (Tree *)malloc(sizeof(Tree));
    node->left = NULL;
    node->right = NULL;
    scanf(" \"%[^\"]\" %d \"%[^\"]\"", &node->Name, &node->BirthYear, &node->Country);
    while (1) {
        if (strcmp(tree->Name, node->Name) >= 0) {
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

int findEl(Tree *tree, Movie el) {
    Tree *node = tree;
    int cmp = strcmp(node->Name, el.Name);
    
    if (cmp == 0) {
        printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n", node->Name, node->BirthYear, node->Country, el.Name, el.MovieName);
        if (node->left != 0) {
            findEl(node->left, el);
        }
        return 1;
    }
    else if (cmp == 1) {
        if (node->left == NULL) {
            return 0;
        }
        else {
            findEl(node->left, el);
            return 1;
        }
    }
    else {
        if (node->right == NULL) {
            return 0;
        }
        else {
            findEl(node->right, el);
            return 1;
        }
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d", &n);

    Tree Root;
    scanf(" \"%[^\"]\" %d \"%[^\"]\"", &Root.Name, &Root.BirthYear, &Root.Country);
    Root.left = NULL;
    Root.right = NULL;

    for (int j = 0; j < n - 1; ++j) {
        addEl(&Root);
    }

    scanf("%d", &m);
    Movie *table = (Movie *)calloc(m, sizeof(Movie));

    for (int i = 0; i < m; ++i) {
        scanf(" \"%[^\"]\" \"%[^\"]\"", table[i].Name, table[i].MovieName);
    }

    for (int i = 0; i < m; ++ i) {
        findEl(&Root, table[i]);
    }
    
    fclose(stdin);
    fclose(stdout);
}
