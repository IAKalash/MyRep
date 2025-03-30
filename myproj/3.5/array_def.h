#include <stdlib.h>

//initializes members of [vec] structure for empty array
void CONCAT(NAME, init) (NAME * vec) {
    vec->n = 0;
    vec->capacity = 100;
    vec->arr = (TYPE *)malloc(sizeof(TYPE) * 100);
}

//makes array [vec] empty and frees its array buffer [vec->arr]
//note: this function can be called many times
void CONCAT(NAME, destroy) (NAME * vec) {
    free(vec->arr);
    vec->arr = (TYPE *)malloc(sizeof(TYPE) * 100);
    vec->n = 0;
    vec->capacity = 100;
}

//adds element [value] to the end of array [vec]
//returns index of the added element
int CONCAT(NAME, push) (NAME * vec, TYPE value) {
    if (vec->n + 1 >= vec->capacity) {
        vec->arr = (TYPE *)realloc (vec->arr, sizeof(TYPE) * (vec->capacity + 100));
        vec->capacity += 100;
    }
    vec->arr[vec->n] = value;
    vec->n++;
    return vec->n - 1;
}

//removes the last element from array [vec]
//returns removed element
TYPE CONCAT(NAME, pop) (NAME * vec) {
    vec->n--;
    return vec->arr[vec->n + 1];
}

//ensures that array [vec] has enough storage for [capacity] elements
//note: address of elements surely won’t change before [vec->n] exceeds capacity
void CONCAT(NAME, reserve) (NAME * vec, int capacity) {
    if (vec->capacity - vec->n < capacity) {
        vec->arr = (TYPE *)realloc(vec->arr, sizeof(TYPE) * (vec->capacity + capacity));
        vec->capacity += capacity;
    }
}

//changes number of elements in array [vec] to [newCnt]
//if the number increases, new elements get value [fill]
//if the number decreases, some elements at the end are removed
void CONCAT(NAME, resize) (NAME * vec, int newCnt, TYPE fill) {
    vec->arr = (TYPE *)realloc(vec->arr, sizeof(TYPE) * newCnt);
    if (newCnt > vec->n) {
        for (int i = vec->n; i < newCnt; i++) {
            vec->arr[i] = fill;
        }
    }
    vec->n = newCnt;
    vec->capacity = newCnt;
}   

//inserts elements [arr[0]], [arr[1]], [arr[2]], ..., [arr[num-1]]
//in-between elements [vec->arr[where-1]] and [vec->arr[where]]
//note: the whole array [arr] cannot be part of array [vec]
//[where] may vary from 0 to [vec->n], [num] can also be zero
void CONCAT(NAME, insert) (NAME *vec, int where, TYPE *arr, int num) {
    CONCAT(NAME, reserve) (vec, num);
    for (int i = 0; i < num; ++i) {
        vec->arr[where + i + num] = vec->arr[where + i];
        vec->arr[where + i] = arr[i];
    }
    vec->n += num;
}

//removes elements [vec->arr[k]] for k = [where], [where+1], ..., [where+num-1]
//all the elements starting from [where+num]-th are shifted left by [num] positions
void CONCAT(NAME, erase) (NAME * vec, int where, int num) {
    for (int i = where; i < where + num; ++i) {
        vec->arr[i] = vec->arr[i + num];
    }
    vec->n -= num;
}