#include <stdio.h>

typedef struct {
    char name[30];
    char surname[30];
    int id;
    int midterm_grade;
    int final_grade;
    double average_grade;
    char letter_grade;
    
} student;

typedef struct {
    student Student[100];
    int num_of_students;
    double threshold;
} class;

void calculateAverage(student *Student, double threshold) {
    double average;
    average = (Student->midterm_grade * 0.4) + (Student->final_grade * 0.6);
    Student->average_grade = average;
    if (average >= threshold) {
        Student->letter_grade = 'P';
    }
    else {
        Student->letter_grade = 'F';
    }
}

class createClass() {
    class Class;
    int flag = 1;
    int counter = 0;
    printf("Please enter a threshold average grade to pass the class?: ");
    scanf("%lf", &(Class.threshold));

    while (flag) {
        flag = 1;
        printf("Student %d\n", counter+1);
        printf("Enter name: ");
        scanf("%s", Class.Student[counter].name);
        printf("Enter surname: ");
        scanf("%s", Class.Student[counter].surname);
        printf("Enter ID: ");
        scanf("%d", &(Class.Student[counter].id));
        printf("Enter midterm grade: ");
        scanf("%d", &(Class.Student[counter].midterm_grade));
        printf("Enter final grade: ");
        scanf("%d", &(Class.Student[counter].final_grade));

        calculateAverage(&(Class.Student[counter]), Class.threshold);
        
        printf("Do you want to add another student?('1' = yes, '0' = no): ");
        scanf("%d", &flag);
        counter++;
    }

    Class.num_of_students = counter;
    
    return Class;
}

void orderGrades(class* Class) {
    int i, j;
    class Temp;

    for (i = 0; i < Class->num_of_students-1; i++) {
        for (j = i+1; j < Class->num_of_students;j++) {
            if (Class->Student[j].average_grade > Class->Student[i].average_grade) {
            
                Temp.Student[0] = Class->Student[j];
                Class->Student[j] = Class->Student[i];
                Class->Student[i] = Temp.Student[0];
            }
        }
    } 
}

void updateScore(int student_id, int new_final_grade, class* Class) {
    int i, flag = 0, index;
    
    for (i = 0; i < Class->num_of_students; i++) {
        if (student_id == Class->Student[i].id) {
            flag = 1;
            index = i;
            break;
        }    
    }
    
    if (flag) {
        Class->Student[index].final_grade = new_final_grade; 
        calculateAverage(&(Class->Student[index]), Class->threshold);
    }
    else {
        printf("Student does not exist.\n");
    }
}

void printInfo(class Class) {
    int i, passing_students = 0;
    double class_average;
    int sum = 0;
    printf("Class Information:\n");
    printf("--------------------------------------------------------------\n");
    printf("Name\tSurname\tID\tMidterm\tFinal\tAverage\tGrade\t\n");
    printf("--------------------------------------------------------------\n");
    
    for (i = 0; i < Class.num_of_students; i++) {
        printf("%s\t%s\t%d\t%d\t%d\t%.1lf\t%c\n", Class.Student[i].name, Class.Student[i].surname, Class.Student[i].id, Class.Student[i].midterm_grade, Class.Student[i].final_grade, Class.Student[i].average_grade, Class.Student[i].letter_grade);
        sum += Class.Student[i].average_grade;
        if (Class.Student[i].letter_grade == 'P')passing_students++;
    }
    printf("--------------------------------------------------------------\n");
    class_average = (double)sum / (double)Class.num_of_students;
    
    printf("Passing students: %d\n", passing_students);
    printf("Class average: %.1lf\n", class_average);
    
}

int main() {
    int new_final_grade, student_id;
    class Class;
    Class = createClass();
    printInfo(Class);
    
    printf("Call Sort");
    orderGrades(&Class);
    
    printInfo(Class);
    
    printf("Update final grade: \n");
    printf("Enter ID: ");
    scanf("%d", &student_id);
    printf("Enter new final grade: ");
    scanf("%d", &new_final_grade);
    
    printf("Call Update");
    updateScore(student_id, new_final_grade, &Class);
    printInfo(Class);
}




