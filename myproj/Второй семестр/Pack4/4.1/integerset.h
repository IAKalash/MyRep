#pragma once

typedef struct IntegerSet IntegerSet;

IntegerSet *CreateSet (int *arr, int n);
int IsInSet (IntegerSet *set, int num);