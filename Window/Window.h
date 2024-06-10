#pragma once

// === Include Directives ===
#include "Data.h"


// === Constants ===
// extern ListOfUsers* listOfUser;




/**
 * @brief Register multiple window style for this game
 * @param hInstance a handle to an instance of a module (typically, a DLL or an EXE)
 * @return VOID mean nothing
 * @note Can be modified to add more window styles
 */
VOID RegWindows(HINSTANCE hInstance);
ATOM RegWindowStyle(
    UINT      style,
    WNDPROC   lpfnWndProc,
    HINSTANCE hInstance,
    LPCWSTR    lpszMenuName,
    LPCWSTR    lpszClassName
);



/**
 * @brief Data storage for window class, can easily modify class style
 */
class WindowData
{
private:

    DWORD wExStyle; // extra style;
    LPCWSTR wClassName; // window template name
    LPCWSTR wWindowName; // window name
    DWORD wStyle; // basic style
    int wX, wY; // coordinate of window
    int wW, wH; // width and height of window 
    HWND hParent; // Handle to parent window
    HMENU hMenu; // Handle to menu tab
    HINSTANCE hInstance; // handle to the instance of the module to be associated with the window
    LPVOID    lpParam; // Additional data to draw

public:

    WindowData(const WindowData&) = delete; // Deactivated
    WindowData& operator= (const WindowData&) = delete; // Deactivated
    WindowData(
        DWORD w_Exstyle = NULL,
        LPCWSTR w_Class = L"WINDOW",
        LPCWSTR w_Name = L"Empty window",
        DWORD w_Style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        int w_X = 0, int w_Y = 0, int w_W = 1000, int w_H = 1000,
        HWND h_Parent = NULL, HMENU h_Menu = NULL,
        HINSTANCE h_Instance = NULL, LPVOID w_lpParam = NULL  );
    ~WindowData() {}; // Seft delete

    // Get data
    HINSTANCE GetHINSTANCE() const { return hInstance; };
    HWND GetWindow(); // Create window and return handle

};





/**
 * @brief Window Template class that defined base window with default
 * function.
 * @note Can be overloaded in children class to modify their behaviors
 */
class WindowTemplate
{
private: // Variable

    WindowData* wData;
    HWND hWnd = NULL;

protected:

    // Create window
    virtual BOOL CreateMyWindow();

    // virtual for overriding
    virtual BOOL GetCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { return true; }
    virtual BOOL GetKeyUp(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { return true; }
    virtual BOOL GetKeyDown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { return true; }

    // Define the static helper function
    static BOOL StaticGetCommand(WindowTemplate* window, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static BOOL StaticGetKeyUp(WindowTemplate* window, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static BOOL StaticGetKeyDown(WindowTemplate* window, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public: // Function

    WindowTemplate(WindowData* ptr = nullptr) : wData(ptr) { CreateMyWindow(); };
    ~WindowTemplate() { delete wData; };
    WindowTemplate(const WindowTemplate&) = delete; // Deactivate
    WindowTemplate& operator= (const WindowTemplate&) = delete; // Deactivate

    // Get value
    HWND GetHWND() const { return hWnd; }
    HINSTANCE GetHINSTANCE() const { return wData->GetHINSTANCE(); }

    // Make WndProc static
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private: // Function

    // Check if the window is a child window
    BOOL IsChildWindow() const { return (GetParent(hWnd) != NULL); };
};




/**
 * @brief WindowMain class that is derived from base window template
 * @note Handle menu
 */
class WindowMenu : public WindowTemplate
{
private: // Variable
    List<UserName>* current_player = { 0 };
    

public: // Function

    WindowMenu(WindowData* data = nullptr) : WindowTemplate(data) { CreateMyWindow(); };

private: // Function

    // Override CreateMyWindow to create the button
    BOOL CreateMenuScreen();
    BOOL CreateMyWindow() override;

    // Override GetCommand to handle button events
    BOOL GetCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

};


/**
 * @brief DialogProc for managing dialog
 */
LRESULT CALLBACK AboutDialog(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK UserDialog(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LeaderboardDialog(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK NewGameDialog(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

/**
 * @brief WindowGame class that is derived from base window template
 * @note Handle Gameplay
 */
class WindowGame : public WindowTemplate
{
private: // Variable

    PlayerData* pGame = { 0 };

private: // Function

    // Override to handle button events
    BOOL GetCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
    BOOL GetKeyDown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

    void DrawTopBox(HDC hdc, RECT rect);
    void DrawBottomBox(HDC hdc, RECT rect);
    void DrawMatrix(HDC hdc, RECT rect);

    int CheckUserInput(HWND hWnd);


public: // Function

    WindowGame(WindowData* data = nullptr) : WindowTemplate(data) { CreateMyWindow(); };
    ~WindowGame() {};

    void SetGame(PlayerData* data = NULL) { pGame = data; };
    // Override CreateMyWindow to create the button
    BOOL CreateMyWindow() override;
};



/**
 * @brief Utility function
 */


// Open file dialog
bool OpenFileDialog(HWND owner, LPWSTR fileName, DWORD fileNameSize);

// Show text box
void ShowText_About(HWND hWnd);
void ShowText_Information(HWND hWnd);
void ShowText_Shortcut(HWND hWnd);


// Layout of window
BOOL CenterWindow(HWND hWnd);
void DrawRectCentered(HDC hdc, RECT rect, const wchar_t* str, int total, COLORREF rectColor, COLORREF textColor);
COLORREF generateColorRefFromIndex(int index, int x = 2);
void DrawCell(HDC hdc, RECT cellRect, int value, COLORREF cellColor);
wchar_t* FindLongestStr();
