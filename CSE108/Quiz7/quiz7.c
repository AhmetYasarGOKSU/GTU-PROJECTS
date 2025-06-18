#include <stdio.h>
#include <string.h>
 
void removeDuplicates(char* input) {
    char temp[100]; 
    int index = 1, flag, index2 = 1;
    temp[0] = input[0];
    while (input[index] != '\0') {

        int temp_index = 0;
        flag = 0;
        while (temp[temp_index] != '\0') {
            if (input[index] == temp[temp_index]) {
                flag = 1;
                
                break;
            }
            temp_index++;
        }
        
        if (!flag) {
            temp[index2++] = input[index];
        }
        index++;
    }
    temp[index2] = '\0';
    printf("String after removing duplicates: %s\n", temp);
    
}

void compressString(char* input) {
    int length = strlen(input);
    int index = 0, letter_counter, flag;
    printf("Compressed string: ");
    while (input[index+1] != '\0') {
        if (flag) {
            letter_counter = 1;
        }
        flag = 0;
        if (input[index] == input[index+1]) {
            letter_counter++;
        }
    
        else {
            if (letter_counter == 1) {
                printf("%c", input[index]);
                
            }
            else {            
                printf("%c%d", input[index], letter_counter);
            }
            flag = 1;
        }
        index++;
    }
    printf("\n");
}

void reverseString(char* input) {
    int length = strlen(input);
    int left = 0, right = length-1;
    char temp;
    while (left < right) {
        temp = input[left];
        input[left] = input[right];
        input[right] = temp;
        left++;
        right--;

    }
    printf("Reversed string: %s\n", input);
}
 
int main() {
    char input[100];
    char input2[100];
    char input3[100];
    
    /* First part of quiz */
    printf("Enter a string: ");
    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = '\0';
    reverseString(input);

    /* Second part of quiz */
    printf("Enter a string: ");
    fgets(input2, 100, stdin);
    input[strcspn(input2, "\n")] = '\0';
    compressString(input2);
        
    /* Third part of quiz */
    printf("Enter a string: ");
    fgets(input3, 100, stdin);
    input3[strcspn(input3, "\n")] = '\0';
    removeDuplicates(input3);
}
