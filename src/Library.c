#include "Library.h"
#include "LibraryFile.h"
#include "GUI.h"

LibraryRecord Books[MYLIBRARY_MAX_BOOKS];
int BookCount = 0;

void InitLibrary()
{
    memset(&Books, 0, sizeof(Books));

    InitLibraryFile();
}

void AddBook(LibraryRecord NewBook)
{
    // This function is only given the author and the title of the book.
    // This function needs to give the new book an ID and put it in the database
    if (BookCount < MYLIBRARY_MAX_BOOKS)
    {
        Books[BookCount] = NewBook;
        Books[BookCount].BookID = BookCount + 1;
        strcpy(Books[BookCount].Possession, "Library");
        strcpy(Books[BookCount].CheckoutDate, "null");
        strcpy(Books[BookCount].ReturnDate, "null");
        BookCount++;
        SaveFile();
    }
}

void DeleteBook(int BookID)
{
    // Delete a book by ID
}

bool BookExists(int BookID)
{
    // Check if a book exists
    return true;
}

char *GetBookName(int BookID)
{
    // Get book name by ID, return it
    char *BookName = calloc(256, 0);
    BookName[0] = ' ';
    return BookName;
}

bool UserExists(const char *Username)
{
    // Return true if a user exists
    return true;
}

int GetNumBooksCheckedOut(const char *Username)
{
    // Get the number of books checked out by a specific user.
    // This should probably return -1 if the user doesnt exist
    return 0;
}

void CheckOutBook(const char *Username, int BookID)
{
    // Check out a book for the specified user.
    // Update the possession, check out date, and due date for this book.
}