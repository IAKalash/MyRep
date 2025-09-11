#include <stdio.h>
#include <string.h>

typedef struct Label_s
{
    char name[16]; // имя автора (заканчивается нулём)
    int age;       // возраст автора (сколько лет)
} Label;

typedef struct NameStats_s
{
    int cntTotal; // сколько всего подписей
    int cntLong;  // сколько подписей с именами длиннее 10 букв
} NameStats;

typedef struct AgeStats_s
{
    int cntTotal;  // сколько всего подписей
    int cntAdults; // сколько подписей взрослых (хотя бы 18 лет)
    int cntKids;   // сколько подписей детей (меньше 14 лет)
} AgeStats;

void calcStats(const Label *arr, int cnt, NameStats *oNames, AgeStats *oAges) {
    oNames->cntTotal = cnt;
    oAges->cntTotal = cnt;
    for (int i = 0; i < cnt; ++i) {
        if (arr[i].age > 17) {
            ++oAges->cntAdults;
        }
        else if (arr[i].age < 14) {
            ++oAges->cntKids;
        }
        if (strlen(arr[i].name) > 10) {
            ++oNames->cntLong;
        }
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    char bin[4];

    scanf("%d", &n);

    Label Names[1001];
    NameStats oNames;
    AgeStats oAges;

    for (int i = 0; i < n; ++i) {
        scanf("%s %d %s", &Names[i].name, &Names[i].age, &bin);
    }

    calcStats(Names, n, &oNames, &oAges);

    printf("names: total = %d\nnames: long = %d\nages: total = %d\nages: adult = %d\nages: kid = %d",
            oNames.cntTotal, oNames.cntLong, oAges.cntTotal, oAges.cntAdults, oAges.cntKids);


    fclose(stdin);
    fclose(stdout);
}