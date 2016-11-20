#define WINDOW_BORDER_CHAR ACS_CKBOARD

void InitGUI();
void TerminateGUI();

// Clears the screen and redraws everything
void RefreshLibraryTerm();

void SetPromptText(char* Text);
void PrintMessage(const char* Input);
char* GetUserInput();

// Main menu window declarations
WINDOW* MainMenuWindow;
void SetWindowTitle(char* Input);
void DrawMainMenu();

// Add book window declarations
WINDOW* AddBookWindow;
void CreateAddBookWindow();
void UpdateAddBookWindowRecord();
void SetAddBookMenuRecord(LibraryRecord InRecord);
void RemoveAddBookWindow();
void DrawAddBookMenu();

// Delete book window declarations
WINDOW* DeleteBookWindow;
void CreateDeleteBookWindow();
void RemoveDeleteBookWindow();
void DrawDeleteBookMenu();
void SetDeleteBookMenuBookID(int InID);