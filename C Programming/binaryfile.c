#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char name[50];
    double gpa;
} Student;

Student createStudent(int* student_count) {
    Student student;
    (*student_count)++;
    student.id = (*student_count);
    strcpy(student.name, "Ahmet");
    student.gpa = 9*(*student_count);
    return student;
}


int main() {
    FILE * fp;
    Student students[3];
    int student_count = 0;
    students[student_count] = createStudent(&student_count);
    students[student_count] = createStudent(&student_count);
    students[student_count] = createStudent(&student_count);
    fp = fopen("binary_file.bin", "wb");

    if (fp == NULL) {
        printf("error\n");
        return -1;
    }

    if (fwrite(students, sizeof(Student), 3, fp) != 3) {
        printf("Error\n");
        fclose(fp);
        return -1;
    } 
    fclose(fp);
    
    fp = fopen("binary_file.bin", "rb");

    if (fp == NULL) {
        printf("error\n");
        return -1;
    }
    Student new_student[3];

    if (fread(&new_student, sizeof(Student), 3, fp) != 3) {
        printf("Error\n");
        fclose(fp);
        return -1;
    }

    printf("%s %d %.2lf", new_student[2].name, new_student[2].id, new_student[2].gpa);


    fclose(fp);
    return 0;
}