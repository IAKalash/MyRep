#include <stdio.h>

typedef struct DateTime_s
{
    int year, month, day;
    int hours, minutes, seconds;
} DateTime;

DateTime min(const DateTime *arr, int cnt) {
    DateTime minDate = arr[0];
    for (int i = 1; i < cnt; ++i) {
        if (minDate.year > arr[i].year) {
            minDate = arr[i];
        }
        else if (minDate.year == arr[i].year) {
            if (minDate.month > arr[i].month) {
                minDate = arr[i];
            }
            else if (minDate.month == arr[i].month) {
                if (minDate.day > arr[i].day)
                {
                    minDate = arr[i];
                }
                else if (minDate.day == arr[i].day) {
                    if (minDate.hours > arr[i].hours)
                    {
                        minDate = arr[i];
                    }
                    else if (minDate.hours == arr[i].hours) {
                        if (minDate.minutes > arr[i].minutes)
                        {
                            minDate = arr[i];
                        }
                        else if (minDate.minutes == arr[i].minutes) {
                            if (minDate.seconds > arr[i].seconds)
                            {
                                minDate = arr[i];
                            }
                        }
                    }
                }
            }
        }
    }
    return minDate;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;

    scanf("%d", &n);

    DateTime day [50000];

    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d %d %d %d", &day[i].year, &day[i].month, &day[i].day, &day[i].hours, &day[i].minutes, &day[i].seconds);
    }

    DateTime Date = min(day, n);

    printf("%d %d %d %d %d %d", Date.year, Date.month, Date.day, Date.hours, Date.minutes, Date.seconds);

    fclose(stdin);
    fclose(stdout);
}