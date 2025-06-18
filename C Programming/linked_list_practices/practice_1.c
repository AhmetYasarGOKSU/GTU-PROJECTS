#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node *next;
} Node;



void insertatHead(Node **head, int new_data) {

    Node *new_node = malloc(sizeof(Node));

    new_node->data = new_data;
    new_node->next = *head;
    (*head) = new_node;

}

void insertatTail(Node **head, int new_data) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node *last_node = *head;
    while (last_node->next != NULL) {
        last_node =     last_node->next;
    }
    last_node->next = new_node;
}

void printList(Node *head) {
    Node *current_node = head;

    while(current_node != NULL) {
        printf("%d -> ", current_node->data);
        current_node = current_node->next;
    }
    printf("NULL");
}

Node *search(Node *head, int key) {
    Node *current = head;
    while (current != NULL) {
        if (current->data == key) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void deleteNode(Node **head, int value) {
    Node *current_node = *head;

    if (head == NULL || *head == NULL)
        return;
    if (current_node->data == value) {
        *head = current_node->next;
        free(current_node);
        return;
    }
    while (current_node->next != NULL && current_node->next->data != value) current_node = current_node->next;
    

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

int main () {
    Node* head = NULL;
    insertatTail(&head, 10);
    insertatTail(&head, 20);
    insertatHead(&head, 30);
    insertatHead(&head, 15);
    Node* searched_node = search(head, 30);
    printList(head);
    printf("\n%d\n", searched_node->data);

    deleteNode(&head, 15);
    printList(head);
    printf("\n");
    reverseList(&head);
    printList(head);
    Node *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }

}