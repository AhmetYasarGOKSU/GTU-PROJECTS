#include <stdio.h>

int is_leap(int num);

int main () {
        int year;
        int check;
        printf("Please type a year: ");
        scanf("%d", &year);
        if (year < 0) {
                printf("Invalid input. Year can not be lower than 0");
                return 0;
        }
        check = is_leap(year);
        
        if (check) {
                printf("%d is a leap year", year);
        }
        else {
                printf("%d is not a leap year", year);
        }
        


}

int is_leap(int num) {
        if (num % 400 == 0) {
                return 1;
        }
        else {
                if (num % 100 == 0) {
                        return 0;
                }
                
        }
        if (num % 4 == 0) {
                return 1;

        }
        else {
                return 0;
        }


}

