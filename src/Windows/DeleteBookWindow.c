#include "Library.h"
#include "GUI.h"

static int BookID;
void PrintDeleteBookWindowText();

void CreateDeleteBookWindow()
{
    BookID = -1;

    int MaxX, MaxY, SizeX, SizeY;
    SizeX = 50;
    SizeY = 15;

    getmaxyx(stdscr, MaxY, MaxX);

    DeleteBookWindow = subwin(MainMenuWindow, SizeY, SizeX, 
                                ((MaxY - 2) / 2) - (SizeY / 2),
                                (MaxX / 2) - (SizeX / 2));
    RefreshLibraryTerm();
}

void RemoveDeleteBookWindow()
{
    if (DeleteBookWindow)
    {
        delwin(DeleteBookWindow);
        DeleteBookWindow = NULL;
        
        RefreshLibraryTerm();
    }
}

void DrawDeleteBookMenu()
{
    if (DeleteBookWindow)
    {
        wclear(DeleteBookWindow);

        wborder(DeleteBookWindow, WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR);

        PrintDeleteBookWindowText();

        wrefresh(DeleteBookWindow);
    }
}

void SetDeleteBookMenuBookID(int InID)
{
    BookID = InID;
    RefreshLibraryTerm();
}

void PrintDeleteBookWindowText()
{
    if (BookID > -1)
    {
        mvwprintw(DeleteBookWindow, 2, 2, "Book ID: %d", BookID);
    }
    else
    {
        mvwprintw(DeleteBookWindow, 2, 2, "Book ID: ");
    }

    mvwprintw(DeleteBookWindow, 5, 2, "'t': Try again");
    mvwprintw(DeleteBookWindow, 6, 2, "'b': Return to main menu");
}