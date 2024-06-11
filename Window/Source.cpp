//// This is the file our WinMain program run
//// Only has WinMain Function


// Include header
#include "Window.h"
#include "Resource.h" // Contain data
#include "Defined.h"


// Global data
// ListOfUsers* listOfUser = nullptr;
// ListOfUsers* listOfUser = nullptr;



// When creating window, there are three things to do
// 1. Register your custom window
// 2. Create window
// 3. Send message to window procedures



int APIENTRY WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow){
     /***************************************************************
     *                       Import File                    *
     *************************************************************/
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    


    // ===============================
    // Section: Setting the game
    // ===============================
    RedirectIOToConsole();
    CreateNewDirectory(FOLDER_USER_W);
    CreateNewDirectory(FOLDER_DATA_W);
    // listOfUser->getListFromFile();



    // ===============================
    // Section: Create main window
    // ===============================

    // Register multiple window used in the game
    RegWindows(hInstance);

    // Get name of main window / menu window
    WCHAR windowName[MAX_LOADSTRING] = { 0 };
    LoadStringW(hInstance, IDC_WINDOW, windowName, MAX_LOADSTRING);

    // Create data storage of window style
    WindowData* windowData = new WindowData(0, windowName, windowName,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        0, 0, 400, 400, NULL, NULL, hInstance, NULL);

    // Create window class that store window data and create window
    WindowMenu* mainMenu = new WindowMenu(windowData);
    windowData = nullptr; // Release windata pointer

    // Get message to main thread!!!
    MSG msg = { 0 };
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOW));
    
    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // Release Main window
    delete mainMenu;
    return static_cast<int>(msg.wParam);
}
