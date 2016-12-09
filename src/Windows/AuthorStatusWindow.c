#include "Library.h"
#include "GUI.h"

static char AuthorName[128];
static int SizeX;
static int SizeY;

void PrintAuthorStatusWindowText();

void CreateAuthorStatusWindow()
{
    int MaxX, MaxY;
    SizeX = 50;
    SizeY = 6;

    for (int i = 0; i < MYLIBRARY_MAX_BOOKS; i++)
    {
        if (Books[i].bValidBook && strcmp(AuthorName, Books[i].Author) == 0)
        {
            SizeY++;
        }
    }

    getmaxyx(stdscr, MaxY, MaxX);

    AuthorStatusWindow = subwin(MainMenuWindow, SizeY, SizeX, 
                                ((MaxY - 2) / 2) - (SizeY / 2),
                                (MaxX / 2) - (SizeX / 2));
    RefreshLibraryTerm();
}

void RemoveAuthorStatusWindow()
{
    if (AuthorStatusWindow)
    {
        delwin(AuthorStatusWindow);
        AuthorStatusWindow = NULL;
        
        RefreshLibraryTerm();
    }
}

void DrawAuthorStatusWindow()
{
    if (AuthorStatusWindow)
    {
        wclear(AuthorStatusWindow);

        wborder(AuthorStatusWindow, WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                            WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR);

        PrintAuthorStatusWindowText();

        wrefresh(AuthorStatusWindow);
    }
}

void SetAuthorStatusWindowAuthor(const char* InAuthor)
{
    if (InAuthor)
    {
        strcpy(AuthorName, InAuthor);
    }
    else
    {
        memset(&AuthorName, 0, sizeof(AuthorName));
    }
}

void SortBooksByTitle(int* InArr, int Count);

void PrintAuthorStatusWindowText()
{
    // Stick all of the books by this author into an array
    int BooksByThisAuthor[MYLIBRARY_MAX_BOOKS];
    int BookCount = 0;
    for (int i = 0; i < MYLIBRARY_MAX_BOOKS; i++)
    {
        BooksByThisAuthor[i] = -1;

        if (Books[i].bValidBook && strcmp(AuthorName, Books[i].Author) == 0)
        {
            BooksByThisAuthor[BookCount] = i;
            BookCount++;
        }
    }

    SortBooksByTitle(&BooksByThisAuthor[0], BookCount);

    for (int i = 0; i < BookCount; i++)
    {   
        if (strcmp(Books[BooksByThisAuthor[i]].Possession, "Library") == 0)
        {
            mvwprintw(AuthorStatusWindow, i + 2, 2, "%d '%s' In library", BooksByThisAuthor[i] + 1, Books[BooksByThisAuthor[i]].Title);
        }
        else
        {
            mvwprintw(AuthorStatusWindow, i + 2, 2, "%d '%s' Available after %s", BooksByThisAuthor[i] + 1, Books[BooksByThisAuthor[i]].Title, Books[BooksByThisAuthor[i]].ReturnDate);
        }
    }

    mvwprintw(AuthorStatusWindow, SizeY - 3, 2, "'t': Try again");
    mvwprintw(AuthorStatusWindow, SizeY - 2, 2, "'b': Return to main menu");
}

void SortBooksByTitle(int* InArr, int Count)
{
    int Temp = -1;

    for (int i = 0; i < Count; i++)
    {
        for (int j = i + 1; j < Count; j++)
        {
            if (strcmp(Books[InArr[i]].Title, Books[InArr[j]].Title) > 0)
            {
                Temp = InArr[i];
                InArr[i] = InArr[j];
                InArr[j] = Temp;
            }
        }
    }
}
