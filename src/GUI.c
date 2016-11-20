#include "Library.h"
#include "GUI.h"

#define MAX_WINDOWS 5
#define BUFFER_LEN 256

int MaxX, MaxY;
WINDOW* Windows[MAX_WINDOWS];
char* PromptText = NULL;

void ResetCursor();

void InitGUI()
{
    initscr(); // Start ncurses
    noecho();

    getmaxyx(stdscr, MaxY, MaxX);
    MainMenuWindow = subwin(stdscr, MaxY - 2, MaxX, 0, 0);

    RefreshLibraryTerm();
}

void RefreshLibraryTerm()
{
    wclear(stdscr);

    DrawMainMenu();

    DrawAddBookMenu();

    DrawDeleteBookMenu();

    ResetCursor();
}

void ResetCursor()
{
    if (PromptText)
    {
        mvwprintw(stdscr, MaxY-2, 0, "%s", PromptText);
        wmove(stdscr, MaxY-2, strlen(PromptText) + 1);
        wrefresh(stdscr);
    }
}

bool IsValidChar(char In)
{
    if (In < 32) // 32 is space
        return false;

    return true;
}

// TO DO: filter this input so that only ascii keys are returned
char* GetUserInput()
{
    while (true)
    {
        ResetCursor();

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
            else if (IsValidChar(c))
            {
                Buffer[i] = c;
                i++;

                addch(c);
            }
        }

        if (i)
        {
            RefreshLibraryTerm();

            return Buffer;
        }
    }
}

void SetPromptText(char* Text)
{
    if (PromptText)
    {
        free(PromptText);
    }

    PromptText = strdup(Text);

    RefreshLibraryTerm();
}

void PrintMessage(const char* Input)
{
    mvwprintw(stdscr, MaxY-1, 0, Input);

    ResetCursor();

    wrefresh(stdscr);
}

void TerminateGUI()
{
    endwin();
}