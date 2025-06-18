#include <stdio.h>

int generateCollatzSequence(int start, int length, FILE* file);
void convertToBinary(int n, FILE * file);
void convertToHex(int n, FILE * file);
void convertToOctal(int n, FILE * file);


int main() {
    int start, length, input_check, last_number, conversion_option;
    
    FILE * collatz_file;
    
    printf("Please type two positive integer number as start and length: ");
    input_check = scanf("%d %d", &start, &length);
    if (input_check != 2) {
        printf("Invalid Input. Please try again!\n");
        return 0;
    }
    if (start <= 0 || length <= 0) {
        printf("Numbers cant be negative! Please try again.\n");
        return 0;
    }

    last_number = generateCollatzSequence(start, length, collatz_file);
    
    printf("Please choose one of conversion: \n");
    printf("1- Decimal to Binary\n");
    printf("2- Decimal to Octal\n");
    printf("3- Decimal to Hexadecimal\n");
    
    input_check = scanf("%d", &conversion_option);
    if (!input_check) {
        printf("Invalid Input. Please try again!\n");
        return 0;
    }
    if (conversion_option == 1 || conversion_option == 2 || conversion_option == 3) {
        if (conversion_option == 1) {
            convertToBinary(last_number, collatz_file);
        } else if (conversion_option == 2) {
            convertToOctal(last_number, collatz_file);
        } else if (conversion_option == 3) {
            convertToHex(last_number, collatz_file);
        } 
    } 
    else {
        printf("Invalid Input. Please try againn!\n");
        return 0;
    }
    

    
}

int generateCollatzSequence(int start, int length, FILE* file) {
    int counter, current_number, last_number;
    file = fopen("collatz.txt", "w");
    current_number = start;
    for (counter = 0; counter < length; counter++) {
        last_number = current_number;
        if (current_number % 2 == 0) {
            fprintf(file, "%d\n", current_number);
            printf("%d.%d\n", counter+1 ,current_number);
            current_number = current_number / 2;
        }
        else if (current_number % 2 != 0) {
            fprintf(file, "%d\n", current_number);
            printf("%d.%d\n", counter+1, current_number);
            current_number = current_number * 3 + 1;
            
        }
    }

    fclose(file);
    printf("Last number is: %d\n", last_number);
    return (last_number);
}

void convertToBinary(int n, FILE * file) {
    int carry, counter;
    int arr[10];
    counter = 0;
    file = fopen("collatz.txt", "a");
    fprintf(file, "Decimal: %d\n", n);
    while (n >= 2) {
        carry = n % 2;
        n /= 2;
        arr[counter] = carry;
        counter++;
    }
    arr[counter] = n;
    int i;
    printf("Decimal to Binary Conversion: ");
    fprintf(file, "Decimal to Binary: ");
    for (i = counter; i >= 0; i--) {
        printf("%d", arr[i]);
        fprintf(file, "%d", arr[i]);
    }
    printf("\n");
    
    

}
void convertToOctal(int n, FILE * file)  {
    int carry, counter;
    int arr[10];
    counter = 0;
    file = fopen("collatz.txt", "a");
    fprintf(file, "Decimal: %d\n", n);
    while (n >= 8) {
        carry = n % 8;
        n /= 8;
        arr[counter] = carry;
        counter++;
    }
    arr[counter] = n;
    int i;
    printf("Decimal to Octal Conversion: ");
    fprintf(file, "Decimal to Octal: ");
    for (i = counter; i >= 0; i--) {
        printf("%d", arr[i]);
        fprintf(file, "%d", arr[i]);
    }
    printf("\n");
}
void convertToHex(int n, FILE * file) {
    int carry, counter;
    int arr[10];
    counter = 0;
    file = fopen("collatz.txt", "a");
    fprintf(file, "Decimal: %d\n", n);
    while (n >= 16) {
        carry = n % 16;
        n /= 16;
        arr[counter] = carry;
        counter++;
    }
    arr[counter] = n;
    int i;
    printf("Decimal to Hexadecimal Conversion: ");
    fprintf(file, "Decimal to Hexadecimal: ");
    for (i = counter; i >= 0; i--) {
        if (arr[i] > 9) {
            if(arr[i] == 10) {
                printf("%c", 'A');
                fprintf(file, "%c", 'A');
            } else if (arr[i] == 11) {
                printf("%c", 'B');
                fprintf(file, "%c", 'B');
            } else if (arr[i] == 12) {
                printf("%c", 'C');
                fprintf(file, "%c", 'C');
            } else if (arr[i] == 13) {
                printf("%c", 'D');
                fprintf(file, "%c", 'D');
            } else if (arr[i] == 14) {
                printf("%c", 'E');
                fprintf(file, "%c", 'E');
            } else if (arr[i] == 15) {
                printf("%c", 'F');
                fprintf(file, "%c", 'F');
            }
        } else {
            printf("%d", arr[i]);
            fprintf(file, "%d", arr[i]);
        }
        
    }
    printf("\n");
}
