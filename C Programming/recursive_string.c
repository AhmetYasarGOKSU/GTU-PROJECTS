#include <stdio.h>
#include <string.h>


void reverse() {
    char ch;
    ch = getchar();
    
    if (ch != '\n') {
        reverse();
        putchar(ch);
    }
}

int main() {
    printf("Input: ");
    reverse();
}