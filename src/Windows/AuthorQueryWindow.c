#include "Library.h"
#include "GUI.h"

char Author[128];

void PrintAuthorQueryWindowText();

void CreateAuthorQueryWindow()
{
    memset(&Author, 0, sizeof(Author));

    int MaxX, MaxY, SizeX, SizeY;
    SizeX = 40;
    SizeY = 10;

    getmaxyx(stdscr, MaxY, MaxX);

    AuthorQueryWindow = subwin(MainMenuWindow, SizeY, SizeX, 
                                ((MaxY - 2) / 2) - (SizeY / 2),
                                (MaxX / 2) - (SizeX / 2));
    RefreshLibraryTerm();
}

void RemoveAuthorQueryWindow()
{
    if (AuthorQueryWindow)
    {
        delwin(AuthorQueryWindow);
        AuthorQueryWindow = NULL;
        
        RefreshLibraryTerm();
    }
}

void DrawAuthorQueryWindow()
{
    if (AuthorQueryWindow)
    {
        wclear(AuthorQueryWindow);

        wborder(AuthorQueryWindow, WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR);

        PrintAuthorQueryWindowText();

        wrefresh(AuthorQueryWindow);
    }
}

void SetAuthorQueryWindowAuthor(const char* InAuthor)
{
    if (InAuthor)
    {
        strcpy(Author, InAuthor);
    }
    else
    {
        memset(&Author, 0, sizeof(Author));
    }

    RefreshLibraryTerm();
}

void PrintAuthorQueryWindowText()
{
    mvwprintw(AuthorQueryWindow, 2, 2, "Author: %s", Author);

    mvwprintw(AuthorQueryWindow, 6, 2, "'t': Try again");
    mvwprintw(AuthorQueryWindow, 7, 2, "'b': Return to main menu");
}
