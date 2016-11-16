#include "Library.h"
#include "GUI.h"

int main()
{
    InitGUI();

    while (true)
    {
        char* Input = GetUserInput();

        if (Input && strlen(Input) == 1)
        {
            switch(Input[0])
            {
                case 'a':
                    break;
                case 'd':
                    break;
                case 'o':
                    break;
                case 'r':
                    break;
                case 's':
                    break;
                case 'q':
                    break;
                case 'u':
                    break;
                case 'x':
                    exit(0);
                    break;
                default:
                    PrintErrorMessage("Unrecognized input!");
                    break;
            }
        }
        else if (strlen(Input) > 1)
        {
            PrintErrorMessage("Unrecognized input!");
        }
    }

    TerminateGUI();
}