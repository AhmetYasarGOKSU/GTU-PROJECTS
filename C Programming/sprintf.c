#include <stdio.h>

int main() {
    char string[100], name[30] = "Ahmet";
    int age = 19;
    double score = 99;
    sprintf(string, "Name: %s Age: %d Score: %.2lf", name, age, score);

    printf("%s", string);
}