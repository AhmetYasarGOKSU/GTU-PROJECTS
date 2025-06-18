#include <stdio.h>
#include <string.h>

struct Book
{
    char title[100], author[50];
    int pages;
    float price;
};

void printBook(struct Book book1) {
    printf("%s %s %d %.2f", book1.title, book1.author, book1.pages, book1.price);
}

int main() {
    struct Book book1;
    strcpy(book1.title, "The C Programming Language");
    strcpy(book1.author, "Kernighan and Ritchie");

    book1.pages = 272;
    book1.price = 49.99;

    printf("%s %s %d %.2f", book1.title, book1.author, book1.pages, book1.price);
}