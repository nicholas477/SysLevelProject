#include "Library.h"
#include "LibraryFile.h"
#include "GUI.h"
#include "Utils.h"

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

        // Make the checkout date
        {
            time_t CurrTime;
            struct tm* TimeInfo;
            char CheckoutDate[32];

            time(&CurrTime);
            TimeInfo = localtime(&CurrTime);

            sprintf(CheckoutDate, "%d-%d-%d", TimeInfo->tm_year + 1900, TimeInfo->tm_mon + 1, TimeInfo->tm_mday);
            strcpy(Books[BookID - 1].CheckoutDate, CheckoutDate);
        }

        // Make the return date
        {
            time_t CurrTime;
            struct tm* TimeInfo;
            char ReturnDate[32];

            time(&CurrTime);
            TimeInfo = localtime(&CurrTime);

            // Add thirty days and make the time again
            TimeInfo->tm_mday += 30;
            mktime(TimeInfo);

            sprintf(ReturnDate, "%d-%d-%d", TimeInfo->tm_year + 1900, TimeInfo->tm_mon + 1, TimeInfo->tm_mday);
            strcpy(Books[BookID - 1].ReturnDate, ReturnDate);
        }

        SaveFile();
    }
}

double GetBookFine(const char* CurrentDate, int BookID)
{
    double Fine = 0.0;

    if (Books[BookID - 1].bValidBook)
    {
        int DaysPastReturn = CompareDates(CurrentDate, Books[BookID - 1].ReturnDate);

        if (DaysPastReturn > 0)
        {
            Fine = DaysPastReturn * MYLIBRARY_BOOK_FINE;
        }
    }

    return Fine;
}

bool IsLegalDate(const char* Date)
{
    char* DateStr = strdup(Date);
    char* OutDateStrs[3];
    memset(&OutDateStrs, 0, sizeof(OutDateStrs));

    bool bIsLegalDate = true;

    SplitString(DateStr, '-', OutDateStrs, 3);

    for (int i = 0; i < 3; i++)
    {
        if (!OutDateStrs[i] || !IsStringNumber(OutDateStrs[i]))
        {
            bIsLegalDate = false;
            break;
        }
    }

    free(DateStr);

    return bIsLegalDate;
}

struct tm DateToTimeStruct(const char* Date)
{
    char* DateStr = strdup(Date);
    char* OutDateStrs[3];
    memset(&OutDateStrs, 0, sizeof(OutDateStrs));
    
    struct tm OutTime;
    memset(&OutTime, 0, sizeof(OutTime));

    SplitString(DateStr, '-', OutDateStrs, 3);

    OutTime.tm_year = atoi(OutDateStrs[0]) - 1900;
    OutTime.tm_mon = atoi(OutDateStrs[1]) - 1;
    OutTime.tm_mday = atoi(OutDateStrs[2]);

    return OutTime;
}

// If the LHS is before RHS, returns the negative difference in number of days
// If they are equal, returns 0
// If LHS is after RHS, returns the positive difference in number of days
int CompareDates(const char* Lhs, const char* Rhs)
{
    struct tm LhsDate = DateToTimeStruct(Lhs);
    struct tm RhsDate = DateToTimeStruct(Rhs);

    double DeltaSecs = difftime(mktime(&LhsDate), mktime(&RhsDate));

    return (int)(DeltaSecs / 86400.0);
}