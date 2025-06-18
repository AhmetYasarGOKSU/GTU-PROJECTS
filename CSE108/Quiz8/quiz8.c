#include <stdio.h>



double pow_calculate(double n, int power) {
    if (n == 0) return 0;
    if (power == 0) {
        return 1;
    }
    if (power > 0) return n * pow_calculate(n, power-1);
    
    else if (power < 0) return (1/n) * pow_calculate(n, power+1);
}

int print_digits(int number) {
    if (number < 10) {
        printf("%d ", number);
        return number;
    }
    else {
        print_digits(number/10);
        printf("%d ", number % 10);
    }
     
}

int binaryToDecimal(int n, int power) {

    if (n >= 1) return ((n % 10) * pow_calculate(2, power)) + binaryToDecimal(n/10, power+1);
    else return 0;
    
    

}

void findPatterns(char text[], char pattern[]) {
    int index = 0, flag, start_index = 0;
    int j;
    while (text[index] != '\n') {
        flag = 0;
        for (j = 0; pattern[j] != '\n'; j++) {
            if (text[index+j] != pattern[j]) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            printf("Pattern found at index %d\n", index);
            index += j-1;
        }
        else {
            index++;
        }
    }
}


int main() {
    int number; /* For quiz 1 */
    int n, result; /* For quiz 2 */
    char text[100], pattern[100]; /* For quiz 3 */
        /*
    printf("Please enter a number: ");
    scanf("%d", &number);
    print_digits(number);

    printf("\n");
    printf("Please enter a number: ");
    scanf("%d", &n);
    
    
    result = binaryToDecimal(n, 0);
    printf("%d\n", result);
        */

    printf("Please enter a text: ");
    fgets(text, sizeof(text), stdin);

    printf("Please enter a pattern: ");
    fgets(pattern, sizeof(pattern), stdin);


    findPatterns(text, pattern);
    

    
}
