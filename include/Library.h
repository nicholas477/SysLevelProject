// Our "main" header, include this in every c file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <ncurses.h>

typedef struct
{
    int BookID;
    char Title[128];
    char Author[128];
    int Possession;
} LibraryRecord;

// Book funcs
void AddBook(LibraryRecord NewBook);
void DeleteBook(int BookID);
bool BookExists(int BookID);
char* GetBookName(int BookID);

// User funcs
bool UserExists(const char* Username);
int GetNumBooksCheckedOut(const char* Username);
void CheckOutBook(const char* Username, int BookID);