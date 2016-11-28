#include "Library.h"
#include "GUI.h"

void PrintCheckOutWindowText();
char* Username = NULL;
int BookID = -1;

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

    if (Username)
    {
        free(Username);
        Username = NULL;
    }
    BookID = -1;
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

void SetCheckOutWindowUsername(char* Input)
{
    if (Username)
    {
        free(Username);
        Username = NULL;
    }

    if (Input)
    {
        Username = strdup(Input);
    }
    else
    {
        Username = Input;
    }

    RefreshLibraryTerm();
}

void SetCheckOutWindowBookID(int Input)
{
    BookID = Input;
    RefreshLibraryTerm();
}

void PrintCheckOutWindowText()
{
    if (Username)
    {
        mvwprintw(CheckOutWindow, 2, 2, "User name: %s", Username);
    }
    else
    {
        mvwprintw(CheckOutWindow, 2, 2, "User name:");
    }

    if (BookID > -1)
    {
        mvwprintw(CheckOutWindow, 3, 2, "  Book ID: %d", BookID);
    }
    else
    {
        mvwprintw(CheckOutWindow, 3, 2, "  Book ID:");
    }

    mvwprintw(CheckOutWindow, 5, 2, "'t': Try again");
    mvwprintw(CheckOutWindow, 6, 2, "'b': Return to main menu");
}