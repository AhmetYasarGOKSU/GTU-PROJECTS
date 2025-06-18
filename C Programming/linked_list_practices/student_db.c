#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Student {
    int id;
    char name[50];
    int grade;
    struct Student* next;
} Student;

Student *createStudent(int id, const char name[], int grade) {
    Student* student;
    student = malloc(sizeof(Student));
    student->id = id;
    strcpy(student->name, name);
    student->grade = grade;
    student->next = NULL;
    return student;
}

void insertHead(Student **head, Student *new_node) {
    new_node->next = *head;
    *head = new_node;
}

void insertTail(Student **head, Student *new_node) {
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Student* current = *head;
    while (current->next != NULL) current = current->next;
    current->next = new_node;
}

void insertSortedbyId(Student **head, Student* new_node) {
    int added = 0;
    if (*head == NULL) {
        new_node->next = NULL;
        *head = new_node;
        return;
    }
    Student *current = *head;
    Student *prev = NULL;
    while (current != NULL && current->id < new_node->id) {
        prev    = current;
        current = current->next;
    }

    if (prev == NULL) {
        new_node->next = *head;
        *head          = new_node;
    }
    else {
        prev->next     = new_node;
        new_node->next = current; 
    }

}

int deletebyID(Student **head, int id) {
    if (*head == NULL) return 0;

    Student *current = *head;
    Student *prev = NULL;
    while (current != NULL) {
        if (current->id == id) {
            prev->next = current->next;
            return 1;
        }
        else { 
            prev = current;
            current = current->next;
        }
    }
    return 0;
}

void reverseList(Student **head) {
    Student *current = *head;
    Student *prev = NULL;
    Student *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void sortByGrade(Student **head) {
    Student *current = *head;
    Student *counter;
    Student *temp;
    int    tmpId;
    int    tmpGrade;
    char   tmpName[50];


    while (current != NULL && current->next != NULL) {
        counter = current->next;
        while (counter != NULL) {
            if (counter->grade > current->grade) {
                tmpId        = current->id;
                tmpGrade     = current->grade;
                strcpy(tmpName, current->name);

                current->id    = counter->id;
                current->grade = counter->grade;
                strcpy(current->name, counter->name);

                counter->id    = tmpId;
                counter->grade = tmpGrade;
                strcpy(counter->name, tmpName);
            }
            counter = counter->next;
        }
        current = current->next;
    }
}

void printList(Student *head) {
    Student *current = head;
    while (current != NULL) {
        printf(" %d   %s   %d ->", current->id, current->name, current->grade);
        current = current->next;
    }
    printf("NULL\n");
}

void freeStudents(Student **head) {
    Student *current = *head;
    Student *temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}


int main() {
    Student* head = NULL;
    insertTail(&head, createStudent(100, "Ahmet", 100));
    insertHead(&head, createStudent(50, "Mehmet", 50));

    insertTail(&head, createStudent(40, "Ali", 40));
    printList(head);
    insertSortedbyId(&head, createStudent(60, "Salih", 55));
    printList(head);
    deletebyID(&head, 40);
    printList(head);
    reverseList(&head);
    printList(head);
    insertTail(&head, createStudent(40, "Fatma", 99));
    insertTail(&head, createStudent(40, "Ali", 75));

    sortByGrade(&head);
    printList(head);
    freeStudents(&head);
}


