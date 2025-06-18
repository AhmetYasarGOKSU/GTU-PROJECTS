#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mainMenu() {
    printf("\n1. Perform Action\n");
    printf("2. Undo Last Action\n");
    printf("3. Print Action History\n");
    printf("4. Exit\n");
}

void push(char **stack, int *top, const char* data) {
    (*top)++;
    strcpy(stack[*top], data);
}

void undo(char ***stackRef, int *top, int *capacity, int choice1) {
    if (*top < 0) {
        printf("No actions to undo.\n");
        return;
    }

    if (choice1 == 2 && *top <= (*capacity / 2)) {
        *capacity /= 2;
        *stackRef = realloc(*stackRef, sizeof(char*) * (*capacity));
        printf("Stack shrunk to capacity: %d\n", *capacity);
    }
    else if (choice1 == 1) {
        (*capacity)--;
        *stackRef = realloc(*stackRef, sizeof(char*) * (*capacity));
        printf("Stack shrunk to capacity: %d\n", *capacity);
    }

    free((*stackRef)[*top]);
    (*top)--;
}

void performAction(char ***stackRef, int *top, char *data, int *capacity, int choice1) {
    int i;
    if (choice1 == 1) {
        (*capacity)++;
        *stackRef = realloc(*stackRef, sizeof(char*) * (*capacity));
    } else if (choice1 == 2 && *top + 1 >= *capacity) {
        int oldCapacity = *capacity;
        *capacity *= 2;
        *stackRef = realloc(*stackRef, sizeof(char*) * (*capacity));
        for (i = oldCapacity; i < *capacity; i++) {
            (*stackRef)[i] = NULL; 
        }
        printf("Stack resized to capacity: %d\n", *capacity);
    }

    (*stackRef)[*top + 1] = (char*)malloc(50 * sizeof(char));
    push(*stackRef, top, data);
}

void actionHistory(char **stack, int top) {
    int i;
    if (top == -1) {
        printf("No actions performed.\n");
        return;
    }

    printf("Action History:\n");
    for ( i = top; i >= 0; i--) {
        printf("%d: %s\n", i + 1, stack[i]);
    }
}

int main() {
    char **stack = NULL;
    char data[50];
    int choice1, choice2;
    int capacity;
    int top = -1, i;

    printf("Which stack will you use?\n");
    printf("1. One-by-one growth stack\n");
    printf("2. Doubling capacity stack\n");
    printf("Choice: ");
    scanf("%d", &choice1);

    if (choice1 == 2) {
        printf("Enter initial stack capacity: ");
        scanf("%d", &capacity);
    } else {
        capacity = 1;
    }

    stack = (char**)malloc(sizeof(char*) * capacity);
    for ( i = 0; i < capacity; i++) {
        stack[i] = NULL;
    }

    while (1) {
        mainMenu();
        printf("Choice: ");
        scanf("%d", &choice2);
        getchar(); 

        if (choice2 == 1) {
            printf("Enter action: ");
            fgets(data, 50, stdin);
            data[strcspn(data, "\n")] = 0; 
            performAction(&stack, &top, data, &capacity, choice1);
        } else if (choice2 == 2) {
            undo(&stack, &top, &capacity, choice1);
        } else if (choice2 == 3) {
            actionHistory(stack, top);
        } else if (choice2 == 4) {
            for ( i = 0; i <= top; i++) {
                free(stack[i]);
            }
            free(stack);
            printf("Exiting...\n");
            return 0;
        } else {
            printf("Invalid choice. Please select 1-4.\n");
        }
    }
}
