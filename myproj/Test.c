#include <stdlib.h>
#include <string.h>
#include "concat.h"

void CONCAT(NAME, init) (NAME *vec) {
    vec->n = 0;
    vec->capacity = 100;
    vec->arr = (TYPE *)calloc(sizeof(TYPE), 100);
}

void CONCAT(NAME, destroy) (NAME *vec) {
    free(vec->arr);
    vec->arr = (TYPE *)malloc(sizeof(TYPE) * 100);
    vec->n = 0;
    vec->capacity = 100;
}

int CONCAT(NAME, push) (NAME *vec, TYPE value) {
    if (vec->n == vec->capacity) {
        int new_capacity = vec->capacity * 2 + 1;
        vec->arr = (TYPE *)realloc(vec->arr, sizeof(TYPE) * new_capacity);
        vec->capacity = new_capacity;
    }
    vec->arr[vec->n] = value;
    vec->n++;
    return vec->n - 1;
}

TYPE CONCAT(NAME, pop) (NAME *vec) {
    if (vec->n > 0) {
        vec->n--;
        return vec->arr[vec->n];
    }
    return (TYPE)0; // Заглушка для n == 0
}

void CONCAT(NAME, reserve) (NAME *vec, int cap) {
    if (vec->capacity < vec->n + cap) {
        vec->arr = (TYPE *)realloc(vec->arr, sizeof(TYPE) * (vec->n + cap));
        vec->capacity = vec->n + cap;
    }
}

void CONCAT(NAME, resize) (NAME *vec, int newCnt, TYPE fill) {
    if (newCnt < 0) return;
    vec->arr = (TYPE *)realloc(vec->arr, sizeof(TYPE) * newCnt);
    if (newCnt > vec->n) {
        for (int i = vec->n; i < newCnt; i++) {
            vec->arr[i] = fill;
        }
    }
    vec->n = newCnt;
    vec->capacity = newCnt;
}

void CONCAT(NAME, insert) (NAME *vec, int where, TYPE *arr, int num) {
    if (num <= 0 || where < 0 || where > vec->n) return;
    CONCAT(NAME, reserve) (vec, num);
    for (int i = vec->n - 1; i >= where; i--) {
        vec->arr[i + num] = vec->arr[i];
    }
    for (int i = 0; i < num; i++) {
        vec->arr[where + i] = arr[i];
    }
    vec->n += num;
}

void CONCAT(NAME, erase) (NAME *vec, int where, int num) {
    if (num <= 0 || where < 0 || where + num > vec->n) return;
    for (int i = where; i < vec->n - num; i++) {
        vec->arr[i] = vec->arr[i + num];
    }
    vec->n -= num;
}

#undef TYPE
#undef NAME