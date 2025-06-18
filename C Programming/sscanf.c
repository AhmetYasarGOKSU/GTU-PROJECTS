#include <stdio.h>
#include <string.h>

int main() {
    char line[100], name[30];
    int age;
    double score;

    fgets(line, 100, stdin);
    line[strcspn(line, "\n")] = '\0';

    sscanf(line, "Name: %s Age: %d Score: %lf", name, &age, &score);
    
    printf("Name: %s, Age: %d, Score: %.2lf\n", name, age, score);
}