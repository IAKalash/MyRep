#include <stdio.h>
#include <stdlib.h>


int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int cntOfReq = 0, abs_num = 0;
    scanf("%d %d\n",&abs_num,&cntOfReq);

    int cnt = 2000;
    int **mas = (int**)malloc((cnt+1)*sizeof(int*));
    for(int k = 0; k < cnt + 1;k++){
        mas[k] = (int*)malloc(sizeof(int) * (k + 1));
    }


    for(int i = 0; i < cnt+1; i++){
        mas[i][0] = 1;  
        mas[i][i] = 1;
    }

    for (int i = 2; i < cnt + 1; ++i) {
        for (int j = 1; j < i; ++j) {
            mas[i][j] = (mas[i - 1][j] + mas[i - 1][j - 1]) % abs_num;
        }
    }
    
    int n = 0, k = 0;
    for (int i = 0; i < cntOfReq; ++i) {
        scanf("%d %d\n", &n, &k);
        if (k < 0 || k > n) {
            printf ("0\n");
        }
        else {
            printf("%d", mas[n][k]);
            if (i != cntOfReq - 1) {
                printf("\n");
            }
        }
    }

    fclose(stdin);
    fclose(stdout);
    for(int k = 0; k < cnt + 1; k++){
        free(mas[k]);
    }
    free(mas);
    return 0;
}