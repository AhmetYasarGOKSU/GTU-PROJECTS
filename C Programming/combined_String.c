#include <stdio.h>
#include <ctype.h>
#include <string.h>

void parseString(char string[], char name[], int* age, double* score) {
    fgets(string, 100, stdin);
    string[strcspn(string, "\n")] = '\0';

    sscanf(string, "Name: %s Age: %d Score: %.2lf", name, age, score);
}

void generateNewString(char newString[], char name[], int age, double score) {
    sprintf(newString, "Name: %s Age: %d Score: %.2lf", name, age, score);
}

void printOutputFormat(char newString[]) {
    char ch;
    int index = 0;
    while (newString[index] != '\0') {
        if (!isdigit(newString[index])) {
            putchar(toupper(newString[index]));
        }
        else {
            putchar('X');
        }
        index++;
    }
}

int main() {
    char string[100], newString[100], name[30];
    int age;
    double score;

    parseString(string, name, &age, &score);
    generateNewString(newString, name, age, score);
    printOutputFormat(newString);
}