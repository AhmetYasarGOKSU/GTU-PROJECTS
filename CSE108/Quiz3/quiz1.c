#include <stdio.h>




int main () {
        int number;
        int sum = 0;
        FILE * open_file;
        open_file = fopen("numbers.txt", "r");
        if (open_file == NULL) {
                open_file = fopen("numbers.txt", "w");
        }

        while (fscanf(open_file, "%d", &number) != EOF) {
                if (number % 2 == 0)sum += number;
        }
        
        printf("Sum of even number: %d\n", sum);
        
    return 0;
    
}


