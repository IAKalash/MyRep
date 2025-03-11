#include <assert.h>
#include "primes.h"

int main() {
    // Тесты для isPrime
    assert(isPrime(0) == 0);  // 0 не простое
    assert(isPrime(1) == 0);  // 1 не простое
    assert(isPrime(2) == 1);  // 2 простое
    assert(isPrime(3) == 1);  // 3 простое
    assert(isPrime(4) == 0);  // 4 составное
    assert(isPrime(13) == 1); // 13 простое
    assert(isPrime(100) == 0); // 100 составное
    assert(isPrime(997) == 1); // 997 простое
    assert(isPrime(999983) == 1); // Большое простое
    assert(isPrime(10000000) == 0); // 10^7 составное

    // Тесты для findNextPrime
    assert(findNextPrime(0) == 2);  // Следующее простое после 0
    assert(findNextPrime(1) == 2);  // Следующее простое после 1
    assert(findNextPrime(2) == 2);  // 2 уже простое
    assert(findNextPrime(3) == 3);  // 3 уже простое
    assert(findNextPrime(4) == 5);  // Следующее после 4
    assert(findNextPrime(10) == 11); // Следующее после 10
    assert(findNextPrime(100) == 101); // Следующее после 100
    assert(findNextPrime(999999) == 1000003); // Следующее после 999999
    
    // Тесты для getPrimesCount
    assert(getPrimesCount(0, 1) == 0);  // [0, 1) — нет простых
    assert(getPrimesCount(0, 2) == 0);  // [0, 2) — нет простых
    assert(getPrimesCount(0, 3) == 1);  // [0, 3) — только 2
    assert(getPrimesCount(2, 5) == 2);  // [2, 5) — 2, 3
    assert(getPrimesCount(10, 20) == 4); // [10, 20) — 11, 13, 17, 19
    assert(getPrimesCount(100, 105) == 2); // [100, 105) — 101, 103
    assert(getPrimesCount(999900, 1000000) == 8); // [999900, 10^6) — 999907, 999917, 999931, 999953, 999959
    assert(getPrimesCount(1000000, 1000010) == 1); // [10^6, 10^6+10) — 1000003
    
    assert(getPrimesCount(1, 100000) == 9592);
    assert(isPrime(9999973) == 1);
    assert(findNextPrime(9999908) == 9999929);

    return 0;
}