#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{add_Patient = 1, display_Patients, orderPatients, Exit} menu;

typedef struct {
    char patient_name[50];
    int patient_age;
    char disease[50];
    char entry_date[50];
} Patient;

void displayMenu() {
    printf("\nHospital Management System\n");
    printf("--------------------------------\n");
    printf("1. Add Patient\n");
    printf("2. Display All Patients\n");
    printf("3. Order Patients According to Entry Date\n");
    printf("4. Exit\n");
}

void addPatient(Patient *p) {
    char ch;
    printf("\nPATIENT ADDED\n");
    printf("Please enter patient name: ");
    fgets(p->patient_name, sizeof(p->patient_name), stdin);
    p->patient_name[strcspn(p->patient_name, "\n")] = '\0';

    printf("Please enter patient age: ");
    scanf("%d", &(p->patient_age));
    
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("Please enter disease name: ");
    fgets(p->disease, sizeof(p->disease), stdin);
    p->disease[strcspn(p->disease, "\n")] = '\0';

    printf("Please enter entry date (dd/mm/yyyy format): ");
    fgets(p->entry_date, sizeof(p->entry_date), stdin);
    p->entry_date[strcspn(p->entry_date, "\n")] = '\0';
}

void displayPatients(Patient *patients, int patient_counter) {
    if (patient_counter == 0) {
        printf("\nNo patients found.\n");
        return;
    }
    int i;
    printf("\nList of Patients:\n");
    for (i = 0; i < patient_counter; i++) {
        printf("\nPatient %d\n", i + 1);
        printf("Patient Name: %s\n", patients[i].patient_name);
        printf("Patient Age: %d\n", patients[i].patient_age);
        printf("Disease: %s\n", patients[i].disease);
        printf("Entry Date: %s\n", patients[i].entry_date);
    }
}

void sortPatients(Patient *patients, int patient_counter) {
    int i, j;
    Patient temp;
    
    for (i = 0; i < patient_counter - 1; i++) {
        for (j = 0; j < patient_counter - i - 1; j++) {
            int day1, month1, year1;
            int day2, month2, year2;

            sscanf(patients[j].entry_date, "%d/%d/%d", &day1, &month1, &year1);
            sscanf(patients[j+1].entry_date, "%d/%d/%d", &day2, &month2, &year2);

            if (year1 > year2 || (year1 == year2 && month1 > month2) || (year1 == year2 && month1 == month2 && day1 > day2)) {
                temp = patients[j];
                patients[j] = patients[j+1];
                patients[j+1] = temp;
            }
        }
    }
    printf("\nPatients sorted successfully according to their entry dates!\n");
}

int main() {
    int capacity = 10;
    int patient_counter = 0;
    char ch;
    menu n;

    // İlk 10 hastalık bellek ayırma
    Patient *patients = (Patient*)malloc(sizeof(Patient) * capacity);
    if (patients == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    while (1) {
        displayMenu();
        printf("Please enter what do you want to do: ");
        scanf("%d", &n);
        while ((ch = getchar()) != '\n' && ch != EOF);

        switch (n) {
        case add_Patient:
            // Bellek yetersizse genişlet
            if (patient_counter == capacity) {
                capacity += 10;
                patients = (Patient*)realloc(patients, sizeof(Patient) * capacity);
                if (patients == NULL) {
                    printf("Memory reallocation failed.\n");
                    return 1;
                }
                printf("\nMemory resized. New capacity: %d patients.\n", capacity);
            }
            addPatient(patients + patient_counter);
            patient_counter++;
            break;
        
        case display_Patients:
            displayPatients(patients, patient_counter);
            break;
        
        case orderPatients:
            sortPatients(patients, patient_counter);
            break;
        
        case Exit:
            // Belleği serbest bırak
            free(patients);
            printf("\nExiting the system. Goodbye!\n");
            return 0;
        
        default:
            printf("\nInvalid option. Please try again.\n");
            break;
        }
    }
}
