#include "integerset.h"
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int value;
    struct node* next;
} node;

typedef struct IntegerSet {
    int n;
    node** arr;
    int table_size;
} IntegerSet;

static unsigned int hash(int size, int num) {
    unsigned int u_num = (unsigned int)num;
    return u_num % size;
}

static int cmp(const void* a, const void* b) {
    return (*(int*)a) - (*(int*)b);
}

IntegerSet* CreateSet(int* arr, int n) {
    if (n < 0) return NULL;
    int* temp = (int*)malloc(n * sizeof(int));
    if (!temp) return NULL;
    memcpy(temp, arr, n * sizeof(int));
    qsort(temp, n, sizeof(int), cmp);
    for (int i = 1; i < n; i++) {
        if (temp[i] == temp[i - 1]) {
            free(temp);
            return NULL;
        }
    }

    IntegerSet* set = (IntegerSet*)calloc(1, sizeof(IntegerSet));
    if (!set) {
        free(temp);
        return NULL;
    }

    set->n = n;
    set->table_size = n > 0 ? (n < 10007 ? n : 10007) : 1;
    if (n == 0) {
        set->arr = NULL;
        free(temp);
        return set;
    }

    set->arr = (node**)calloc(set->table_size, sizeof(node*));
    if (!set->arr) {
        free(temp);
        free(set);
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        unsigned int pos = hash(set->table_size, temp[i]);
        node* new_node = (node*)malloc(sizeof(node));
        if (!new_node) {
            for (int j = 0; j < set->table_size; j++) {
                node* current = set->arr[j];
                while (current) {
                    node* next = current->next;
                    free(current);
                    current = next;
                }
            }
            free(set->arr);
            free(temp);
            free(set);
            return NULL;
        }
        new_node->value = temp[i];
        new_node->next = set->arr[pos];
        set->arr[pos] = new_node;
    }

    free(temp);
    return set;
}

int IsInSet(IntegerSet* set, int num) {
    if (!set || set->n == 0) {
        return 0;
    }

    unsigned int pos = hash(set->table_size, num);
    node* current = set->arr[pos];

    while (current) {
        if (current->value == num) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}