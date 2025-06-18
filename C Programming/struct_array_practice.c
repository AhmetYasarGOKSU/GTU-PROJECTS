#include <stdio.h>
#include <string.h>

struct Employee{
    char name[30];
    int id;
    float salary;
};

int main() {
    int i;
    struct Employee staff[3];
    strcpy(staff[0].name, "Ahmet");
    staff[0].id = 1;
    staff[0].salary = 100.5;

    staff[1] = staff[0];
    staff[2] = staff[0];

    for (i = 0; i < 3; i++) {
        printf("%s %d %.2f\n", staff[i].name, staff[i].id, staff[i].salary);

    }
}


