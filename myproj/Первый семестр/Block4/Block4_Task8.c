#include <stdio.h>

int len(int num) 
{
    int i = 0;
    if (num != 0) {
        while (num > 0) {
            num /= 10;
            ++i;
        }
    }
    else
        i = 1;
    return i;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int id, maxid = -1, maxdur = -1, maxfr = 0, dur, frags,
     Duration[10005] = {0}, Frags[10005] = {0}, t1, t2, t3;

    scanf("%d", &frags);
    for (int i = 0; i < frags; ++i) {
        scanf("%d %d", &id, &dur);
        ++Frags[id];
        Duration[id] += dur;
        if (id > maxid) {
            maxid = id;
        }
        if (Duration[id] > maxdur) {
            maxdur = Duration[id];
        }
        if (Frags[id] > maxfr) {
            maxfr = Frags[id];
        }
    }

    t1 = len(maxid) + 2;
    t2 = len(maxfr) + 2;
    t3 = len(maxdur) + 2;

    printf("+%.*s+%.*s+%.*s+\n", t1, "------------------", t2, "------------------", t3, "------------------");
    for (int i = 0; i <= maxid; ++i) {
        if (Frags[i] != 0) {
            printf("|%*s%d |%*s%d |%*s%d |\n", t1 - len(i) - 1, "", i, t2 - len(Frags[i]) - 1,
             "", Frags[i], t3 - len(Duration[i]) - 1, "", Duration[i]);
            printf("+%.*s+%.*s+%.*s+", t1, "------------------", t2, "------------------", t3, "------------------");
            if (i != maxid)
                printf("\n");
        }
    }

    fclose(stdin);
    fclose(stdout);
}