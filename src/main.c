#include "Library.h"
#include "GUI.h"

void ExitProgram();
void OpenBookMenu();
void OpenDeleteBookMenu();

int main()
{
    InitGUI();

    SetWindowTitle("Library Program- Menu");
    SetPromptText("#");

    while (true)
    {
        char* Input = GetUserInput();

        if (strlen(Input) == 1)
        {
            switch(Input[0])
            {
                case 'a':
                    // Add book
                    OpenBookMenu();
                    break;

                case 'd':
                    OpenDeleteBookMenu();
                    // Delete a book
                    break;

                case 'o':
                    // Check out a book
                    break;

                case 'r':
                    // Return a book
                    break;

                case 's':
                    // Book status query by name
                    break;

                case 'q':
                    // Book query by author sorted by book title
                    break;

                case 'u':
                    // List books checked out by given user
                    break;

                case 'x':
                    // Quit
                    ExitProgram();
                    break;

                default:
                    PrintMessage("Unrecognized input!");
                    break;
            }
        }
        else if (strlen(Input) > 1)
        {
            PrintMessage("Unrecognized input!");
        }
    }

    ExitProgram();
}

void OpenBookMenu()
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

bool IsStringNumber(const char* Input)
{
    if (strlen(Input) == 0)
        return false;

    for (int i = 0; i < strlen(Input); i++)
    {
        if (Input[i] < '0' || Input[i] > '9')
            return false;
    }

    return true;
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
                    snprintf(Buffer, 256, "Are you sure you want to delete book '%s'? (Y/N)", GetBookName(BookID));
                    PrintMessage(&Buffer[0]);
                    ConfirmDeleteBook = true;
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
    }
}

void ExitProgram()
{
    TerminateGUI();
    exit(0);
}