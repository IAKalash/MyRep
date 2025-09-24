#include "ConsoleGen.h"
#include "TextGen.h"
#include "HtmlGen.h"

int main() {
    ConsoleGen cGen;
    cGen.generate("input.txt");

    TextGen tGen;
    tGen.generate("input.txt", "output.txt");

    HtmlGen hGen;
    hGen.generate("input.txt", "output.html");

    return 0;
}