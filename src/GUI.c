#include "Library.h"

#include "GUI.h"

#define BUFFER_LEN 256
#define WINDOW_BORDER_CHAR ACS_CKBOARD

int MaxX, MaxY;
WINDOW* MainWindow = NULL;

void InitGUI()
{
    initscr(); // Start ncurses

    getmaxyx(stdscr, MaxY, MaxX);
    MainWindow = subwin(stdscr, MaxY - 3, MaxX, 1, 0);

    RefreshLibraryTerm();
}

char* GetUserInput()
{
    char* Buffer = calloc(BUFFER_LEN);
    char c;

    int i = 0;

    while (c = getch())
    {
        if (c == '\n')
        {
            RefreshLibraryTerm();
        }
    }

    return Buffer;
}

void RefreshLibraryTerm()
{
    clear();

    wborder(MainWindow, WINDOW_BORDER_CHAR,
        WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
        WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
        WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR);

    char* ProgramName = " Library Program ";
    mvwprintw(stdscr, 0, (MaxX / 2) - (strlen(ProgramName) / 2), ProgramName);

    mvwprintw(stdscr, MaxY-2, 0, "#");
    wrefresh(MainWindow);
    wrefresh(stdscr);
}

void TerminateGUI()
{
    endwin();
}