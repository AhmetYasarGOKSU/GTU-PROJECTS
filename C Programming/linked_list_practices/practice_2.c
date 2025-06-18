#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int val;
    struct Node* next;
} Node;

void insertAtHead(Node **head, int val) {
    Node *new_node = malloc(sizeof(Node));
    new_node->val = val;
    new_node->next = *head;
    *head = new_node; 

}

void insertAtTail(Node **head, int val) {
    Node *new_node = malloc(sizeof(Node));
    new_node->val = val;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    
    Node *current_node = *head;
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }
    current_node->next = new_node;

}

void insertAtMiddleRecursion(Node** head, int key, int index){
    if (index == 1) {
        Node* new_node = malloc(sizeof(Node));
        new_node->val = key;
        new_node->next = *head;
        *head = new_node;
        return;
    }
    insertAtMiddleRecursion(&((*head)->next),key,index-1);
}

void insertAtMiddle(Node **head, int key, int index) {
    if (index == 1) {
        Node* new_node = malloc(sizeof(Node));
        new_node->val = key;
        new_node->next = *head;
        *head = new_node;
        return;
    }
    Node* curr_node = *head;
    int i = 1;
    while (curr_node->next != NULL && i++ < index-1) {
        curr_node = curr_node->next;
        
    }
    Node* new_node = malloc(sizeof(Node)); 
    Node* temp = curr_node;
    new_node->val = key;
    temp = curr_node->next;
    curr_node->next = new_node;
    new_node->next = temp;
    

}

Node *search(Node *head, int key) {
    Node *current = head;
    while (current != NULL) {
        if (current->val == key) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("NULL\n");
}

void deleteNode(Node **head, int value) {
    Node *current_node = *head;

    if (head == NULL || *head == NULL)
        return;
    if (current_node->val == value) {
        *head = current_node->next;
        free(current_node);
        return;
    }
    while (current_node->next != NULL && current_node->next->val != value) current_node = current_node->next;
    

    Node *temp = current_node->next;
    if (current_node->next->next != NULL) 

    current_node->next = current_node->next->next;
    else current_node->next = NULL;
    free(temp);
}

void reverseList(Node **head) {
    Node* current_node = *head;
    if (current_node == NULL || current_node->next == NULL) return;
    Node* next_node = NULL;
    Node* prev_node = NULL;
    Node* temp;
    while (current_node != NULL) {
        next_node = current_node->next;
        current_node->next = prev_node;
        prev_node = current_node;
        current_node = next_node;
    }
    *head = prev_node;
}

void freeList(Node **head) {
    Node *current = *head, *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}



int main() {
    Node* head = NULL; 

    insertAtHead(&head, 10);
    insertAtTail(&head, 20);
    insertAtHead(&head, 15);
    insertAtTail(&head, 25);
    printList(head);
    reverseList(&head);
    printList(head);
    insertAtMiddleRecursion(&head, 50, 3);
    printList(head);
}