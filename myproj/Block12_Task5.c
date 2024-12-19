
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ActorBio {
    char Name[31];
    int BirthYear;
    char Country[11];
} Bio;

typedef struct ActorInMovie {
    char Name[31];
    char MovieName[21];
} Movie;

int binsearch(Bio *arr, char *num, int len) {
    int M, L = 0, R = len - 1;

    while (L <= R) {
        M = (L + R) / 2;
        int cmp = strcmp(arr[M].Name, num);
        if (cmp == 0) {
            return M;
        }
        else if (cmp < 0) {
            L = M + 1;
        }
        else {
            R = M - 1;
        }
    }
    return -1;
}

int cmpMovie(const void *x1, const void *x2) {
    return (strcmp(((Movie *)x1)->Name, ((Movie *)x2)->Name));
}

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d", &n);

    Bio *table1 = (Bio *)calloc(n, sizeof(Bio));
    char str1[100];

    for (int i = 0; i < n; ++i) {
        scanf(" \"%[^\"]\" %d \"%[^\"]\"", str1, &table1[i].BirthYear, table1[i].Country);
        table1[i].Name[0] = '\0'; 
        strcat(table1[i].Name, str1);
    }

    scanf("%d", &m);
    Movie *table2 = (Movie *)calloc(m, sizeof(Movie));

    for (int i = 0; i < m; ++i) {
        scanf(" \"%[^\"]\" \"%[^\"]\"", table2[i].Name, table2[i].MovieName);
    }

    qsort((void *)table2, m, sizeof(Movie), cmpMovie);

    for (int j = 0; j < m; ++j) {
        int i = binsearch(table1, table2[j].Name, n);
        if (i != -1) {
            printf("\"%s\" %d \"%s\" \"%s\"\n", 
                   table1[i].Name, table1[i].BirthYear, table1[i].Country, table2[j].MovieName);
        }
    }
    
    free(table1);
    free(table2);
    fclose(stdout);

    return 0;
}
