#include "Library.h"
#include "GUI.h"

char BookName[128];
int SizeX;
int SizeY;

void PrintBookStatusWindowText();

void CreateBookStatusWindow()
{
    int MaxX, MaxY;
    SizeX = 50;
    SizeY = 6;

    for (int i = 0; i < MYLIBRARY_MAX_BOOKS; i++)
    {
        if (Books[i].bValidBook && strcmp(BookName, Books[i].Title) == 0)
        {
            SizeY++;
        }
    }

    getmaxyx(stdscr, MaxY, MaxX);

    BookStatusWindow = subwin(MainMenuWindow, SizeY, SizeX, 
                                ((MaxY - 2) / 2) - (SizeY / 2),
                                (MaxX / 2) - (SizeX / 2));
    RefreshLibraryTerm();
}

void RemoveBookStatusWindow()
{
    if (BookStatusWindow)
    {
        delwin(BookStatusWindow);
        BookStatusWindow = NULL;
        
        RefreshLibraryTerm();
    }
}

void DrawBookStatusWindow()
{
    if (BookStatusWindow)
    {
        wclear(BookStatusWindow);

        wborder(BookStatusWindow, WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR);

        PrintBookStatusWindowText();

        wrefresh(BookStatusWindow);
    }
}

void SetBookStatusWindowBookName(const char* NewBookName)
{
    if (NewBookName)
    {
        strcpy(BookName, NewBookName);
    }
    else
    {
        memset(&BookName, 0, sizeof(BookName));
    }
}

void PrintBookStatusWindowText()
{
    int BookCount = 0;
    for (int i = 0; i < MYLIBRARY_MAX_BOOKS; i++)
    {   
        if (Books[i].bValidBook && strcmp(BookName, Books[i].Title) == 0)
        {
            if (strcmp(Books[i].Possession, "Library") == 0)
            {
                mvwprintw(BookStatusWindow, BookCount + 2, 2, "%d '%s' Status: In library", i + 1, Books[i].Title);
            }
            else
            {
                mvwprintw(BookStatusWindow, BookCount + 2, 2, "%d '%s' Status: Available after %s", i + 1, Books[i].Title, Books[i].ReturnDate);
            }

            BookCount++;
        }
    }

    mvwprintw(BookStatusWindow, SizeY - 3, 2, "'t': Try again");
    mvwprintw(BookStatusWindow, SizeY - 2, 2, "'b': Return to main menu");
}
