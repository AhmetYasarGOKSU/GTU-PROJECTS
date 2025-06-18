#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {CSE101 = 2, CSE102, CSE103, CSE104, CSE105} lectures;

typedef struct Student{
    char name[50];
    lectures *lecture;
    int id;
    int grade_lecture_counts;
    double *grades;
    double gpa;
    struct Student* next;
} Student;


void addStudent(Student **students);
void removeStudent(Student **students);
void printIds(Student *students);
double calculateGPA(Student *students);
void printLectures(lectures* lecture, Student *students);
void printID(Student *students, int id);
void searchID(Student *students);
void removeLecture(Student *students);
void addLecture(Student *students);
void printList(Student *students);

int main() {
    Student *students = NULL;
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Add Student\n");
        printf("2. Remove Student\n");
        printf("3. Search Student\n");
        printf("4. Add Lecture\n");
        printf("5. Remove Lecture\n");
        printf("6. Print ID\n");
        printf("7. Print List\n");
        printf("8. Exit\n");
        printf("\nChoice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                addStudent(&students);
                printf("Student added.\n");
                break;
            case 2:
                removeStudent(&students);
                break;
            case 3:
                searchID(students);
                break;
            case 4:
                addLecture(students);
                break;
            case 5:
                removeLecture(students);
                break;
            case 6:
                printIds(students);
                break;
            case 7:
                printList(students);
                break;
            case 8:
                while (students != NULL) {
                    Student *temp = students;
                    students = students->next;
                    free(temp->grades);
                    free(temp->lecture);
                    free(temp);
                }
                printf("Freeing memory... Have a nice day!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 8);

    return 0;
}


void addStudent(Student **students) {
    char name[50];
    char grades[50];
    char lecture[50];
    int grade_count = 0, lecture_count = 0;
    char* token;
    Student *new_student = (Student*)malloc(sizeof(Student));
    new_student->grades = NULL;
    new_student->lecture = NULL;
    new_student->next = NULL;
    new_student->grade_lecture_counts = 0;
    Student *last_student = *students;
    printf("Enter student name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; 
    printf("Enter lectures: ");
    fgets(lecture, sizeof(lecture), stdin);
    lecture[strcspn(lecture, "\n")] = 0;
    printf("Enter grades: ");
    fgets(grades, sizeof(grades), stdin);
    grades[strcspn(grades, "\n")] = 0;

    strcpy(new_student->name, name);
    token = strtok(grades, ",");

    while (token != NULL) {
        grade_count++;
        new_student->grades = realloc(new_student->grades, sizeof(double)* grade_count);
        new_student->grades[grade_count-1] = atof(token);
        token = strtok(NULL, ",");
    }
    new_student->grade_lecture_counts = grade_count;
    token = strtok(lecture, ",");
    
    while (token != NULL) {
        lecture_count++;
        new_student->lecture = realloc(new_student->lecture, sizeof(lectures)* lecture_count);
        if (strncmp(token, "CSE101", 6) == 0) {
            new_student->lecture[lecture_count-1] = CSE101;
        }
        else if (strncmp(token, "CSE102",6) == 0) {
            new_student->lecture[lecture_count-1] = CSE102;
        }
        else if (strncmp(token, "CSE103", 6) == 0) {
            new_student->lecture[lecture_count-1] = CSE103;
        } 
        else if (strncmp(token, "CSE104", 6) == 0) {
            new_student->lecture[lecture_count-1] = CSE104;
        }
        else if (strncmp(token, "CSE105", 6) == 0) {
            new_student->lecture[lecture_count-1] = CSE105;
        }

        token = strtok(NULL, ",");
    }

    if (*students == NULL) {
        new_student->id = 1;
        new_student->gpa = calculateGPA(new_student);
        *students = new_student;
        printIds(*students);

    }
    else {
        while (last_student->next != NULL) {
            last_student = last_student->next;  
        }
        new_student->id = (last_student->id) + 1;
        new_student->gpa = calculateGPA(new_student);
        last_student->next = new_student;
        printIds(*students);

    }

}

void removeStudent(Student **students) {
    int id, found = 0;
    printf("Enter student id: ");
    scanf("%d", &id);

    if (*students == NULL) {
        printf("ID COULD NOT FOUND\n");
        return;
    }

    Student *current_student = *students;
    Student *temp_student;
    if (current_student->next == NULL && current_student->id == id) {
        *students = NULL;
        return;
    }
    if (current_student->id == id) {
        temp_student = *students;
        *students = current_student->next;
        printf("Student was removed\n");
        free(temp_student->grades);
        free(temp_student->lecture);
        free(temp_student);

        printIds(*students);
        return;
    } 
    while (current_student->next != NULL) {
        if (current_student->next->id == id) {
            found = 1;
            break;
        }
        current_student = current_student->next;
    }

    if (found) {
        temp_student = current_student->next;
        current_student->next = current_student->next->next;
        printf("Student was removed\n");
        free(temp_student->grades);
        free(temp_student->lecture);
        free(temp_student);
        printIds(*students);

    }
    else {
        printf("ID: %d Could not found.\n", id);
        printIds(*students);

    }
}

void printIds(Student *students) {
    Student *current_student = students;
    printf("id: ");

    if (current_student != NULL && current_student->next == NULL) {
        printf("%d\n", current_student->id);
        return;
    }

    while (current_student->next != NULL) {
        printf("%d,", current_student->id);
        current_student = current_student->next;
 
   }
   printf("%d\n", current_student->id);
}

void printID(Student *students, int id) {
    int i, found = 0;
    Student* current_student = students;
    if (current_student != NULL && current_student->next == NULL && current_student->id == id) {
        found = 1;
    }

    while (current_student->next != NULL && found == 0) {
        if (current_student->id == id)  {
            found = 1;
            break;
        }
        current_student = current_student->next;
    }
    if (found) {
        printf("----------------------------------------------------\n");
        printf("Name       Lectures              Grades         GPA\n");
        printf("----------------------------------------------------\n");
        printf("%s      ", current_student->name);
        printLectures(current_student->lecture, current_student);
        for (i = 0; i < current_student->grade_lecture_counts; i++) {
            printf("%.1lf,", current_student->grades[i]);
        }
        printf("        %.2lf\n", current_student->gpa);
    }
}

void printLectures(lectures* lecture, Student *students) {
    int i = 0;
    Student* current_student = students;
    while (i < current_student->grade_lecture_counts) {
        if (lecture[i] == CSE101) {
            printf("CSE101");
        }
        else if (lecture[i] == CSE102) {
            printf("CSE102");
        }
        else if (lecture[i] == CSE103) {
            printf("CSE103");
        }
        else if (lecture[i] == CSE104) {
            printf("CSE104");
        }
        else if (lecture[i] == CSE105) {
            printf("CSE105");
        }
        printf(",");
        i++;
    }
    printf("      ");
}

double calculateGPA(Student *students) {
    int i;
    Student *current_student = students;
    double total = 0;
    int total_lecture_credit = 0;
    for (i = 0; i < current_student->grade_lecture_counts; i++) {
        total += (current_student->grades[i] * current_student->lecture[i]);
        total_lecture_credit += current_student->lecture[i];
    }

    return (total / total_lecture_credit);
}

void searchID(Student *students) {
    Student *current_student = students;
    int id, found = 0;
    printf("Please enter id: ");
    scanf("%d", &id);
    while (current_student != NULL) {
        if (current_student->id == id) {
            printID(students, id);
            found = 1;
            break;
        }
        current_student = current_student->next;
    }
    if (!found) {
        printf("ID could not found\n");
    }
}

void addLecture(Student *students) {
    int id, i, j, exists;
    char lecture_input[100], grades_input[100];
    char *token;
    lectures lec;
    double grade;

    printf("Enter student id: ");
    scanf("%d", &id);
    getchar();

    Student *current = students;
    while (current != NULL && current->id != id) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Student not found.\n");
        return;
    }

    printf("Enter lectures: ");
    fgets(lecture_input, sizeof(lecture_input), stdin);
    lecture_input[strcspn(lecture_input, "\n")] = 0;

    printf("Enter grades: ");
    fgets(grades_input, sizeof(grades_input), stdin);
    grades_input[strcspn(grades_input, "\n")] = 0;

    char *lecture_token = strtok(lecture_input, ",");
    char *grade_token = strtok(grades_input, ",");

    while (lecture_token != NULL && grade_token != NULL) {
        grade = atof(grade_token);

        if (strncmp(lecture_token, "CSE101", 6) == 0) lec = CSE101;
        else if (strncmp(lecture_token, "CSE102", 6) == 0) lec = CSE102;
        else if (strncmp(lecture_token, "CSE103", 6) == 0) lec = CSE103;
        else if (strncmp(lecture_token, "CSE104", 6) == 0) lec = CSE104;
        else if (strncmp(lecture_token, "CSE105", 6) == 0) lec = CSE105;
        else {
            lecture_token = strtok(NULL, ",");
            grade_token = strtok(NULL, ",");
            continue;
        }

        exists = 0;
        for (i = 0; i < current->grade_lecture_counts; i++) {
            if (current->lecture[i] == lec) {
                current->grades[i] = grade; 
                exists = 1;
                break;
            }
        }

        if (!exists) {
            current->lecture = realloc(current->lecture, sizeof(lectures) * (current->grade_lecture_counts + 1));
            current->grades = realloc(current->grades, sizeof(double) * (current->grade_lecture_counts + 1));
            current->lecture[current->grade_lecture_counts] = lec;
            current->grades[current->grade_lecture_counts] = grade;
            current->grade_lecture_counts++;
        }

        lecture_token = strtok(NULL, ",");
        grade_token = strtok(NULL, ",");
    }

    current->gpa = calculateGPA(current);

    printf("----------------------------------------------------\n");
    printf("Name       Lectures              Grades         GPA\n");
    printf("----------------------------------------------------\n");
    printf("%s      ", current->name);
    printLectures(current->lecture, current);
    for (i = 0; i < current->grade_lecture_counts; i++) {
        printf("%.1lf,", current->grades[i]);
    }
    printf("        %.3lf\n", current->gpa);
}


void removeLecture(Student *students) {
    int id, i, j;
    char lecture_input[100];
    char *token;
    lectures lec;

    printf("Enter student id: ");
    scanf("%d", &id);
    getchar(); 

    Student *current = students;
    while (current != NULL && current->id != id) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Student not found.\n");
        return;
    }

    printf("Enter lectures: ");
    fgets(lecture_input, sizeof(lecture_input), stdin);
    lecture_input[strcspn(lecture_input, "\n")] = 0;

    token = strtok(lecture_input, ",");

    while (token != NULL) {
        if (strncmp(token, "CSE101", 6) == 0) lec = CSE101;
        else if (strncmp(token, "CSE102", 6) == 0) lec = CSE102;
        else if (strncmp(token, "CSE103", 6) == 0) lec = CSE103;
        else if (strncmp(token, "CSE104", 6) == 0) lec = CSE104;
        else if (strncmp(token, "CSE105", 6) == 0) lec = CSE105;
        else {
            token = strtok(NULL, ",");
            continue;
        }

        for (i = 0; i < current->grade_lecture_counts; i++) {
            if (current->lecture[i] == lec) {
                for (j = i; j < current->grade_lecture_counts - 1; j++) {
                    current->lecture[j] = current->lecture[j + 1];
                    current->grades[j] = current->grades[j + 1];
                }

                current->grade_lecture_counts--;

                if (current->grade_lecture_counts > 0) {
                    current->lecture = realloc(current->lecture, sizeof(lectures) * current->grade_lecture_counts);
                    current->grades = realloc(current->grades, sizeof(double) * current->grade_lecture_counts);
                } else {
                    free(current->lecture);
                    free(current->grades);
                    current->lecture = NULL;
                    current->grades = NULL;
                }

                break;
            }
        }

        token = strtok(NULL, ",");
    }

    current->gpa = calculateGPA(current);

    printf("----------------------------------------------------\n");
    printf("Name       Lectures              Grades         GPA\n");
    printf("----------------------------------------------------\n");
    printf("%s      ", current->name);
    printLectures(current->lecture, current);
    for (i = 0; i < current->grade_lecture_counts; i++) {
        printf("%.1lf,", current->grades[i]);
    }
    printf("        %.3lf\n", current->gpa);
}

void printList(Student *students) {
    Student *current = students;
    int i;

    printf("----------------------------------------------------------------------------------\n");
    printf("Name             Lectures                    Grades              GPA     ID\n");
    printf("----------------------------------------------------------------------------------\n");

    while (current != NULL) {
        printf("%-16s", current->name); 
        printLectures(current->lecture, current);

        for (i = 0; i < current->grade_lecture_counts; i++) {
            printf("%.1lf", current->grades[i]);
            if (i != current->grade_lecture_counts - 1)
                printf(",");
        }

        printf("       %.2lf     %d\n", current->gpa, current->id);
        current = current->next;
    }
}
