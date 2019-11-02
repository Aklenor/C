#include <stdio.h>
#include "gets.h"

char *month_name(int n);

static char days_in_month[2][13] = {
        {0,31,28,31,30,31,30,31,31,30,31,30,31},
        {0,31,29,31,30,31,30,31,31,30,31,30,31}
    };

/* вернуть день года по дате и месяцу */
int day_of_year(int year, int month, int day) {

    int days = 0;
    int leap = ((year%4 == 0 && year%100 != 0) || year%400 == 0 );
    printf("leap year: %s %d\n", leap? "yes":"no", leap);

    if ( month < 1 || month > 12)
        return -1;
    if ( day > days_in_month[leap][month] || day < 1)
        return -1;

    for(int m = 1; m < month; m++)
        days += days_in_month[leap][m];
    return days+day;

}

/* return month and day if argument day of the year */
void day_to_date(int year, int year_day, char **month, int *day) {

    int leap = ((year%4 == 0 && year%100 != 0) || year%400 == 0 );

    if ( year_day < 1 || (year_day > (leap? 366:365)) ){
        printf("wrong day: %d of year: %d\n", year_day, year);
        *month = month_name(-1);
        *day = -1;
        return;
    }

    int m = 1;
    while( year_day  > days_in_month[leap][m] ){
        year_day = year_day - days_in_month[leap][m];
        (m)++;
    }

    *month = month_name(m);
    *day = year_day;
}

/* month_name: возвращает имя n-го месяца */
char *month_name(int n) {
    static char *name[] = {
        "Неверный месяц",
        "Январь", "Февраль", "Март",
        "Апрель", "Май", "Июнь",
        "Июль", "Август", "Сентябрь",
        "Октябрь", "Ноябрь", "Декабрь"
        };

    return (n < 1 || n > 12) ? name[0] : name[n];
}

int main() {

    int year=-1;
    char *month = NULL;
    int day=-1;
    int days=-1;
    while(1){
        printf("year: ");
        getint(&year);
        printf("days: ");
        getint(&days);
        day_to_date(year, days, &month, &day);
        printf("date: %d-%s-%d\n",year, month, day);
    }

    return 0;
}
