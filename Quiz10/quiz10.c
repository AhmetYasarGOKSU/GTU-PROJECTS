#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char name[30];
    char surname[30];
    char department[50];
    char class1[30];
    char class2[30];
    double salary;
} Instructor;

typedef struct {
    char name[30];
    char surname[30];
    double salary;
    char degree;
} Employee;

typedef union {
    Instructor instructor;
    Employee employee;
} DifferentType;

typedef struct {
    char struct_type;
    DifferentType person;
} CombineType;

void readFile(CombineType *person_info) {
    FILE * inp_file;
    inp_file = fopen("input.txt", "r");
    char temp[100], *token;
    int i;
    if (inp_file == NULL) {
        printf("Error while opening input.txt file\n");
        exit(-1);
    }
    for (i = 0; i < 5; i++) {
        fgets(temp, sizeof(temp), inp_file);
        token = strtok(temp, ",");
        person_info[i].struct_type = token[0];
        token = strtok(NULL, " ");
        if (person_info[i].struct_type == 'I') {

            strcpy(person_info[i].person.instructor.name, token);
            token = strtok(NULL, ",");
            strcpy(person_info[i].person.instructor.surname, token);
            token = strtok(NULL, ",");
            strcpy(person_info[i].person.instructor.department, token);
            token = strtok(NULL, ",");
            strcpy(person_info[i].person.instructor.class1, token);
            token = strtok(NULL, ",");
            strcpy(person_info[i].person.instructor.class2, token);
            token = strtok(NULL, ",");

            person_info[i].person.instructor.salary = atof(token);
        }
        else if (person_info[i].struct_type == 'E') {
            strcpy(person_info[i].person.employee.name, token);
            token = strtok(NULL, ",");
            strcpy(person_info[i].person.employee.surname, token);
            token = strtok(NULL, ",");
            person_info[i].person.employee.salary = atoi(token);
            token = strtok(NULL, ",");
            person_info[i].person.employee.degree = token[0];
            
        }
    }
    
    fclose(inp_file);
}

void calculateAnnualSalary(CombineType *person_info) {
    int i;
    
    for (i = 0; i < 5; i++) {
        if (person_info[i].struct_type == 'I') {
            person_info[i].person.instructor.salary += (person_info[i].person.instructor.salary * 5.3 / 100);
        
        }
        else if (person_info[i].struct_type == 'E') {
            if (person_info[i].person.employee.degree == 'a') {
                person_info[i].person.employee.salary += (person_info[i].person.employee.salary * 17.5 / 100);
            }
            else if (person_info[i].person.employee.degree == 'b') {
                person_info[i].person.employee.salary += (person_info[i].person.employee.salary * 12 / 100);
            }
           else if (person_info[i].person.employee.degree == 'c') {
                person_info[i].person.employee.salary += (person_info[i].person.employee.salary * 9 / 100);
            }
        }
    }

}

int main() {
    CombineType persons[5];
    readFile(persons);
    calculateAnnualSalary(persons);

    int i;
    for (i = 0; i < 5; i++) {
        
        if (persons[i].struct_type == 'I') {
            printf("Type: Instructor\n");
            printf("Name: %s\n", persons[i].person.instructor.name);
            printf("Department: %s\n", persons[i].person.instructor.department);
            printf("Courses: %s, %s\n", persons[i].person.instructor.class1, persons[i].person.instructor.class2);
            printf("Salary: %.2lf\n", persons[i].person.instructor.salary);
        }
        else if (persons[i].struct_type == 'E') {
            printf("Type: Employee\n");
            printf("Name: %s\n", persons[i].person.employee.name);
            printf("Surname: %s\n", persons[i].person.employee.surname);
            printf("Degree: %c\n", persons[i].person.employee.degree);
            printf("Salary: %.2lf\n", persons[i].person.employee.salary);
        }
        printf("----------------------------------------------------------\n\n");
    }
}
