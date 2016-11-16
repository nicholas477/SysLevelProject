#include "Library.h"
#include "GUI.h"

#define BUFFER_LEN 256
#define WINDOW_BORDER_CHAR ACS_CKBOARD

int MaxX, MaxY;
WINDOW* MainWindow = NULL;

void InitGUI()
{
    initscr(); // Start ncurses
    noecho();

    getmaxyx(stdscr, MaxY, MaxX);
    MainWindow = subwin(stdscr, MaxY - 3, MaxX, 1, 0);

    RefreshLibraryTerm();
}

char* GetUserInput()
{
    wmove(stdscr, MaxY-2, 1);

    char* Buffer = calloc(BUFFER_LEN, 1);
    char c;

    int i = 0;

    while ((c = getch()) != '\n' && i < BUFFER_LEN)
    {
        // Backspace keys
        if (c == 127 || c == 8)
        {
            if (i > 0)
            {
                i--;
                Buffer[i] = '\0';

                // Move over the cursor and delete the char
                int x, y;
                getyx(stdscr, y, x);
                
                mvwdelch(stdscr, y, x-1);
            }
        }
        else
        {
            Buffer[i] = c;
            i++;

            addch(c);
        }
    }

    RefreshLibraryTerm();

    if (i)
    {
        return Buffer;
    }
    else
    {
        return NULL;
    }
}

void PrintErrorMessage(const char* Input)
{
    mvwprintw(stdscr, MaxY-1, 0, Input);
    wmove(stdscr, MaxY-2, 1);
    wrefresh(stdscr);
}

void RefreshLibraryTerm()
{
    wclear(stdscr);
    wclear(MainWindow);

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