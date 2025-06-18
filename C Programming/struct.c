#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Book {
    char book_name[100];
    char author_name[50];
    int price;
}book;

int main() {
    int n, i;
    char ch;
    printf("How many book information do you want to take? ");
    scanf("%d", &n);

    book * books = (book*)malloc(sizeof(book) * n);
    while ((ch = getchar()) != '\n' && ch != EOF)continue;;
    for (i = 0; i < n; i++) {
        printf("Enter book name: ");
        fgets(books[i].book_name, sizeof(books[i].book_name), stdin);
        books[i].book_name[strcspn(books[i].book_name, "\n")] = '\0';
        printf("Enter author name: ");
        fgets(books[i].author_name, sizeof(books[i].author_name), stdin);
        books[i].author_name[strcspn(books[i].author_name, "\n")] = '\0';
        printf("Enter price of book: ");
        scanf("%d", &((books+i)->price));
        while ((ch = getchar()) != '\n' && ch != EOF)continue;;

    }

    for (i = 0; i < n; i++) {
        printf("Book Name: %s\nAuthor Name: %s\nPrice: %d\n", books[i].book_name, books[i].author_name, books[i].price);
    }
    free(books);
}