#include "Library.h"
#include "GUI.h"

static char Username[128];
static char CurrentDate[16];
static int SizeX;
static int SizeY;

void PrintUserStatusWindowText();

void CreateUserStatusWindow()
{
    if (UserStatusWindow)
    {
        RemoveUserStatusWindow();
    }

    int MaxX, MaxY;
    SizeX = 50;
    SizeY = 7;

    for (int i = 0; i < MYLIBRARY_MAX_BOOKS; i++)
    {
        if (Books[i].bValidBook && strcmp(Username, Books[i].Possession) == 0)
        {
            SizeY++;
        }
    }

    getmaxyx(stdscr, MaxY, MaxX);

    UserStatusWindow = subwin(MainMenuWindow, SizeY, SizeX, 
                                ((MaxY - 2) / 2) - (SizeY / 2),
                                (MaxX / 2) - (SizeX / 2));
    RefreshLibraryTerm();
}

void RemoveUserStatusWindow()
{
    if (UserStatusWindow)
    {
        delwin(UserStatusWindow);
        UserStatusWindow = NULL;
        
        RefreshLibraryTerm();
    }
}

void DrawUserStatusWindow()
{
    if (UserStatusWindow)
    {
        wclear(UserStatusWindow);

        wborder(UserStatusWindow, WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR);

        PrintUserStatusWindowText();

        wrefresh(UserStatusWindow);
    }
}

void SetUserStatusWindowUsername(const char* InUsername)
{
    if (InUsername)
    {
        strcpy(Username, InUsername);
    }
    else
    {
        memset(&Username, 0, sizeof(Username));
    }
}

void SetUserStatusWindowCurrentDate(const char* InCurrentDate)
{
    if (InCurrentDate)
    {
        strcpy(CurrentDate, InCurrentDate);
    }
    else
    {
        memset(&CurrentDate, 0, sizeof(CurrentDate));
    }
}

void PrintUserStatusWindowText()
{
    int BookCount = 0;
    for (int i = 0; i < MYLIBRARY_MAX_BOOKS; i++)
    {   
        if (Books[i].bValidBook && strcmp(Books[i].Possession, Username) == 0)
        {
            if (CompareDates(CurrentDate, Books[i].ReturnDate) > 0)
            {
                mvwprintw(UserStatusWindow, BookCount + 2, 2, "%d, '%s', %s, %s Over Due", i + 1, Books[i].Title, Books[i].CheckoutDate, Books[i].ReturnDate);
            }
            else
            {
                mvwprintw(UserStatusWindow, BookCount + 2, 2, "%d, '%s', %s, %s", i + 1, Books[i].Title, Books[i].CheckoutDate, Books[i].ReturnDate);
            }
            BookCount++;
        }
    }

    mvwprintw(UserStatusWindow, SizeY - 3, 2, "'t': Try again");
    mvwprintw(UserStatusWindow, SizeY - 2, 2, "'b': Return to main menu");
}