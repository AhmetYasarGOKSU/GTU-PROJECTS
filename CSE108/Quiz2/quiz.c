#include <stdio.h>

int is_prime(int num);
void printPrimes(int lowerLimit, int upperLimit);




int main() {
        int number, upper_limit, lower_limit;


        printf("Please determine upper limit: ");
        scanf("%d", &upper_limit);
        if (upper_limit < 2) {
                printf("Upper limit can not be smaller than 2. Please try again.\n");
                return 0;
        }
        printf("Please determine lower limit: ");
        scanf("%d", &lower_limit);
        if (lower_limit > upper_limit) {
                printf("Upper limit can not be larger than upper limit. Please try again.\n");
                return 0;
        }
        
        
        printPrimes(lower_limit, upper_limit);        




}


int is_prime(int num) {
        int is_it_prime = 1;
        if (num < 2) {
                return 0;
        }
        for (int i = 2; i < (num / 2 + 1); i++) {
                if (num % i != 0) continue;
                else if (num % i == 0) {
                        is_it_prime = 0;
                        break;
                        
                }
        }
        if (is_it_prime) {
                return 1;
        }
        else {
                return 0;
        }
}

void printPrimes(int lowerLimit, int upperLimit) {

        for (int i = lowerLimit; i < upperLimit; i++) {
                if (is_prime(i)){
                        printf("%d\n", i);
                }       
        }
}
