#include <stdio.h>
#include <malloc.h>

typedef struct Tokens_s
{
    int num;    // количество слов в строке
    char **arr; // массив слов (каждый элемент –- строка, т.е. char*)
} Tokens;

// tokens: структура, в которую нужно положить результаты
// str: строка, в которой нужно искать слова
// delims: все символы-разделители в виде строки
void tokensSplit(Tokens *tokens, const char *str, const char *delims) {

}
// удаляет все ресурсы внутри tokens
void tokensFree(Tokens *tokens) {
    
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    Tokens tokens;
    *tokens.arr = 0;

    

    fclose(stdin);
    fclose(stdout);
}