#include <assert.h>
#include "modular.h"

int main () {
    MOD = 13; //устанавливаем глобальный модуль
    int a = 45;
    a = pnorm (a );
    assert (a == 6);
    int x = pmul (padd (7 , psub (2 , 3)) , 5);
    assert (x == 4);
    int y = pdiv (7 , x);
    assert ( pmul (x , y) == 7);
    MOD = 2; //меняем модуль на другой
    assert ( pnorm (5) == 1);
    int z = (pmul (2, padd(5,-24)));
    assert (z == 0);
    assert (pdiv (z, 15) == 0);
    assert (pdiv (15, 1) == 1);
    MOD = 5;
    MOD = 10;
    assert (pnorm (149) == 9);
    assert (pdiv (142, 13) == 4);
    return 0;
}