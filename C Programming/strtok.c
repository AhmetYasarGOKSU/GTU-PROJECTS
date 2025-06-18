#include <stdio.h>
#include <string.h>



int main() {
    char input[100] = "Ahmet,Yasar,Gokturk,Eren";
    char* token;

    token = strtok(input, ",");
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }

}