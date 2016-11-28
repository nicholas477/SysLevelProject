#define WINDOW_BORDER_CHAR ACS_CKBOARD

void InitGUI();
void TerminateGUI();

// Clears the screen and redraws everything
void RefreshLibraryTerm();

void SetPromptText(char* Text);
void PrintMessage(const char* Input);
char* GetUserInput();

// Main menu
WINDOW* MainMenuWindow;
void SetWindowTitle(char* Input);
void DrawMainMenu();

// Add book window
WINDOW* AddBookWindow;
void CreateAddBookWindow();
void UpdateAddBookWindowRecord();
void SetAddBookMenuRecord(LibraryRecord InRecord);
void RemoveAddBookWindow();
void DrawAddBookMenu();

// Delete book window
WINDOW* DeleteBookWindow;
void CreateDeleteBookWindow();
void RemoveDeleteBookWindow();
void DrawDeleteBookMenu();
void SetDeleteBookMenuBookID(int InID);

// Check out window
WINDOW* CheckOutWindow;
void CreateCheckOutWindow();
void RemoveCheckOutWindow();
void DrawCheckOutWindow();
void SetCheckOutWindowUsername(char* Input);
void SetCheckOutWindowBookID(int Input);