#include <stdio.h>
#include <string.h>

struct Person{
    char name[50];
    int age;
};

void updatePerson(struct Person* p, const char*newName, int newAge) {
    strcpy(p->name, newName);
    p->age = newAge;    

}

int main() {
    struct Person Person1;
    updatePerson(&Person1, "Ahmet", 19);
    printf("%s %d", Person1.name, Person1.age);
}