#include <stdio.h>

int main()
{    
    #if defined(__clang__)
        printf("Compiler: clang\n");
    #elif defined(__GNUC__)
        printf("Compiler: GCC\n");
    #elif defined(__TINYC__)
        printf("Compiler: TCC\n");
    #endif

    #ifdef __x86_64__
        printf("Bitness: 64\n");
    #else
        printf("Bitness: 32\n");
    #endif

    #ifdef NDEBUG
        printf("Asserts: disabled");
    #else
        printf("Asserts: enabled");
    #endif

    return 0;
}
