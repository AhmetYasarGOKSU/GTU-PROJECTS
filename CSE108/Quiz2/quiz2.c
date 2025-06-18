#include <stdio.h>

int isPerfect(int num);
void printPerfect(int lowerLimit, int upperLimit);




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
        
        
        printPerfect(lower_limit, upper_limit);        




}


int isPerfect(int num) {
        int is_it_perfect = 1;
        int total = 0;
        for (int i = 1; i < (num / 2 + 1); i++) {
                if (num % i == 0) {
                        total += i;
                }
        }
        if (num == total)is_it_perfect = 1;
        else is_it_perfect = 0;
        
        if (is_it_perfect) {
                return 1;
        }
        else {
                return 0;
        }
}

void printPerfect(int start, int end) {

        for (int i = start; i < end; i++) {
                if (isPerfect(i)){
                        printf("%d\n", i);
                }       
        }
}
