#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Defined constants for maximum lengths of book attributes
#define MAX_BOOKNAME_LENGTH 100
#define MAX_AUTHOR_LENGTH 50
#define MAX_GENRE_LENGTH 50

// Defined a structure for book information
typedef struct {
    int bookId;
    char bookName[MAX_BOOKNAME_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    char genre[MAX_GENRE_LENGTH];
    int copies;
} bookInfo;

// Global array of bookInfo to store the books
bookInfo books[250];
// Global variable to keep track of the number of books
int bookCount = 0;

// Function to add a new book
void addBook(FILE* f_ptr) {
    bookInfo* bookDetails = NULL;

    // Increment the book count
    bookCount++;
    // Allocate memory for the new book
    bookDetails = (bookInfo*)realloc(bookDetails, bookCount * sizeof(bookInfo));
    if (bookDetails == NULL) {
        printf("Memory allocation failed.\n");
        return; 
    }

    // Get book details from the user
    printf("Enter the BookID:");
    scanf("%d", &bookDetails[bookCount - 1].bookId);
    printf("Enter the Book Name:");
    getchar();
    scanf("%99[^\n]", bookDetails[bookCount - 1].bookName);
    printf("Enter the Author:");
    getchar();
    scanf("%49[^\n]", bookDetails[bookCount - 1].author);
    printf("Enter the Genre:");
    getchar();
    scanf("%49[^\n]", bookDetails[bookCount - 1].genre);
    printf("Enter the Number of Copies:");
    scanf("%d", &bookDetails[bookCount - 1].copies);
    printf("Book added successfully.\n");

    // Open file to append new book details
    f_ptr = fopen("Library Management Sheet.csv", "a");
    if (f_ptr == NULL) {
        printf("Error opening the file.");
        return; 
    }

    // Write book details to file
    fprintf(f_ptr,"%d,%s,%s,%s,%d\n", bookDetails[bookCount - 1].bookId, &bookDetails[bookCount - 1].bookName, &bookDetails[bookCount - 1].author,
        &bookDetails[bookCount - 1].genre, bookDetails[bookCount - 1].copies);
    fclose(f_ptr);
    free(bookDetails); // Free allocated memory
}

// Function to search for a book
void searchBook() {
    int i, choice = 0, bookFound = 0;
    char name[MAX_BOOKNAME_LENGTH], auth[MAX_AUTHOR_LENGTH], genre[MAX_GENRE_LENGTH];
    printf("1.Search by Book Name\n");
    printf("2.Search by Author\n");
    printf("3.Search by Genre\n");
    printf("Enter option from(1-3): ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        printf("Enter Name of Book:");
        getchar();
        scanf("%99[^\n]",name);
        // Search by book name
        for (i = 0; i < bookCount; i++) {
            if (strcmp(name, books[i].bookName) == 0) {
                printf("Book found.\n");
                printf("%d, %s, %s, %s, %d\n\n", books[i].bookId, books[i].bookName, books[i].author,
                    books[i].genre, books[i].copies);
                bookFound = 1;
            }
        }
        if (!bookFound) {
            printf("Book Not Found.\n\n");
        }
        break;
    case 2:
        printf("Enter Name of Author:");
        getchar();
        scanf("%49[^\n]", auth);
        // Search by author
        for (i = 0; i < bookCount; i++) {
            if (strcmp(auth,books[i].author) == 0) {
                printf("Book found.\n");
                printf("%d, %s, %s, %s, %d\n\n", books[i].bookId, books[i].bookName, books[i].author,
                    books[i].genre, books[i].copies);
                bookFound = 1;
            }
        }
        if (!bookFound) {
            printf("Book Not Found.\n\n");
        }
        break;
    case 3:
        printf("Enter Name of Genre:");
        getchar();
        scanf("%49[^\n]", genre);
        // Search by genre
        for (i = 0; i < bookCount; i++) {
            if (strcmp(genre, books[i].genre) == 0) {
                printf("Book found.\n");
                printf("%d, %s, %s, %s, %d\n\n", books[i].bookId, books[i].bookName, books[i].author,
                    books[i].genre, books[i].copies);
                bookFound = 1;
            }
        }
        if (!bookFound) {
            printf("Book Not Found.\n\n");
        }
        break;
    }
}

// Function to check book availability
void availBook() {
    char name[MAX_BOOKNAME_LENGTH];
    int bookFound = 0, i = 0;
    printf("Enter Name of Book:");
    getchar();
    scanf("%99[^\n]", name);
    // Check availability by book name
    for (i = 0; i < bookCount; i++) {
        if (strcmp(name, books[i].bookName) == 0) {
            if (books[i].copies == 0) {
                printf("Book Not Available.\n\n");
            }
            else {
                printf("Book Available.\n");
                printf("Number of Copies Available: %d\n\n", books[i].copies);
                bookFound = 1;
            }
        }
    }

    if (!bookFound) {
        printf("Book Not Found.\n\n");
    }
}

// Function to delete a book
void deleteBook(FILE* f_ptr) {
    char name[MAX_BOOKNAME_LENGTH];
    int bookFound = 0;

    printf("Enter Name of Book:");
    getchar();
    scanf("%99[^\n]", name);

    // Search and delete the book
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(name, books[i].bookName) == 0) {
            bookFound = 1;
            // Shift the position of remaining books
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            break;
        }
    }

    // Update file after deletion
    if (bookFound) {
        f_ptr = fopen("Library Management Sheet.csv", "w");
        if (f_ptr == NULL) {
            printf("Error opening the file.\n");
            return;
        }
        fprintf(f_ptr, "BookId,BookName,Author,Genre,Copies\n");
        for (int i = 0; i < bookCount; i++) {
            fprintf(f_ptr,"%d,%s,%s,%s,%d\n", books[i].bookId, books[i].bookName, books[i].author, books[i].genre, books[i].copies);
        }

        fclose(f_ptr);
        printf("Book Successfully Deleted.\n\n");
    }
    else {
        printf("Book Not Found.\n\n");
    }
}

// Function to display all books
void displayBook() {
    int i = 0;
    for (i = 0; i < bookCount; i++) {
        printf("%d, %s, %s, %s, %d\n", books[i].bookId, books[i].bookName, books[i].author,
            books[i].genre, books[i].copies);

    }
    printf("\n");
}

// Function to fetch books from file
void fetchBook(FILE* f_ptr) {

    f_ptr = fopen("Library Management Sheet.csv", "r");

    if (f_ptr == NULL) {
        printf("Error opening the file.\n\n");
    }
    char temp[250];
    int count = 0;

    // Read book details from file
    while (fgets(temp, sizeof(temp), f_ptr)) {
        if (count == 0 && strstr(temp, "BookId") != NULL) {
            continue;
        }

        if (sscanf(temp,"%d,%99[^,],%99[^,],%49[^,],%d",
            &books[count].bookId,
            books[count].bookName,
            books[count].author,
            books[count].genre,
            &books[count].copies) == 5) {
            count++;

        }
    }
    if (ferror(f_ptr)) {
        printf("Error reading file.\n\n");
    }
    fclose(f_ptr);
    bookCount = count;
}

// Main function
int main() {
    FILE* f_ptr = NULL;
    int option;
    printf("Library Management System\n\n");
    do {
        fetchBook(f_ptr); // Load books from file
        
        // Display menu options
        printf("         MENU             \n\n");
        printf("1. Add New Book Details\n");
        printf("2. Search Book Details\n");
        printf("3. Check Book Availability\n");
        printf("4. Delete Book Details\n");
        printf("5. Display All Book Details\n");
        printf("6. Exit\n");
        printf("Select an option from (1-6): ");
        scanf("%d", &option);
        switch (option) {
        case 1:
            addBook(f_ptr);
            break;
        case 2:
            searchBook();
            break;
        case 3:
            availBook();
            break;
        case 4:
            deleteBook(f_ptr);
            break;
        case 5:
            displayBook();
            break;
        case 6:
            printf("Exiting Program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (option != 6);

    return 0;
}
