#include <assert.h>
#include "modular.h"

int main () {
    MOD = 13;
    assert(pnorm(-14) == 12);
    assert(pmul(psub(4,12), 8) == 1);
    assert(pnorm(13) == 0);
    assert(padd(44, 29) == 8);
    assert(pdiv(pmul(padd(5, 7), 8), (psub(3, (pmul(9,5))))));
    MOD = 104;
    assert(pnorm(158) == 54);
    assert(padd(12,21) == 33);
    assert(psub(105, 5) == 100);
    assert(pmul(100, 103) == 4);
    assert(pdiv(12, 25) == 92);
    return 0;
}