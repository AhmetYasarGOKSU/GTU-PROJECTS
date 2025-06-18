#include <stdio.h>
#include <ctype.h>

void sentence_formatter() {
    int index = 0;
    char ch;
    while ((ch = getchar()) != '\n') {
        if (!isdigit(ch)) {
            putchar(toupper(ch));
        }
        else {
            putchar('X');
        }
    }

}
int main() {

    sentence_formatter();
}