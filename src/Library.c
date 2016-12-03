#include "Library.h"
#include "LibraryFile.h"
#include "GUI.h"

LibraryRecord Books[MYLIBRARY_MAX_BOOKS];

void ParseMyLibraryFile();
void ParseLineToRecord(const char* Line, int RecordNum);

void InitLibrary()
{
    InitLibraryFile();

    // Open the file and read it into the buffer
    memset(&MyLibraryFileBuffer[0], '\0', sizeof(MyLibraryFileBuffer));

    MyLibraryFile = fopen("./data/MyLibrary.txt", "a+");

    if (MyLibraryFile)
    {
        int i = 0;
        char c;

        while ((c = fgetc(MyLibraryFile)) != EOF)
        {
            MyLibraryFileBuffer[i] = c;
            i++;
        }

        ParseMyLibraryFile();
    }
    else
    {
        PrintMessage("ERROR: Failed to open ./data/MyLibrary.txt!");
    }
}

void ParseMyLibraryFile()
{
    // Split the file up into lines
    char* Lines[MYLIBRARY_MAX_BOOKS];
    {
        int i = 0;
        char* LastLine = &MyLibraryFileBuffer[0];
        int LineNum = 0;

        while (MyLibraryFileBuffer[i] && i < sizeof(MyLibraryFileBuffer))
        {
            if (MyLibraryFileBuffer[i] == '\n')
            {
                MyLibraryFileBuffer[i] = '\0';
                Lines[LineNum] = LastLine;
                LineNum++;
                LastLine = &MyLibraryFileBuffer[i + 1];
            }

            i++;
        }
    }

    // Parse each line
    {
        int LineNum = 0;

        while (Lines[LineNum] && LineNum < MYLIBRARY_MAX_BOOKS)
        {
            ParseLineToRecord(Lines[LineNum], LineNum);
            LineNum++;
        }
    }
}

void ParseLineToRecord(const char* Line, int RecordNum)
{
    // Keeping track of which record we are entering in this line
    enum RecordField 
    {
        BookID, Title, Author, Possession, CheckoutDate, ReturnDate
    } CurrentRecordField = BookID;

    // Parse each character in each line
    int i = 0;
    int j = 0;
    char c;
    while (Line[i] && i < strlen(Line))
    {
        if (Line[i] == ',')
        {
            CurrentRecordField++;
            j = 0;
        }
        else
        {
            switch (CurrentRecordField)
            {
                case BookID:
                    Books[RecordNum].BookID;
                break;

                case Title:

                break;

                case Author:

                break;

                case Possession:

                break;

                case CheckoutDate:

                break;

                case ReturnDate:

                break;

                default:
                break;
            }
        }

        i++;
        j++;
    }
}

void AddBook(LibraryRecord NewBook)
{
    // This function is only given the author and the title of the book.
    // This function needs to give the new book an ID and put it in a database
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