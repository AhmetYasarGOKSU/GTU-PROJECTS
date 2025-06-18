#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

void insertFront(Node **head, int val) {
    Node *new_node = malloc(sizeof(Node));
    new_node->val = val;
    if (*head == NULL) {
        new_node->next = NULL;
        *head = new_node;
        return;
    }

    new_node->next = *head;
    *head = new_node;
    return;
}


void insertTailRecursive(Node **head, int val) {
    if (*head == NULL) {
        *head = malloc(sizeof(Node));
        (*head)->val = val;
        (*head)->next = NULL;
        return;
    }

    if ((*head)->next == NULL) {
        Node* new_node = malloc(sizeof(Node));
        new_node->next = NULL;
        new_node->val = val;
        (*head)->next = new_node;
        return;
    }
    
    insertTailRecursive(&(*head)->next, val);
    
}

void insertTail(Node** head, int val) {
    Node* new_node = malloc(sizeof(Node));
    new_node->val = val;
    new_node->next = NULL;
    if (*head ==  NULL) {
        *head = new_node;
        return;
    }

    Node* curr_node = *head;
    while (curr_node->next != NULL) {
        curr_node = curr_node->next;
    }
    curr_node->next = new_node;
    return;
}

void reverseList(Node** head) {
    Node* curr = *head;
    Node* prev = NULL;
    Node* next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

void search(Node* head, int val) { 
    int found = 0;
    Node* curr = head;
    while (curr != NULL) {
        if (curr->val == val) {
            found = 1;
            break;
        }
        curr = curr->next;
    }
    if (found) {
        printf("Val has been found!\n");
    }
    else {
        printf("Val could not be found\n");
    }

}

void printList(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        printf("%d->", curr->val);
        curr = curr->next;
    }
    printf("NULL\n");
}

int main () {
    Node* head = NULL;
    printList(head);
    insertFront(&head, 5);
    insertFront(&head, 10);
    insertTail(&head, 15);
    insertTailRecursive(&head, 20);
    printList(head);
    search(head, 10);
    reverseList(&head);
    printList(head);
}