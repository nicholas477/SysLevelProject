#include "Library.h"
#include "GUI.h"

int BookID;
LibraryRecord WindowRecord;

void PrintStatusQueryWindowText();

void CreateStatusQueryWindow()
{
    BookID = -1;
    memset(&WindowRecord, 0, sizeof(WindowRecord));

    int MaxX, MaxY, SizeX, SizeY;
    SizeX = 40;
    SizeY = 10;

    getmaxyx(stdscr, MaxY, MaxX);

    StatusQueryWindow = subwin(MainMenuWindow, SizeY, SizeX, 
                                ((MaxY - 2) / 2) - (SizeY / 2),
                                (MaxX / 2) - (SizeX / 2));
    RefreshLibraryTerm();
}

void RemoveStatusQueryWindow()
{
    if (StatusQueryWindow)
    {
        delwin(StatusQueryWindow);
        StatusQueryWindow = NULL;
        
        RefreshLibraryTerm();
    }
}

void DrawStatusQueryWindow()
{
    if (StatusQueryWindow)
    {
        wclear(StatusQueryWindow);

        wborder(StatusQueryWindow, WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR);

        PrintStatusQueryWindowText();

        wrefresh(StatusQueryWindow);
    }
}

void SetStatusQueryWindowBookID(int InBookID)
{
    BookID = InBookID;

    if (InBookID == -1)
    {
        memset(&WindowRecord, 0, sizeof(WindowRecord));
    }
    else
    {
        memcpy(&WindowRecord, &Books[BookID - 1], sizeof(WindowRecord));
    }

    RefreshLibraryTerm();
}

void PrintStatusQueryWindowText()
{
    mvwprintw(StatusQueryWindow, 2, 2, "Book Title: %s", WindowRecord.Title);

    mvwprintw(StatusQueryWindow, 6, 2, "'t': Try again");
    mvwprintw(StatusQueryWindow, 7, 2, "'b': Return to main menu");
}
