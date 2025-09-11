#include <stdio.h>
#include <string.h>

void split(char *str) {
    int i = 0, in_quotes = 0;
    int len = strlen(str);
    
    while (i < len && (str[i] == ' ' || str[i] == '\t')) {
        i++;
    }
    
    if (i >= len) return;
    
    printf("[");
    
    while (i < len) {
        if (str[i] == '\\') {
            int backslash_count = 0;
            while (i < len && str[i] == '\\') {
                backslash_count++;
                i++;
            }
            if (i < len && str[i] == '"') {
                int print_backslashes = backslash_count / 2;
                for (int j = 0; j < print_backslashes; j++) {
                    printf("\\");
                }
                if (backslash_count % 2 == 0) {
                    in_quotes = !in_quotes;
                    i++;
                } else {
                    printf("\"");
                    i++;
                }
            } else {
                for (int j = 0; j < backslash_count; j++) {
                    printf("\\");
                }
            }
        }
        else if (str[i] == '"' && i + 1 < len && str[i + 1] == '"') {
            if (in_quotes) {
                printf("\"");
            }
            i += 2;
        }
        else if (str[i] == '"') {
            in_quotes = !in_quotes;
            i++;
        }
        else if ((str[i] == ' ' || str[i] == '\t') && !in_quotes) {
            printf("]");
            while (i < len && (str[i] == ' ' || str[i] == '\t')) {
                i++;
            }
            if (i < len) {
                printf("\n[");
            }
        }
        else {
            printf("%c", str[i]);
            i++;
        }
    }
    
    if (i > 0 && str[i-1] != ' ' && str[i-1] != '\t') {
        printf("]");
    }
}

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char str[101] = {0};
    fgets(str, 101, stdin);
    str[strcspn(str, "\n")] = 0;
    
    split(str);

    fclose(stdin);
    fclose(stdout);
    return 0;
}