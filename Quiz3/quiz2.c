#include <stdio.h>



int main () {
        int number, check, new_number, reversed_num = 0, multiply;
        int is_minus = 0;
        
        printf("Please type a number: ");
        check = scanf("%d", &number);
        if (check != 1) {
                printf("Invalid input.");
                return -1;
        }

        if (number < 1) {
                number *= -1;
                is_minus = 1;
        }
        multiply = 1;
        int find_multiply = number;
        while (find_multiply > 10) {
                new_number = find_multiply % 10;
                find_multiply = (find_multiply - new_number) / 10;
                multiply *= 10;
        }

        while (number > 0) {
                new_number = number % 10;
                number = (number - new_number) / 10;

                reversed_num += new_number * multiply;
                multiply /= 10;
        }
        
        if (is_minus) {
                reversed_num *= -1;
        }
        
        printf("Reversed num: %d\n", reversed_num);



} 
