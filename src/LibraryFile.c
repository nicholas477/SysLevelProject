#include "Library.h"
#include "LibraryFile.h"
#include <sys/stat.h>
#include <errno.h>
#include "GUI.h"

#define MYLIBRARY_BUFFER_SIZE 4096

FILE *MyLibraryFile = NULL;
char MyLibraryFileBuffer[MYLIBRARY_BUFFER_SIZE];

void ParseMyLibraryFile();
void ParseLineToRecord(char* Line, int RecordNum);

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

    // Make the directory for the file, make sure the directory exists too
    if (mkdir("./data", 0777) && errno != EEXIST)
    {
        PrintMessage("ERROR: Failed to create directory ./data!");
        return;
    }

    MyLibraryFile = fopen("./data/MyLibrary.txt", "a+");

    if (!MyLibraryFile)
    {
        PrintMessage("ERROR: Failed to open MyLibrary.txt!");
        return;
    }

    rewind(MyLibraryFile);

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
    memset(&Lines, 0, sizeof(Lines));

    SplitString(MyLibraryFileBuffer, '\n', Lines, MYLIBRARY_MAX_BOOKS);

    // Print out how many records we've loaded (for funsies)
    {
        char Buffer[256];
        int RecordCount = 0;
        for (int i = 0; i < MYLIBRARY_MAX_BOOKS; i++)
        {
            if (Lines[i])
                RecordCount++;
        }
        snprintf(Buffer, 256, "Successfully loaded %d records", RecordCount);
        PrintMessage(&Buffer[0]);
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

void ParseLineToRecord(char* Line, int RecordNum)
{
    // Split the line up into individual record strings
    char* Records[MYLIBRARY_LIBRARYRECORD_MEMBERS];
    SplitString(Line, ',', Records, MYLIBRARY_LIBRARYRECORD_MEMBERS);

    // Keeping track of which record we are entering in this line
    enum RecordField 
    {
        BookID, Title, Author, Possession, CheckoutDate, ReturnDate
    } CurrentRecordField = BookID;

    // Put the strings into the fields
    for (int CurrentRecordField = 0; CurrentRecordField < MYLIBRARY_LIBRARYRECORD_MEMBERS; CurrentRecordField++)
    {
        char* CurrentField = Records[CurrentRecordField];

        switch (CurrentRecordField)
        {
            case BookID:
                Books[RecordNum].BookID = atoi(CurrentField);
            break;

            case Title:
                strncpy(Books[RecordNum].Title, CurrentField, sizeof(Books[RecordNum].Title));
            break;

            case Author:
                strncpy(Books[RecordNum].Author, CurrentField, sizeof(Books[RecordNum].Author));
            break;

            case Possession:
                strncpy(Books[RecordNum].Possession, CurrentField, sizeof(Books[RecordNum].Possession));
            break;

            case CheckoutDate:
                strncpy(Books[RecordNum].CheckoutDate, CurrentField, sizeof(Books[RecordNum].CheckoutDate));
            break;

            case ReturnDate:
                strncpy(Books[RecordNum].ReturnDate, CurrentField, sizeof(Books[RecordNum].ReturnDate));
            break;

            default:
            break;
        }
    }
}