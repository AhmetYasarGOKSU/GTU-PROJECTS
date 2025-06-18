#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int* data;
    int* min_data;
    int top;        // kaç eleman var
    int capacity;   // sadece data için
    int min_top;    // sadece min_data için
} Stack;

void push(Stack* stack, int val) {
    // kapasite artır ve realloc
    stack->capacity++;
    stack->data = realloc(stack->data, sizeof(int) * stack->capacity);
    stack->data[stack->top++] = val;

    // min_data'ya gerekiyorsa ekle
    if (stack->min_top == 0 || val <= stack->min_data[stack->min_top - 1]) {
        stack->min_data = realloc(stack->min_data, sizeof(int) * (stack->min_top + 1));
        stack->min_data[stack->min_top++] = val;
    }
}

void pop(Stack* stack) {
    if (stack->top <= 0) return;

    int removed = stack->data[--stack->top];
    stack->capacity--;
    stack->data = realloc(stack->data, sizeof(int) * stack->capacity);

    if (stack->min_top > 0 && removed == stack->min_data[stack->min_top - 1]) {
        stack->min_top--;
        stack->min_data = realloc(stack->min_data, sizeof(int) * stack->min_top);
    }
}

int getMin(Stack* stack) {
    if (stack->min_top == 0) {
        printf("Stack is empty!\n");
        return -1;
    }
    return stack->min_data[stack->min_top - 1];
}

int main() {
    Stack* stack = malloc(sizeof(Stack));
    stack->capacity = 0;
    stack->top = 0;
    stack->min_top = 0;
    stack->data = NULL;
    stack->min_data = NULL;

    push(stack, 5);
    push(stack, 3);
    push(stack, 7);
    push(stack, 2);

    printf("Min: %d\n", getMin(stack));  // 2

    pop(stack);
    printf("Min after pop: %d\n", getMin(stack));  // 3

    // free bellek
    free(stack->data);
    free(stack->min_data);
    free(stack);

    return 0;
}
