#include <stdio.h>
#include <string.h>

int mdays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

typedef struct {
    int day, month, year;
} Date;

int leap_year(int year) {
    if (year % 400 == 0) return 1;
    if (year % 4 == 0 && year % 100 != 0) return 1;
    return 0;
}

void normalized_date(Date *d) {
    if (leap_year(d->year)) {
        mdays[1] = 29;
    } else {
        mdays[1] = 28;
    }
    if (d->month > 12) {
        d->year++;
        d->month = d->month-12;
        normalized_date(d); 
    }
    else if (d->day > mdays[d->month-1]) {
        d->day = d->day - mdays[d->month-1];
        d->month++;
        normalized_date(d);
    }
    else if (d->day < 1) {
        d->day = mdays[d->month-2] + d->day;
        d->month--;

        normalized_date(d);
    }

    
}
void add_days(Date *d, int n) {
    d->day += n;
    normalized_date(d);

}

int main() {
    Date d = {24, 8, 2005};
    add_days(&d, 130);

    printf("%d %d %d", d.day, d.month, d.year);
}