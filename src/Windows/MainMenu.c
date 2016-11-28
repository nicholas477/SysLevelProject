#include "Library.h"
#include "GUI.h"

char* WindowTitle = NULL;

void PrintMenuText();

void DrawMainMenu()
{
    int MaxX, MaxY;
    getmaxyx(stdscr, MaxY, MaxX);

    wclear(MainMenuWindow);

    wborder(MainMenuWindow, WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                        WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                        WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                        WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR);

    if (WindowTitle)
    {
        wattron(MainMenuWindow, A_REVERSE);
        mvwprintw(MainMenuWindow, 0, (MaxX / 2) - (strlen(WindowTitle) / 2), WindowTitle);
        wattroff(MainMenuWindow, A_REVERSE);
    }

    PrintMenuText();

    wrefresh(MainMenuWindow);
}

void PrintMenuText()
{
    mvwprintw(MainMenuWindow, 2, 2, "'a': Add a book to the library");
    mvwprintw(MainMenuWindow, 3, 2, "'d': Delete a book from the library");
    mvwprintw(MainMenuWindow, 4, 2, "'o': Check out a book");
    mvwprintw(MainMenuWindow, 5, 2, "'r': Return a book");
    mvwprintw(MainMenuWindow, 6, 2, "'s': Query a book's status");
    mvwprintw(MainMenuWindow, 7, 2, "'q': Query a book's status by author sorted by book title");
    mvwprintw(MainMenuWindow, 8, 2, "'u': List books checked out by a user");
    mvwprintw(MainMenuWindow, 9, 2, "'x': Quit");
}

void SetWindowTitle(char* Input)
{
    if (WindowTitle)
    {
        free(WindowTitle);
        WindowTitle = NULL;
    }

    WindowTitle = strdup(Input);

    RefreshLibraryTerm();
}