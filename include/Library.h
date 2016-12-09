// Fuck C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include <ncurses.h>

#define MYLIBRARY_MAX_BOOKS 64
#define MYLIBRARY_LIBRARYRECORD_MEMBERS 6

#define MYLIBRARY_BOOK_FINE 0.05

typedef struct
{
    bool bValidBook;
    int BookID;
    char Title[128];
    char Author[64];
    char Possession[64];
    char CheckoutDate[16];
    char ReturnDate[16];
} LibraryRecord;

extern LibraryRecord Books[MYLIBRARY_MAX_BOOKS];

void InitLibrary();

// Book funcs
void AddBook(LibraryRecord NewBook);
void DeleteBook(int BookID);
bool AuthorExists(const char* AuthorName);
bool BookExists(int BookID);
int GetBookIDByName(const char* BookName);
char* GetBookName(int BookID);
void ReturnBook(int BookID);
double GetBookFine(const char* CurrentDate, int BookID);

// User funcs
int GetNumBooksCheckedOut(const char* Username);
void CheckOutBook(const char* Username, int BookID);

// Date funcs
bool IsLegalDate(const char* Date);
struct tm DateToTimeStruct(const char* Date);
int CompareDates(const char* Lhs, const char* Rhs);