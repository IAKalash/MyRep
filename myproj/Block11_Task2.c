#include <stdio.h>
#include <malloc.h>

// тип указателя на функцию, которую можно передавать как callback
typedef void (*callback)(void *ctx, int *value);
// здесь ctx –- это контекст, который передаётся в func первым аргументом
// последние два параметра задают массив, по элементам которого нужно пройтись
void arrayForeach(void *ctx, callback func, int *arr, int n);

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    

    fclose(stdin);
    fclose(stdout);
}
