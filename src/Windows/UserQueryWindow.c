#include "Library.h"
#include "GUI.h"

static char Username[128];
static char CurrentDate[16];

void PrintUserQueryWindowText();

void CreateUserQueryWindow()
{
    memset(&Username, 0, sizeof(Username));
    memset(&CurrentDate, 0, sizeof(CurrentDate));

    int MaxX, MaxY, SizeX, SizeY;
    SizeX = 40;
    SizeY = 10;

    getmaxyx(stdscr, MaxY, MaxX);

    UserQueryWindow = subwin(MainMenuWindow, SizeY, SizeX, 
                                ((MaxY - 2) / 2) - (SizeY / 2),
                                (MaxX / 2) - (SizeX / 2));
    RefreshLibraryTerm();
}

void RemoveUserQueryWindow()
{
    if (UserQueryWindow)
    {
        delwin(UserQueryWindow);
        UserQueryWindow = NULL;
        
        RefreshLibraryTerm();
    }
}

void DrawUserQueryWindow()
{
    if (UserQueryWindow)
    {
        wclear(UserQueryWindow);

        wborder(UserQueryWindow, WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR);

        PrintUserQueryWindowText();

        wrefresh(UserQueryWindow);
    }
}

void SetUserQueryWindowUsername(const char* InUsername)
{
    if (InUsername)
    {
        strcpy(Username, InUsername);
    }
    else
    {
        memset(&Username, 0, sizeof(Username));
    }

    RefreshLibraryTerm();
}

void SetUserQueryWindowDate(const char* InDate)
{
    if (InDate)
    {
        strcpy(CurrentDate, InDate);
    }
    else
    {
        memset(&CurrentDate, 0, sizeof(CurrentDate));
    }

    RefreshLibraryTerm();
}

void PrintUserQueryWindowText()
{
    mvwprintw(UserQueryWindow, 2, 2, "Current Date: %s", CurrentDate);
    mvwprintw(UserQueryWindow, 3, 2, "    Username: %s", Username);

    mvwprintw(UserQueryWindow, 6, 2, "'t': Try again");
    mvwprintw(UserQueryWindow, 7, 2, "'b': Return to main menu");
}
