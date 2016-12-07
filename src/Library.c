#include "Library.h"
#include "LibraryFile.h"
#include "GUI.h"

LibraryRecord Books[MYLIBRARY_MAX_BOOKS];

void InitLibrary()
{
    memset(&Books, 0, sizeof(Books));

    // Set the indexes on the books
    for (int i = 0; i < MYLIBRARY_MAX_BOOKS; i++)
    {
        Books[i].BookID = i + 1;
    }

    InitLibraryFile();
}

void AddBook(LibraryRecord NewBook)
{
    // This function is only given the author and the title of the book.
    // This function needs to give the new book an ID and put it in the database    
    for (int i = 0; i < MYLIBRARY_MAX_BOOKS; i++)
    {
        // If this is an invalid book slot, replace it with a new book
        if (!Books[i].bValidBook)
        {
            Books[i] = NewBook;
            Books[i].BookID = i + 1;
            Books[i].bValidBook = true;
            strcpy(Books[i].Possession, "Library");
            strcpy(Books[i].CheckoutDate, "null");
            strcpy(Books[i].ReturnDate, "null");
            SaveFile();

            return;
        }
    }
}

void DeleteBook(int BookID)
{
    // Delete a book by ID
    if (Books[BookID - 1].bValidBook)
    {
        memset(&Books[BookID - 1], 0, sizeof(Books[BookID - 1]));
        Books[BookID - 1].BookID = BookID;

        SaveFile();
        return;
    }
}

bool BookExists(int BookID)
{
    if (BookID < 1 || BookID >= MYLIBRARY_MAX_BOOKS)
    {
        return false;
    }

    return Books[BookID - 1].bValidBook;
}

void ReturnBook(int BookID)
{
    if (Books[BookID - 1].bValidBook)
    {
        strcpy(Books[BookID - 1].Possession, "Library");
        SaveFile();
    }
}

char* GetBookName(int BookID)
{
    // Get book name by ID, return it
    char* BookName = calloc(256, 0);

    if (Books[BookID - 1].bValidBook)
    {
        strcpy(BookName, &Books[BookID - 1].Title[0]);
    }

    return BookName;
}

int GetNumBooksCheckedOut(const char* Username)
{
    // Get the number of books checked out by a specific user.
    int NumBooksCheckedOut = 0;

    for (int i = 0; i < MYLIBRARY_MAX_BOOKS; i++)
    {
        if (strcmp(Username, Books[i].Possession) == 0)
        {
            NumBooksCheckedOut++;
        }
    }

    return NumBooksCheckedOut;
}

void CheckOutBook(const char* Username, int BookID)
{
    // Check out a book for the specified user.
    // Update the possession, check out date, and due date for this book.
    if (Books[BookID -1].bValidBook)
    {
        strcpy(Books[BookID - 1].Possession, Username);

        time_t CurrTime;
        struct tm* TimeInfo;
        char CheckoutDate[32];

        time(&CurrTime);
        TimeInfo = localtime(&CurrTime);

        sprintf(CheckoutDate, "%d-%d-%d", TimeInfo->tm_year, TimeInfo->tm_mon, TimeInfo->tm_mday);

        strcpy(Books[BookID - 1].CheckoutDate, CheckoutDate);
    }
}