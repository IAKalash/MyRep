#include <stdio.h>

int main(void)
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    char curr, next;
    int block = 0; 
    int line = 0;  

    while (fscanf(in, "%c", &curr) != EOF) {
        

        if (block) {

            if (curr == '*') {

                fscanf(in, "%c", &next);

                if (next == '/') {
                    block = 0;
                }
                else {
                    ungetc(next, in);
                }
            }

            else if (curr == '\n') {
                fprintf(out, "%c", curr);
            }
            
        }

        else if (line) {
            if (curr == '\n') {
                line = 0; 
                fprintf(out, "%c", curr);
            }
            }

        else {

            if (curr == '/') {

                fscanf(in, "%c", &next);

                if (next == '/') {
                    line = 1;
                }

                else if (next == '*') {
                    block = 1;
                }

                else {
                    fprintf(out, "%c", curr);
                    ungetc(next, in); 
                }
            }

            else {
                fprintf(out, "%c", curr);
            } 
        }
    }

    fclose(in);
    fclose(out);
}