#include <stdio.h>
#include <string.h>


void sortUniques(char uniques[], int size) {
    int i, j;
    char temp;
    for (i = 0; i < size-1; i++) {
        for (j = i+1; j < size; j++) {
            if (uniques[i] > uniques[j]) {
                temp = uniques[i];
                uniques[i] = uniques[j];
                uniques[j] = temp;
            }
        }
    }
}
void findUniques(char uniques[], char input[]){
    int i, flag = 0, j, index = 0;    
    for (i = 0; input[i] != '\0'; i++) {
        flag = 0;
        for (j = 0; j < i; j++){
            if (input[i] == uniques[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            uniques[index++] = input[i];
        }
    }
    uniques[index] = '\0';
    sortUniques(uniques, index);
}

void generateVectors(char uniques[], char input[]) {
    int i, j, index;
    int unique_len = strlen(uniques);
    for (i = 0; input[i] != '\0'; i++) {
        for (j = 0; j < unique_len; j++) {
            if (input[i] == uniques[j])index = j;

        }

        for(j = 0; j < unique_len; j++) {
            if (j == index)printf("1");
            else printf("0");

        }

    }
    
}



int main() {
    char input[100];
    char uniques[100];

    printf("Please type something: ");

    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = '\0';

    findUniques(uniques, input);

    generateVectors(uniques, input);
}


