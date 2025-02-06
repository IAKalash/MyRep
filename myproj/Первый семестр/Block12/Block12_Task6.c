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

int cmpBio(const void *x1, const void *x2) {
    return (strcmp(((Bio *)x1)->Name, ((Bio *)x2)->Name));
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

    qsort((void *)table1, n, sizeof(Bio), cmpBio);

    scanf("%d", &m);
    Movie *table2 = (Movie *)calloc(m, sizeof(Movie));

    for (int i = 0; i < m; ++i) {
        scanf(" \"%[^\"]\" \"%[^\"]\"", table2[i].Name, table2[i].MovieName);
    }

    qsort((void *)table2, m, sizeof(Movie), cmpMovie);

    int i = 0, j = 0;
    while (i < n && j < m) {
        if (strcmp(table1[i].Name, table2[j].Name) == 0) {
            printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n", table1[i].Name, table1[i].BirthYear, table1[i].Country, table2[j].Name, table2[j].MovieName);
            ++j;
        } else if (strcmp(table1[i].Name, table2[j].Name) < 0) {
            ++i;
            j = 0;
        } else {
            ++j;
        }
    }

    free(table1);
    free(table2);
    fclose(stdout);
}