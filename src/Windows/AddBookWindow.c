#include "Library.h"
#include "GUI.h"

LibraryRecord AddBookMenuRecord;
void PrintAddBookMenuText();

void CreateAddBookWindow()
{
    memset(&AddBookMenuRecord, 0, sizeof(AddBookMenuRecord));
    
    int MaxX, MaxY, SizeX, SizeY;
    SizeX = 50;
    SizeY = 15;

    getmaxyx(stdscr, MaxY, MaxX);

    AddBookWindow = subwin(MainMenuWindow, SizeY, SizeX, 
                                ((MaxY - 2) / 2) - (SizeY / 2),
                                (MaxX / 2) - (SizeX / 2));
    RefreshLibraryTerm();
}

void RemoveAddBookWindow()
{
    if (AddBookWindow)
    {
        delwin(AddBookWindow);
        AddBookWindow = NULL;
        
        RefreshLibraryTerm();
    }
}

void DrawAddBookMenu()
{
    if (AddBookWindow)
    {
        wclear(AddBookWindow);

        wborder(AddBookWindow, WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                        WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                        WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR,
                        WINDOW_BORDER_CHAR, WINDOW_BORDER_CHAR);

        PrintAddBookMenuText();

        wrefresh(AddBookWindow);
    }
}

void PrintAddBookMenuText()
{
    mvwprintw(AddBookWindow, 2, 2, " Title: %s", AddBookMenuRecord.Title);
    mvwprintw(AddBookWindow, 3, 2, "Author: %s", AddBookMenuRecord.Author);
    mvwprintw(AddBookWindow, 5, 2, "'t': Try again");
    mvwprintw(AddBookWindow, 6, 2, "'b': Return to main menu");
}

void SetAddBookMenuRecord(LibraryRecord InRecord)
{
    AddBookMenuRecord = InRecord;

    RefreshLibraryTerm();
}