#include "Library.h"
#include "GUI.h"

int BookID;
void PrintReturnBookWindowText();

void CreateReturnBookWindow()
{
    BookID = -1;

    int MaxX, MaxY, SizeX, SizeY;
    SizeX = 50;
    SizeY = 15;

    getmaxyx(stdscr, MaxY, MaxX);

    ReturnBookWindow = subwin(MainMenuWindow, SizeY, SizeX, 
                                ((MaxY - 2) / 2) - (SizeY / 2),
                                (MaxX / 2) - (SizeX / 2));
    RefreshLibraryTerm();
}

void RemoveReturnBookWindow()
{
    if (ReturnBookWindow)
    {
        delwin(ReturnBookWindow);
        ReturnBookWindow = NULL;
        
        RefreshLibraryTerm();
    }
}

void DrawReturnBookMenu()
{
    if (ReturnBookWindow)
    {
        wclear(ReturnBookWindow);

        wborder(ReturnBookWindow, WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR);

        PrintReturnBookWindowText();

        wrefresh(ReturnBookWindow);
    }
}

void SetReturnBookMenuBookID(int InID)
{
    BookID = InID;
    RefreshLibraryTerm();
}

void PrintReturnBookWindowText()
{
    if (BookID > -1)
    {
        mvwprintw(ReturnBookWindow, 2, 2, "Book ID: %d", BookID);
    }
    else
    {
        mvwprintw(ReturnBookWindow, 2, 2, "Book ID: ");
    }

    mvwprintw(ReturnBookWindow, 5, 2, "'t': Try again");
    mvwprintw(ReturnBookWindow, 6, 2, "'b': Return to main menu");
}
