#include <stdio.h>

int Vis(int year) {
    int fl;
    if (year % 4 == 0) {
        if (year % 100 == 0){
            fl = (year % 400 == 0) ? 1 : 0;
        }
        else{
            fl = 1;
        }
    }
    else {
        fl = 0;
    }
    return (fl);
} 


int main(void)
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int day,month,year,k;

    fscanf(in, "%d %d %d %d", &day, &month, &year, &k);

    k += day;

    while(1){
        (month == 1 && k > 31) ? k -= 31, month += 1:0;
        (month == 2 && Vis(year) == 0 && k > 28) ? k -= 28, month += 1 : 0;
        (month == 2 && Vis(year) == 1 && k > 29) ? k -= 29, month += 1 : 0;
        (month == 3 && k > 31) ? k -= 31, month += 1 : 0;
        (month == 4 && k > 30) ? k -= 30, month += 1 : 0;
        (month == 5 && k > 31) ? k -= 31, month += 1 : 0;
        (month == 6 && k > 30) ? k -= 30, month += 1 : 0;
        (month == 7 && k > 31) ? k -= 31, month += 1 : 0;
        (month == 8 && k > 31) ? k -= 31, month += 1 : 0;
        (month == 9 && k > 30) ? k -= 30, month += 1 : 0;
        (month == 10 && k > 31) ? k -= 31, month += 1 : 0;
        (month == 11 && k > 30) ? k -= 30, month += 1 : 0;
        (month == 12 && k > 31) ? k -= 31, month = 1, ++year : 0;
        if (k <= 28 || (month != 2 && k <= 31) || (month == 2 && Vis(year) == 1 && k <= 29)){
            break;
        }
    }

    fprintf(out, "%d %d %d\n", k, month, year);

    fclose(in);
    fclose(out);
}
