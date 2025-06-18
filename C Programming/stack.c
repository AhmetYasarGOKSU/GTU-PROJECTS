#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push(int* top, char stack[], char val) {
    (*top)++;
    stack[*top] = val; 
}
void pop(int* top) {
    (*top)--;
}

int main() {
    char str[] = "({[])})";
    char stack[100];
    int top = -1;
    int i;
    
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
            push(&top, stack, str[i]);
        }
        else {
            if (stack[top] == '(' && str[i] == ')') {
                pop(&top);
            }
            else if (stack[top] == '[' && str[i] == ']') {
                pop(&top);
            }
            else if (stack[top] == '{' && str[i] == '}') {
                pop(&top);
            }
            else {
                printf("YANLIS\n");
                return -1;
            }
        }
    }
    if (top == -1) {
        printf("DOGRU");
    }

} 