#include "Library.h"
#include "LibraryFile.h"
#include <sys/stat.h>
#include <errno.h>
#include "GUI.h"

#define MYLIBRARY_BUFFER_SIZE 4096

FILE* MyLibraryFile = NULL;
char MyLibraryFileBuffer[MYLIBRARY_BUFFER_SIZE];

void ParseMyLibraryFile();
void PrintOutRecordInfo();
void ParseLineToRecord(char* Line);

// Splits a string into an array of substrings
void SplitString(char* InString, char Delim, char** OutStrings, int OutStringsLen)
{
    int i = 0;
    char* LastLine = &InString[0];
    int LineNum = 0;
    int InStringLen = strlen(InString);

    while (InString[i] && LineNum < OutStringsLen)
    {
        // If we have hit a delimiter char or we're at the end of the string
        if (InString[i] == Delim)
        {
            InString[i] = '\0';
            if (strlen(LastLine) > 0)
            {
                OutStrings[LineNum] = LastLine;
                LineNum++;
            }
            LastLine = &InString[i + 1];
        }
        else if (i == InStringLen - 1)
        {
            OutStrings[LineNum] = LastLine;
            return;
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

    while ((c = fgetc(MyLibraryFile)) != EOF && i < MYLIBRARY_BUFFER_SIZE)
    {
        MyLibraryFileBuffer[i] = c;
        i++;
    }

    ParseMyLibraryFile();

    fclose(MyLibraryFile);

    PrintOutRecordInfo();
}

void PrintOutRecordInfo()
{
    char Buffer[256];
    int RecordCount = 0;
    for (int i = 0; i < MYLIBRARY_MAX_BOOKS; i++)
    {
        if (Books[i].bValidBook)
        {
            RecordCount++;
        }
    }
    snprintf(Buffer, 256, "Successfully loaded %d records", RecordCount);
    PrintMessage(&Buffer[0]);
}

void ParseMyLibraryFile()
{
    // Split the file up into lines
    char* Lines[MYLIBRARY_MAX_BOOKS];
    memset(&Lines, 0, sizeof(Lines));

    SplitString(MyLibraryFileBuffer, '\n', Lines, MYLIBRARY_MAX_BOOKS);

    // Parse each line
    {
        int LineNum = 0;

        while (Lines[LineNum] && LineNum < MYLIBRARY_MAX_BOOKS)
        { 
            ParseLineToRecord(Lines[LineNum]);
            LineNum++;
        }
    }
}

void ParseLineToRecord(char* Line)
{
    // Split the line up into individual record strings
    char* Records[MYLIBRARY_LIBRARYRECORD_MEMBERS];
    memset(&Records, 0, sizeof(Records));
    int RecordNum = -1;

    SplitString(Line, ',', Records, MYLIBRARY_LIBRARYRECORD_MEMBERS);
    
    // Keeping track of which record we are entering in this line
    enum RecordField 
    {
        BookID, Title, Author, Possession, CheckoutDate, ReturnDate
    } CurrentRecordField = 0;

    // Put the strings into the fields
    while (Records[CurrentRecordField])
    {
        char* CurrentFieldStr = Records[CurrentRecordField];
        
        switch (CurrentRecordField)
        {
            case BookID:
                RecordNum = (atoi(CurrentFieldStr) - 1);
            break;

            case Title:
                if (RecordNum >= 0)
                {
                    strncpy(Books[RecordNum].Title, CurrentFieldStr, sizeof(Books[RecordNum].Title));
                }
            break;

            case Author:
                if (RecordNum >= 0)
                {
                    strncpy(Books[RecordNum].Author, CurrentFieldStr, sizeof(Books[RecordNum].Author));
                }
            break;

            case Possession:
                if (RecordNum >= 0)
                {
                    strncpy(Books[RecordNum].Possession, CurrentFieldStr, sizeof(Books[RecordNum].Possession));
                }
            break;

            case CheckoutDate:
                if (RecordNum >= 0)
                {
                    strncpy(Books[RecordNum].CheckoutDate, CurrentFieldStr, sizeof(Books[RecordNum].CheckoutDate));
                }
            break;

            case ReturnDate:
                if (RecordNum >= 0)
                {
                    strncpy(Books[RecordNum].ReturnDate, CurrentFieldStr, sizeof(Books[RecordNum].ReturnDate));
                }
            break;

            default:
            break;
        }
        CurrentRecordField++;
    }

    if (RecordNum >= 0)
    {
        Books[RecordNum].bValidBook = true;
    }
}

void SaveFile()
{
    MyLibraryFile = fopen("./data/MyLibrary.txt", "w+");

    if (!MyLibraryFile)
    {
        PrintMessage("ERROR: Failed to open MyLibrary.txt!");
        return;
    }

    for (int i = 0; i < MYLIBRARY_MAX_BOOKS; i++)
    {
        if (Books[i].bValidBook)
        {
            fprintf(MyLibraryFile, "%d,%s,%s,%s,%s,%s\n", 
                Books[i].BookID, Books[i].Title, Books[i].Author,
                Books[i].Possession, Books[i].CheckoutDate, Books[i].ReturnDate);
        }
    }

    fclose(MyLibraryFile);
}