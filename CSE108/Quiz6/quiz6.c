#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateGrades(int grades[10][5]);
void analyzeGrades(double analysis[10][3], int grades[10][5]);
void reportFile(FILE * file, double analysis[10][3]);
double calculateWeightedAverage(int midterm, int final, int homeworks);
int isPass(double avg_grades);

int main () {
    int grades[10][5];
    double analysis[10][3];
    
    FILE * report_file;
    srand(time(NULL));
    /*FIRST PART OF QUİZ*/
    generateGrades(grades);
    int i, j;
    printf("Student | Midterm  Final  HW1    HW2    HW3\n");
    for (i = 0; i < 10; i++) {
        printf("     %2d |", i+1);
        for (j = 0; j < 5; j++) {
            printf("  %2d   ", grades[i][j]);
        }
        printf("\n");
    }   
    
    analyzeGrades(analysis, grades);
    printf("Student | Final Grade | Pass | Letter Code\n");
    for (i = 0; i < 10; i++) {
        printf("     %2d ", i+1);

        printf("|  %4.2lf      ", analysis[i][0]);
        printf("|  %2d  ", (int)analysis[i][1]);
        printf("|  %2d       ", (int)analysis[i][2]);
        printf("\n");
        
    }  
    printf("\n\n");
    printf("Legend: 5 = A, 4 = B, 3 = C, 2 = D, 1 = F\n");
    
    reportFile(report_file, analysis);
}
void generateGrades(int grades[10][5]) {
    int i, j;
    
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 5; j++) {
            grades[i][j] = rand() % 100;
        }
    }
}

void analyzeGrades(double analysis[10][3], int grades[10][5]) {
    int i, j, k;
    double avg_grades;
    int midterm, final, homeworks;

    
    for (i = 0; i < 10; i++) {
        avg_grades = 0;
    
        midterm = grades[i][0];
        final = grades[i][1];
        homeworks = grades[i][2] + grades[i][3] + grades[i][4];
        
        avg_grades = calculateWeightedAverage(midterm, final, homeworks);
        /* AVG GRADES */ 
        analysis[i][0] = avg_grades;
        
    
        /* BINARY GRADES */
        if (isPass(avg_grades)) {
            analysis[i][1] = 1;
        }
        else {
            analysis[i][1] = 0;
        }
        /* LETTER GRADES*/
        if (avg_grades >= 90 && avg_grades < 100) {
            analysis[i][2] = 5;
        } else if (avg_grades >= 75 && avg_grades < 90) {
            analysis[i][2] = 4;
        } else if (avg_grades >= 65 && avg_grades < 75) {
            analysis[i][2] = 3;
        } else if (avg_grades >= 50 && avg_grades < 65) {
            analysis[i][2] = 2;
        } else if (avg_grades < 50) {
            analysis[i][2] = 1;
        }
    }
}

void reportFile(FILE * file, double analysis[10][3]) {
    int passing_students = 0, letter_A = 0, letter_B = 0, letter_C = 0, letter_D = 0, letter_F = 0;
    double avg_final_grades= 0.0;
    
    int i;
    for (i = 0; i < 10; i++) {
        avg_final_grades += analysis[i][0];
        
        if (analysis[i][1]) {
            passing_students++;
        }
        
        if ((int)analysis[i][2] == 5) {
            letter_A++;
        } else if ((int)analysis[i][2] == 4) {
            letter_B++;
        } else if ((int)analysis[i][2] == 3) {
            letter_C++;
        } else if ((int)analysis[i][2] == 2) {
            letter_D++;
        } else if ((int)analysis[i][2] == 1) {
            letter_F++;
        }
    }
    avg_final_grades = avg_final_grades / 10.0;
    
    file = fopen("class_report.txt", "w");
    
    if (file != NULL) {
        fprintf(file, "=== Class Report ===\n");
        fprintf(file, " - Average Final Grade: %.2lf\n", avg_final_grades);
        fprintf(file, " - Passing Students   : %d / 10\n", passing_students);
        fprintf(file, " - Letter Grade Distribution:\n");
        fprintf(file, "  A (5): %d\n", letter_A);
        fprintf(file, "  B (4): %d\n", letter_B);
        fprintf(file, "  C (3): %d\n", letter_C);
        fprintf(file, "  D (2): %d\n", letter_D);
        fprintf(file, "  F (1): %d\n", letter_F);
        
        printf("=== Class Report ===\n");
        printf(" - Average Final Grade: %.2lf\n", avg_final_grades);
        printf(" - Passing Students   : %d / 10\n", passing_students);
        printf(" - Letter Grade Distribution:\n");
        printf("  A (5): %d\n", letter_A);
        printf("  B (4): %d\n", letter_B);
        printf("  C (3): %d\n", letter_C);
        printf("  D (2): %d\n", letter_D);
        printf("  F (1): %d\n", letter_F);
        
        
        if (avg_final_grades >= 85) {
            fprintf(file, "Class Performance: Excellent\n");
            printf("Class Performance: Excellent\n");
            
        } else if (avg_final_grades >= 70 && avg_final_grades < 85) {
            fprintf(file, "Class Performance: Satisfactory\n");
            printf("Class Performance: Satisfactory\n");
        } else if (avg_final_grades < 70) {
            fprintf(file, "Class Performance: Needs Improvement\n");
            printf("Class Performance: Needs Improvement\n");
        }
        
    } else {
        printf("File could not opened!");
    }
    
}

double calculateWeightedAverage(int midterm, int final, int homeworks) {
    double avg_grades;
    avg_grades = (midterm * 0.3) + (final * 0.4) + ((homeworks/3) * 0.3);
    
    return avg_grades;
}
int isPass(double avg_grades) {
    if (avg_grades >= 50) {
        return 1;
    }
    else {
        return 0;
    }
}
