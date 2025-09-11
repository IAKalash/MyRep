#include <stdio.h>

int main(void)
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    int A1,A2,b1,b2,c1,c2;

    fscanf(in, "%d %d %d %d %d %d", &A1, &A2, &b1, &b2, &c1, &c2);
    
    if ((A1 >= b1 + c1) && (b2 <= A2 && c2 <= A2)){
        fprintf(out, "YES");
    }

    else if ((A1 >= b1 + c2) && (b2 <= A2 && c1 <= A2)){
        fprintf(out, "YES");
    }

    else if ((A1 >= b2 + c1) && (b1 <= A2 && c2 <= A2)){
        fprintf(out, "YES");
    }

    else if ((A1 >= b2 + c2) && (b1 <= A2 && c1 <= A2)){
        fprintf(out, "YES");
    }

    else if ((A2 >= b1 + c1) && (b2 <= A1 && c2 <= A1)){
        fprintf(out, "YES");
    }

    else if ((A2 >= b1 + c2) && (b2 <= A1 && c1 <= A1)){
        fprintf(out, "YES");
    }

    else if ((A2 >= b2 + c1) && (b1 <= A1 && c2 <= A1)){
        fprintf(out, "YES");
    }

    else if ((A2 >= b2 + c2) && (b1 <= A1 && c1 <= A1)){
        fprintf(out, "YES");
    }

    else{
        fprintf(out, "NO");
    }
    

    fclose(in);
    fclose(out);
}
