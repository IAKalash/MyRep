#include "primes.h"
#include <malloc.h>

static int *arr = NULL;

static void erat(void){
    if (arr == NULL) {
        arr = (int *)malloc(sizeof(int) * 10000021);
        arr[0] = arr[1] = 0;
        for (int i = 2; i < 10000021; i++) {
            arr[i] = 1;
        }
    
        for (int i = 2; i * i < 10000021; i++) {
            for (int j = i * i; j < 10000021; j += i) {
                arr[j] = 0;
            }
        }
    }
}

//returns: 1 if x is prime number, 0 otherwise
int isPrime (int x) {
    erat();
    return arr[x];
}
//returns minimal prime number p such that p >= x
int findNextPrime (int x) {
    erat();
    for (int i = x; i < 10000021; ++i) {
        if (arr[i] == 1) {
            return i;
        }
    }
}
//returns the number of primes x such that l <= x < r
int getPrimesCount (int l, int r) {
    erat();
    int c = 0;
    for (int i = l; i < r; ++i) {
        if(arr[i] == 1) c++;
    }
    return c;
}