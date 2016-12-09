#include "Library.h"
#include "GUI.h"
#include "Input.h"
#include "Utils.h"

void OpenAddBookMenu()
{
    CreateAddBookWindow();
    SetPromptText("Title:");

    bool EnteringAuthor = false;
    bool Finished = false;
    LibraryRecord NewRecord;
    memset(&NewRecord, 0, sizeof(NewRecord));

    while (true)
    {
        if (EnteringAuthor)
        {
            SetPromptText("Author:");
        }
        else
        {
            SetPromptText("Title:");
        }

        char* Input = GetUserInput();

        if (strlen(Input) == 1)
        {
            switch(Input[0])
            {
                case 'b':
                    // Return to menu
                    RemoveAddBookWindow();
                    SetPromptText("#");
                    return;
                    break;

                case 't':
                    // Retry key, reset all the data and menu
                    memset(&NewRecord.Title[0], 0, sizeof(NewRecord.Title));
                    memset(&NewRecord.Author[0], 0, sizeof(NewRecord.Author));
                    SetAddBookMenuRecord(NewRecord);
                    EnteringAuthor = false;
                    break;

                default:
                    PrintMessage("Unrecognized input!");
                    break;
            }
        }
        else if (strlen(Input) > 1)
        {
            if (!EnteringAuthor)
            {
                // Copy over the string
                memcpy(&NewRecord.Title[0], Input, strlen(Input));
            }
            else
            {
                // Copy over the string
                memcpy(&NewRecord.Author[0], Input, strlen(Input));
                Finished = true;
            }

            EnteringAuthor = !EnteringAuthor;

            SetAddBookMenuRecord(NewRecord);
        }

        if (Input)
        {
            free(Input);
            Input = NULL;
        }

        if (Finished)
        {
            AddBook(NewRecord);
            RemoveAddBookWindow();

            SetPromptText("#");

            // Print out the successful message
            char Buffer[256];
            snprintf(Buffer, 256, "Added book '%s' by %s.", NewRecord.Title, NewRecord.Author);
            PrintMessage(&Buffer[0]);
            return;
        }
    }
}

void OpenDeleteBookMenu()
{
    CreateDeleteBookWindow();
    SetPromptText("Book ID:");

    int BookID = -1;
    bool ConfirmDeleteBook = false;

    while (true)
    {
        char* Input = GetUserInput();

        if (strlen(Input) > 0)
        {
            if (IsStringNumber(Input))
            {
                BookID = atoi(Input);

                SetDeleteBookMenuBookID(BookID);

                if (BookExists(BookID))
                {
                    char Buffer[256];
                    char* BookName = GetBookName(BookID);
                    SetPromptText("Confirm (y/n):");
                    snprintf(Buffer, 256, "Are you sure you want to delete book '%s'? (Y/N)", BookName);
                    PrintMessage(&Buffer[0]);
                    ConfirmDeleteBook = true;
                    free(BookName);
                }
                else
                {
                    char Buffer[256];
                    snprintf(Buffer, 256, "Error: Book number %d doesn't exist!", BookID);
                    PrintMessage(&Buffer[0]);
                }
            }
            else if (strlen(Input) == 1)
            {
                Input[0] = tolower(Input[0]);
                switch(Input[0])
                {
                    case 'b':
                        // Return to menu
                        RemoveDeleteBookWindow();
                        SetPromptText("#");
                        return;
                        break;

                    case 't':
                        // Retry key, reset all the data and menu
                        BookID = -1;
                        SetDeleteBookMenuBookID(BookID);
                        ConfirmDeleteBook = false;
                        SetPromptText("Book ID:");
                        break;

                    case 'y':
                        if (ConfirmDeleteBook)
                        {
                            DeleteBook(BookID);
                            RemoveDeleteBookWindow();
                            SetPromptText("#");
                            return;
                            break;
                        }

                    case 'n':
                        if (ConfirmDeleteBook)
                        {
                            BookID = -1;
                            SetDeleteBookMenuBookID(BookID);
                            ConfirmDeleteBook = false;
                            SetPromptText("Book ID:");
                            break;
                        }

                    default:
                        PrintMessage("Unrecognized input!");
                        break;
                }
            }
            else
            {
                PrintMessage("Unrecognized input!");
            }
        }

        if (Input)
        {
            free(Input);
        }
    }
}

void OpenCheckOutWindow()
{
    CreateCheckOutWindow();
    SetPromptText("Username:");

    int BookID = -1;
    char* Username = NULL;
    while (true)
    {
        char* Input = GetUserInput();
        if (strlen(Input) > 0)
        {
            // If we have a username then we're inputing the book id
            if (Username && IsStringNumber(Input))
            {
                BookID = atoi(Input);

                if (BookExists(BookID))
                {
                    SetCheckOutWindowBookID(BookID);

                    CheckOutBook(Username, BookID);

                    if (Username)
                    {
                        free(Username);
                        Username = NULL;
                    }

                    RemoveCheckOutWindow();
                    SetPromptText("#");

                    char* BookName = GetBookName(BookID);
                    char Buffer[256];
                    snprintf(Buffer, 256, "Book '%s' checked out successfully!", BookName);
                    PrintMessage(&Buffer[0]);
                    free(BookName);
                    return;
                }
                else
                {
                    char Buffer[256];
                    snprintf(Buffer, 256, "Error: Book number %d doesn't exist!", BookID);
                    PrintMessage(&Buffer[0]);
                }
            }
            else if (strlen(Input) == 1)
            {
                switch(Input[0])
                {
                    case 'b':
                        // Return to menu
                        if (Username)
                        {
                            free(Username);
                            Username = NULL;
                        }
                        BookID = -1;
                        RemoveCheckOutWindow();
                        SetPromptText("#");
                        return;
                        break;

                    case 't':
                        // Retry key, reset all the data and menu
                        if (Username)
                        {
                            free(Username);
                            Username = NULL;
                        }
                        BookID = -1;
                        SetCheckOutWindowUsername(Username);
                        SetPromptText("Username:");
                        break;

                    default:
                        PrintMessage("Unrecognized input!");
                        break;
                }
            }
            else if (Username == NULL)
            {
                Username = strdup(Input);

                SetCheckOutWindowUsername(Username);

                if (GetNumBooksCheckedOut(Username) < 3)
                {
                    SetPromptText("Book ID:");
                }
                else
                {
                    SetCheckOutWindowUsername(NULL);
                    char Buffer[256];
                    snprintf(Buffer, 256, "Error: User %s has 3 or more books checked out!", Username);
                    PrintMessage(&Buffer[0]);

                    if (Username)
                    {
                        free(Username);
                        Username = NULL;
                    }
                }
            }
        }

        if (Input)
        {
            free(Input);
            Input = NULL;
        }
    }

    if (Username)
    {
        free(Username);
        Username = NULL;
    }
}

void OpenReturnBookWindow()
{
    CreateReturnBookWindow();
    SetPromptText("Book ID:");

    int BookID = -1;
    char* CurrentDate = NULL;
    //If this is true, we are asking for the user to input the date
    bool EnteringDate = false;
    bool bWaitingConfirmation = false;

    // While true: keep getting user input even if the user inputs crap
    while (true)
    {
        // This function will wait until the user presses enter
        char* Input = GetUserInput();

        if (strlen(Input) > 0 && (IsStringNumber(Input) || IsLegalDate(Input)))
        {
            // If we are not entering date, we are asking for the book id
            if (!EnteringDate)
            {
                if (IsStringNumber(Input))
                {
                    BookID = atoi(Input);

                    if (BookExists(BookID))
                    {
                        SetReturnBookMenuBookID(BookID);
                        SetPromptText("Current Date:");
                        EnteringDate = true;
                    }
                    else
                    {
                        char Buffer[256];
                        snprintf(Buffer, 256, "Error: Book number %d doesn't exist!", BookID);
                        PrintMessage(&Buffer[0]);
                    }
                }
            }
            else
            {
                // We are asking for the date
                if (IsLegalDate(Input))
                {
                    CurrentDate = strdup(Input);
                    SetReturnBookMenuCurrentDate(Input);

                    SetReturnBookMenuFine(GetBookFine(CurrentDate, BookID));
                    SetPromptText("Confirm:");
                    bWaitingConfirmation = true;
                }
                else
                {
                    PrintMessage("Error: Illegal input date!");
                }
            }
        }
        else if (strlen(Input) == 1)
        {
            // If the input is not a number, then check if the user has entered a single character
            switch(Input[0])
            {
                case 'b':
                    // Return to menu
                    RemoveReturnBookWindow();
                    SetPromptText("#");
                    return;
                    break;

                case 't':
                    // Retry key, reset all the data and menu
                    BookID = -1;
                    SetReturnBookMenuBookID(BookID);
                    free(CurrentDate);
                    CurrentDate = NULL;
                    SetReturnBookMenuCurrentDate(NULL);
                    SetPromptText("Book ID:");
                    break;

                default:
                    if (bWaitingConfirmation)
                    {
                        ReturnBook(BookID);

                        RemoveReturnBookWindow();
                        SetPromptText("#");
                        return;
                    }
                    else
                    {
                        PrintMessage("Unrecognized input!");
                    }
                    break;
            }
        }
        else
        {
            PrintMessage("Unrecognized input!");
        }

        // GetUserInput() allocates mem that we need to free
        if (Input)
        {
            free(Input);
        }
    }
}

void OpenStatusQueryWindow()
{
    char BookName[128];
    memset(&BookName, 0, sizeof(BookName));

    SetBookStatusWindowBookName(NULL);

    CreateStatusQueryWindow();
    SetPromptText("Book Name:");

    while (true)
    {
        char* Input = GetUserInput();

        if (strlen(Input) > 1)
        {
            int BookID = GetBookIDByName(Input);
            if (BookID > -1)
            {
                SetStatusQueryWindowBookID(BookID);

                SetBookStatusWindowBookName(Input);
                CreateBookStatusWindow();
            }
            else
            {
                char Buffer[256];
                snprintf(Buffer, 256, "Error: Book '%s' doesn't exist!", Input);
                PrintMessage(&Buffer[0]);
            }
        }
        else if (strlen(Input) == 1)
        {
            // If the input is not a number, then check if the user has entered a single character
            switch(Input[0])
            {
                case 'b':
                    // Return to menu
                    SetBookStatusWindowBookName(NULL);
                    RemoveBookStatusWindow();
                    RemoveStatusQueryWindow();
                    SetPromptText("#");
                    return;
                    break;

                case 't':
                    // Retry key, reset all the data and menu
                    SetPromptText("Book ID:");
                    SetBookStatusWindowBookName(NULL);
                    RemoveBookStatusWindow();
                    memset(&BookName, 0, sizeof(BookName));
                    SetStatusQueryWindowBookID(-1);
                    break;

                default:
                    PrintMessage("Unrecognized input!");
                    break;
            }
        }
        else
        {
            PrintMessage("Unrecognized input!");
        }

        if (Input)
        {
            free(Input);
        }
    }

}