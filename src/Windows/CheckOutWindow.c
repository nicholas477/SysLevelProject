#include "Library.h"
#include "GUI.h"

void PrintCheckOutWindowText();
char* Username = NULL;

void CreateCheckOutWindow()
{
    int MaxX, MaxY, SizeX, SizeY;
    SizeX = 50;
    SizeY = 15;

    getmaxyx(stdscr, MaxY, MaxX);

    CheckOutWindow = subwin(MainMenuWindow, SizeY, SizeX, 
                                ((MaxY - 2) / 2) - (SizeY / 2),
                                (MaxX / 2) - (SizeX / 2));
    RefreshLibraryTerm();
}

void RemoveCheckOutWindow()
{
    if (CheckOutWindow)
    {
        delwin(CheckOutWindow);
        CheckOutWindow = NULL;
        
        RefreshLibraryTerm();
    }
}

void DrawCheckOutWindow()
{
    if (CheckOutWindow)
    {
        wclear(CheckOutWindow);

        wborder(CheckOutWindow, WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR);

        PrintCheckOutWindowText();

        wrefresh(CheckOutWindow);
    }
}

void PrintCheckOutWindowText()
{
    mvwprintw(DeleteBookWindow, 2, 2, "User name: ");

    mvwprintw(DeleteBookWindow, 5, 2, "'t': Try again");
    mvwprintw(DeleteBookWindow, 6, 2, "'b': Return to main menu");
}