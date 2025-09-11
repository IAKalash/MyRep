
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ActorBio {
    char Name[31];
    int BirthYear;
    char Country[11];
} Bio;

typedef struct ActorInMovie {
    char ActorName[31];
    char MovieName[21];
} Movie;

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d", &n);

    Bio *table1 = (Bio *)calloc(n, sizeof(Bio));
    char str1[100], str2[100];

    for (int i = 0; i < n; ++i) {
        scanf(" \"%[^\"]\" %d \"%[^\"]\"", str1, &table1[i].BirthYear, table1[i].Country);
        table1[i].Name[0] = '\0'; 
        strcat(table1[i].Name, str1);
    }

    scanf("%d", &m);
    Movie *table2 = (Movie *)calloc(m, sizeof(Movie));

    for (int i = 0; i < m; ++i) {
        scanf(" \"%[^\"]\" \"%[^\"]\"", table2[i].ActorName, table2[i].MovieName);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (strcmp(table1[i].Name, table2[j].ActorName) == 0) {
                printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n", 
                       table1[i].Name, table1[i].BirthYear, table1[i].Country, 
                       table2[j].ActorName, table2[j].MovieName);
            }
        }
    }

    free(table1);
    free(table2);
    fclose(stdout);
    fclose(stdin);
}
