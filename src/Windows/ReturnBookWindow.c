#include "Library.h"
#include "GUI.h"

int BookID;
char CurrentDate[32];
double Fine;
void PrintReturnBookWindowText();

void CreateReturnBookWindow()
{
    BookID = -1;
    memset(&CurrentDate, 0, sizeof(CurrentDate));
    Fine = -1.0;

    int MaxX, MaxY, SizeX, SizeY;
    SizeX = 50;
    SizeY = 14;

    getmaxyx(stdscr, MaxY, MaxX);

    ReturnBookWindow = subwin(MainMenuWindow, SizeY, SizeX, 
                                ((MaxY - 2) / 2) - (SizeY / 2),
                                (MaxX / 2) - (SizeX / 2));
    RefreshLibraryTerm();
}

void RemoveReturnBookWindow()
{
    if (ReturnBookWindow)
    {
        delwin(ReturnBookWindow);
        ReturnBookWindow = NULL;
        
        RefreshLibraryTerm();
    }
}

void DrawReturnBookMenu()
{
    if (ReturnBookWindow)
    {
        wclear(ReturnBookWindow);

        wborder(ReturnBookWindow, WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR);

        PrintReturnBookWindowText();

        wrefresh(ReturnBookWindow);
    }
}

void SetReturnBookMenuBookID(int InID)
{
    BookID = InID;
    RefreshLibraryTerm();
}

void SetReturnBookMenuCurrentDate(const char* InCurrentDate)
{
    if (InCurrentDate)
    {
        strcpy(&CurrentDate[0], InCurrentDate);
    }
    else
    {
        memset(&CurrentDate, 0, sizeof(CurrentDate));
    }

    RefreshLibraryTerm();
}

void SetReturnBookMenuFine(double InFine)
{
    Fine = InFine;
    RefreshLibraryTerm();
}

void PrintReturnBookWindowText()
{
    if (BookID > -1)
    {
        mvwprintw(ReturnBookWindow, 2, 2, "     Book ID: %d", BookID);
    }
    else
    {
        mvwprintw(ReturnBookWindow, 2, 2, "     Book ID: ");
    }
    mvwprintw(ReturnBookWindow, 3, 2, "Current Date: %s", CurrentDate);

    if (Fine >= 0.0)
    {
        mvwprintw(ReturnBookWindow, 4, 2, "        Fine: $%.2lf", Fine);
    }
    else
    {
        mvwprintw(ReturnBookWindow, 4, 2, "        Fine: ");
    }

    mvwprintw(ReturnBookWindow, 9, 2, "'t': Try again");
    mvwprintw(ReturnBookWindow, 10, 2, "'b': Return to main menu");
}
