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

// Delete book window
WINDOW* ReturnBookWindow;
void CreateReturnBookWindow();
void RemoveReturnBookWindow();
void DrawReturnBookMenu();
void SetReturnBookMenuBookID(int InID);
void SetReturnBookMenuCurrentDate(const char* InCurrentDate);
void SetReturnBookMenuFine(double InFine);

// Status query window
WINDOW* StatusQueryWindow;
void CreateStatusQueryWindow();
void RemoveStatusQueryWindow();
void DrawStatusQueryWindow();
void SetStatusQueryWindowBookID(int InBookID);

// Book status window
WINDOW* BookStatusWindow;
void CreateBookStatusWindow();
void RemoveBookStatusWindow();
void DrawBookStatusWindow();
void SetBookStatusWindowBookName(const char* NewBookName);

// Author Query window
WINDOW* AuthorQueryWindow;
void CreateAuthorQueryWindow();
void RemoveAuthorQueryWindow();
void DrawAuthorQueryWindow();
void SetAuthorQueryWindowAuthor(const char* InAuthor);

// Author status window
WINDOW* AuthorStatusWindow;
void CreateAuthorStatusWindow();
void RemoveAuthorStatusWindow();
void DrawAuthorStatusWindow();
void SetAuthorStatusWindowAuthor(const char* InAuthor);

// User Query window
WINDOW* UserQueryWindow;
void CreateUserQueryWindow();
void RemoveUserQueryWindow();
void DrawUserQueryWindow();
void SetUserQueryWindowUsername(const char* InUsername);
void SetUserQueryWindowDate(const char* InDate);

// User status window
WINDOW* UserStatusWindow;
void CreateUserStatusWindow();
void RemoveUserStatusWindow();
void DrawUserStatusWindow();
void SetUserStatusWindowUsername(const char* InUsername);
void SetUserStatusWindowCurrentDate(const char* InCurrentDate);