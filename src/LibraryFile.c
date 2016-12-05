#include "Library.h"
#include "LibraryFile.h"
#include "GUI.h"

#define MYLIBRARY_BUFFER_SIZE 4096

FILE *MyLibraryFile = NULL;
char MyLibraryFileBuffer[MYLIBRARY_BUFFER_SIZE];

void ParseMyLibraryFile();
void ParseLineToRecord(const char* Line, int RecordNum);

// Splits a string into an array of substrings
void SplitString(char* InString, char Delim, char** OutStrings, int OutStringsLen)
{
    int i = 0;
    char* LastLine = &InString[0];
    int LineNum = 0;

    while (InString[i] && LineNum < OutStringsLen)
    {
        if (InString[i] == Delim)
        {
            InString[i] = '\0';
            OutStrings[LineNum] = LastLine;
            LineNum++;
            LastLine = &InString[i + 1];
        }

        i++;
    }
}

void InitLibraryFile()
{
    // Open the file and read it into the buffer
    memset(&MyLibraryFileBuffer[0], '\0', sizeof(MyLibraryFileBuffer));

    MyLibraryFile = fopen("./data/MyLibrary.txt", "a+");

    if (!MyLibraryFile)
    {
        PrintMessage("ERROR: Failed to open ./data/MyLibrary.txt!");
        return;
    }

    int i = 0;
    char c;

    while ((c = fgetc(MyLibraryFile)) != EOF)
    {
        MyLibraryFileBuffer[i] = c;
        i++;
    }

    ParseMyLibraryFile();
}


void ParseMyLibraryFile()
{
    // Split the file up into lines
    char* Lines[MYLIBRARY_MAX_BOOKS];
    SplitString(MyLibraryFileBuffer, '\n', Lines, MYLIBRARY_MAX_BOOKS);

    /*
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
    */

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
    
    {
        int i = 0;
        while (Line[i])
        {
            if (Line[i])

            i++;
        }
    }

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