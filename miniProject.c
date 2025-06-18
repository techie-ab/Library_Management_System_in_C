#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Book {
    char title[100];
    char author[100];
    char isbn[14];
    int available; 
    bool isBorrow, isReturn;
    char borrowerName[100];
};

struct Book books[100];
int bookCount = 0;

void addBook() {
    if (bookCount < 100) {
        printf("Enter Book details %d:\n", bookCount + 1);
        printf("Title: ");
        scanf(" %[^\n]%*c", books[bookCount].title);
        printf("Author: ");
        scanf(" %[^\n]%*c", books[bookCount].author);
        printf("ISBN: ");
        scanf("%s", books[bookCount].isbn);
        books[bookCount].available = 1;
        books[bookCount].isBorrow = false;
        books[bookCount].isReturn = false;
        books[bookCount].borrowerName[0] = '\0'; 
        bookCount++;
    } else {
        printf("Book storage is full.\n");
    }
}

void searchBooksByTitleOrAuthor(char input[]) {
    int found = 0;
    printf("Searching for books with title or author '%s':\n", input);
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].title, input) == 0 || strcmp(books[i].author, input) == 0) {
            printf("Found: Title: %s, Author: %s, ISBN: %s, Available: %s, Borrower: %s\n", 
                books[i].title, books[i].author, books[i].isbn, books[i].available ? "Yes" : "No",
                books[i].available ? "None" : books[i].borrowerName);
            found = 1;
        }
    }
    if (!found) {
        printf("No book found with the title or author '%s'.\n", input);
    }
}

void displayBooks() {
    printf("\nDisplaying all Books\n");
    for (int i = 0; i < bookCount; i++) {
        printf("Title: %s, Author: %s, ISBN: %s, Available: %s, Borrower: %s\n", 
            books[i].title, books[i].author, books[i].isbn, books[i].available ? "Yes" : "No",
            books[i].available ? "None" : books[i].borrowerName);
    }
}

void borrowBook(char isbn[]) {
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            if (books[i].available) {
                books[i].available = 0;
                books[i].isBorrow = true;
                books[i].isReturn = false;
                printf("Enter your name: ");
                scanf(" %[^\n]%*c", books[i].borrowerName);
                printf("You have borrowed the book '%s'.\n", books[i].title);
            } else {
                printf("The book '%s' is currently not available.\n", books[i].title);
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No book found with the ISBN '%s'.\n", isbn);
    }
}

void returnBook(char isbn[]) {
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            if (!books[i].available) {
                books[i].available = 1;
                books[i].isBorrow = false;
                books[i].isReturn = true;
                books[i].borrowerName[0] = '\0'; 
                printf("You have returned the book '%s'.\n", books[i].title);
            } else {
                printf("The book '%s' was not borrowed.\n", books[i].title);
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No book found with the ISBN '%s'.\n", isbn);
    }
}

int main() {
    int choice;
    char input[100];

    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Search Book by Title or Author\n");
        printf("3. Display Books\n");
        printf("4. Borrow Book\n");
        printf("5. Return Book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                printf("Enter title or author to search: ");
                scanf(" %[^\n]%*c", input);
                searchBooksByTitleOrAuthor(input);
                break;
            case 3:
                displayBooks();
                break;
            case 4:
                printf("Enter the ISBN to borrow the book: ");
                scanf(" %[^\n]%*c", input);
                borrowBook(input);
                break;
            case 5:
                printf("Enter the ISBN to return the book: ");
                scanf(" %[^\n]%*c", input);
                returnBook(input);
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}


