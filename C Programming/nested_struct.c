#include <stdio.h>
#include <string.h>

struct Date{
    int day;
    int month;
    int year;
};

struct Event{
    char name[100];
    struct Date eventDate;
};

int main() {
    struct Event event;
    strcpy(event.name, "Ahmet");
    event.eventDate.day = 24;
    event.eventDate.month = 8;
    event.eventDate.year = 2005;
    
    printf("%s, %d, %d, %d", event.name, event.eventDate.day, event.eventDate.month, event.eventDate.year);
}