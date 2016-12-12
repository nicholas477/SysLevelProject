#include "Library.h"
#include "GUI.h"
#include "Input.h"

static void ExitProgram();

int main()
{
    InitGUI();

    SetWindowTitle("Library Program- Menu");
    SetPromptText("#");

    InitLibrary();

    while (true)
    {
        char* Input = GetUserInput();

        if (strlen(Input) == 1)
        {
            switch(Input[0])
            {
                case 'a':
                    // Add book
                    OpenAddBookMenu();
                    break;

                case 'd':
                    // Delete a book
                    OpenDeleteBookMenu();
                    break;

                case 'o':
                    // Check out a book
                    OpenCheckOutWindow();
                    break;

                case 'r':
                    OpenReturnBookWindow();
                    // Return a book
                    break;

                case 's':
                    // Book status query by name
                    OpenStatusQueryWindow();
                    break;

                case 'q':
                    // Book query by author sorted by book title
                    OpenAuthorQueryWindow();
                    break;

                case 'u':
                    // List books checked out by given user
                    OpenUserQueryWindow();
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

        if (Input)
        {
            free(Input);
            Input = NULL;
        }
    }

    ExitProgram();
}

void ExitProgram()
{
    TerminateGUI();
    exit(0);
}
