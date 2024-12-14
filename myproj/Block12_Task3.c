#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct ActorBio {
    char Name[30];
    int BirthYear;
    char Country[10];
} Bio;

typedef struct ActorInMovie {
    char ActorName[60];
    char MovieName[20];
} Movie;

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d\n", &n);

    Bio *table1 = (Bio *)calloc(sizeof(struct ActorBio), n);
    char str[100];

    for (int i = 0; i < n; ++i) {
        gets(str);
        table1[i].Country = strtok(str, " \"");
        table1[i].BirthYear = strtok(str, "\" ");
        table1[i].Name = str;
        printf("%s %d %s\n", table1[i].Name, table1[i].BirthYear, table1[i].Country);
        fflush(stdout);
    }

    scanf("%d", &m);

    Movie *table2 = (Movie *)calloc(sizeof(Movie), m);

    for (int i = 0; i < n; ++i) {
        scanf("%s %s", &table2[i].ActorName, &table2[i].MovieName);
    }

    printf("%s %s\n", table2[1].ActorName, table2[1].MovieName);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (table1[i].Name == table2[j].ActorName) {
                printf("%s %d %s %s %s", table1[i].Name, table1[i].BirthYear, table1[i].Country, 
                table2[j].ActorName, table2[j].MovieName);
            }
        }
    }
    
    fclose(stdin);
    fclose(stdout);
}
