#include <stdint.h>

extern int64_t Sum (int l, int r);
extern int n;

int Query (int l, int64_t sum) {
    int r = l + 1;
    while (Sum(l, r) <= sum && r <= n) {
        r++;
    }
    return r - 1;
}