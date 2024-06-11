// Implement for window.h header file
// Need to separate into several file


#include "Window.h"
#include "Resource.h" // Contain data
#include "Library.h" // Include C++ library
#include "Defined.h"




VOID RegWindows(HINSTANCE hInstance) {

    WCHAR title_name[MAX_LOADSTRING] = {0};
    WCHAR window_name[MAX_LOADSTRING] = {0};
    WCHAR user_name[MAX_LOADSTRING] = { 0 };
    LoadStringW(hInstance, IDS_APP_TITLE, title_name, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOW, window_name, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_USER, user_name, MAX_LOADSTRING);


    RegWindowStyle(
        CS_HREDRAW | CS_VREDRAW, WindowMenu::WndProc, hInstance,
        MAKEINTRESOURCEW(IDC_MAIN_MENU), window_name);
    RegWindowStyle(
        CS_HREDRAW | CS_VREDRAW, WindowGame::WndProc, hInstance,
        MAKEINTRESOURCEW(IDC_MAIN_MENU), title_name);
    RegWindowStyle(
        CS_HREDRAW | CS_VREDRAW, WindowTemplate::WndProc, hInstance,
        MAKEINTRESOURCEW(IDC_MAIN_MENU), user_name);
}
ATOM RegWindowStyle(
    UINT      style,
    WNDPROC   lpfnWndProc,
    HINSTANCE hInstance,
    LPCWSTR    lpszMenuName,
    LPCWSTR    lpszClassName)
{
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);

    wc.style = style;
    wc.lpfnWndProc = lpfnWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCEW(IDI_SMALL));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = lpszMenuName;
    wc.lpszClassName = lpszClassName;
    wc.hIconSm = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    if (!RegisterClassExW(&wc)) {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return FALSE;
    }
    return TRUE;
}




// Window data class -----------------------------------------------------------------
WindowData::WindowData(DWORD w_Exstyle,
    LPCWSTR w_Class, LPCWSTR w_Name, DWORD w_Style,
    int w_X, int w_Y, int w_W, int w_H,
    HWND h_Parent, HMENU h_Menu,
    HINSTANCE h_Instance, LPVOID w_lpParam)
{
    this->wExStyle = w_Exstyle;
    this->wClassName = w_Class;
    this->wWindowName = w_Name;
    this->wStyle = w_Style;
    this->wX = w_X; this->wY = w_Y;
    this->wW = w_W; this->wH = w_H;
    this->hParent = h_Parent;
    this->hMenu = h_Menu;
    this->hInstance = h_Instance;
    this->lpParam = w_lpParam;
}

HWND WindowData::GetWindow()
{
    HWND hWnd = CreateWindowExW(
        wExStyle,
        wClassName,
        wWindowName,
        wStyle,
        wX,wY,wW,wH,
        hParent,
        hMenu,
        hInstance,
        lpParam);

    // Check if the window creation was successful
    if (hWnd == NULL) {
        // Retrieve the error code
        DWORD dwError = GetLastError();

        // Buffer to hold the error message
        LPWSTR lpErrorMsg = NULL;

        // Format the error message
        FormatMessageW(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dwError,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPWSTR)&lpErrorMsg,
            0,
            NULL
        );

        // Display error message
        MessageBoxW(NULL, lpErrorMsg, L"Window Creation Failed!", MB_ICONEXCLAMATION | MB_OK);

        // Free the error message buffer
        LocalFree(lpErrorMsg);

        // Exit or handle the error as needed
        return 0; // Or any other appropriate action
    }

    return hWnd;
}





// Window template class --------------------------------------------------
BOOL WindowTemplate::CreateMyWindow()
{
    hWnd = wData->GetWindow();
    // Now modify lpParam associated with the window
    SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)this);

    if (!hWnd) {
        MessageBoxW(NULL, L"Window Creation Failed!", L"Error", MB_ICONERROR);
        ExitProcess(0);
    }
    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);
    return true;
}

BOOL WindowTemplate::StaticGetCommand(WindowTemplate* window, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (window && window->wData) {
        // Call the virtual GetCommand method
        return window->GetCommand(hWnd, message, wParam, lParam);
    }
    return true; // Default behavior if window or wData is not initialized
}
BOOL WindowTemplate::StaticGetKeyUp(WindowTemplate* window, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (window && window->wData) {
        // Call the virtual GetCommand method
        return window->GetKeyUp(hWnd, message, wParam, lParam);
    }
    return true; // Default behavior if window or wData is not initialized
}
BOOL WindowTemplate::StaticGetKeyDown(WindowTemplate* window, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (window && window->wData) {
        // Call the virtual GetCommand method
        return window->GetKeyDown(hWnd, message, wParam, lParam);
    }
    return true; // Default behavior if window or wData is not initialized
}

LRESULT WindowTemplate::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    LONG_PTR ptr = GetWindowLongPtrW(hWnd, GWLP_USERDATA);
    WindowTemplate* window = reinterpret_cast<WindowTemplate*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
    RECT clientRect;
    
    switch (msg) {
    case WM_CREATE:
    {
        CenterWindow(hWnd);
        // Check if the window is a child window
        if (window && window->IsChildWindow()) {
            // Handle WM_CREATE for child window
            LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
            // Additional initialization for child window if needed...
        }
        else {
            // Set WindowTemplate instance as user data during window creation for main window
            LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pcs->lpCreateParams));
        }
        break;
    }
    case WM_COMMAND:
    {
        // Call the static helper function to handle command messages
        if (window && window->wData) {
            if (StaticGetCommand(window, hWnd, msg, wParam, lParam)) {
                // Handle command if necessary
            }
        }
        break;
    }
    case WM_KEYUP:
    {
        // Call the static helper function to handle command messages
        if (window && window->wData) {
            if (StaticGetKeyUp(window, hWnd, msg, wParam, lParam)) {
                // Handle command if necessary
            }
        }
        break;
    }
    case WM_KEYDOWN:
    {
        // Call the static helper function to handle command messages
        if (window && window->wData) {
            if (StaticGetKeyDown(window, hWnd, msg, wParam, lParam)) {
                // Handle command if necessary
            }
        }
        break;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Get the dimensions of the client area
        RECT clientRect;
        GetClientRect(hWnd, &clientRect);

        HBRUSH hBrush = CreateSolidBrush(COLOR_GRAY);
        FillRect(hdc, &clientRect, hBrush);
        DeleteObject(hBrush);

        EndPaint(hWnd, &ps);

        SendMessage(hWnd, WM_COMMAND, ID_GAME_DRAW, NULL);
        return 0;
    }
    case WM_SIZE: 
    {
        // Get the new dimensions of the client area
        GetClientRect(hWnd, &clientRect);
        InvalidateRect(hWnd, NULL, TRUE); // Invalidate the entire client area
        return 0;
    }
    case WM_CLOSE:
    {
        if (MessageBoxW(hWnd, L"Are you sure you want to close?", L"Confirmation", MB_YESNO) == IDNO)
        {
            return 0;
        }
        SendMessageW(hWnd, WM_COMMAND, ID_FILE_SAVE, NULL);
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }

    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_MOUSEMOVE:
    case WM_TIMER:
        break;
    default:
    {
        return DefWindowProcW(hWnd, msg, wParam, lParam);
    }
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}





// Main window class -------------------------------------------------------------------------
BOOL WindowMenu::CreateMenuScreen() {
    CreateWindowExW(WS_EX_WINDOWEDGE,L"STATIC", L"\nGame 2048",
        WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_SUNKEN,
        150, 20, 100, 50,
        GetHWND(), NULL, NULL, NULL);
    HWND hButton = CreateWindowExW(NULL, L"Button", L"Resume",
        WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | BS_PUSHBUTTON,
        150, 100, 100, 50,
        GetHWND(), (HMENU)ID_FILE_LOAD, NULL, NULL);
    CreateWindowExW(NULL, L"Button", L"New game",
        WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | BS_PUSHBUTTON,
        150, 152, 100, 50,
        GetHWND(), (HMENU)ID_FILE_NEW, NULL, NULL);
    CreateWindowExW(NULL, L"Button", L"About",
        WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | BS_PUSHBUTTON,
        150, 204, 100, 50,
        GetHWND(), (HMENU)ID_HELP_ABOUT, NULL, NULL);
    CreateWindowExW(NULL, L"Button", L"Exit",
        WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | BS_PUSHBUTTON,
        150, 256, 100, 50,
        GetHWND(), (HMENU)IDM_EXIT, NULL, NULL);

    List<UserName>* users = ReadUserData("Users/Users.bin");
    if (users == NULL)
    {
        EnableWindow(hButton, FALSE);
    }
    delete users;
    return TRUE;
}
BOOL WindowMenu::CreateMyWindow()
{
    if (!CreateMenuScreen()) return FALSE;

    return TRUE;
}
BOOL WindowMenu::GetCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId = LOWORD(wParam);
    HWND hwndGoto = NULL;  // Window handle of dialog box 
    // Parse the menu selections:
    switch (wmId)
    {
        // Handle Button
    case IDM_EXIT:
    {
        SendMessageW(hWnd, WM_CLOSE, 0, 0);
        break;
    }
        // File
    case ID_FILE_NEW:
    {
        hwndGoto = CreateDialogW(NULL, MAKEINTRESOURCE(IDD_NEWGAME), hWnd, NewGameDialog);
        ShowWindow(hwndGoto, SW_SHOW);
        break;
    }
    case ID_FILE_LOAD:
    {
        hwndGoto = CreateDialogW(NULL, MAKEINTRESOURCE(IDD_LOADGAME), hWnd, NewGameDialog);
        ShowWindow(hwndGoto, SW_SHOW);
        break;
    }
    case ID_FILE_OPEN:
    {
        // Open folder
        WCHAR filePath[MAX_PATH] = { 0 };

        // Call the function to get the file path
        if (GetOpenFilePath(filePath)) {
            // User selected a file, display its path
            MessageBox(NULL, filePath, L"Selected File", MB_OK | MB_ICONINFORMATION);
        }
        break;
    }
    case ID_FILE_SAVE:
    {
        // Resave data
        MessageBox(NULL, L"Save data", L"Save File", MB_OK | MB_ICONINFORMATION);
        break;
    }
    case ID_FILE_DELETE: {
        if (MessageBoxW(hWnd, L"Are you sure you want to delete data?", L"Confirmation", MB_YESNO) == IDNO)
        {
            return 0;
        }
        deleteFolderContents(FOLDER_USER_W);
        deleteFolderContents(FOLDER_DATA_W);
        MessageBoxW(hWnd, L"Deleted user's data!!!", L"Notification", MB_ICONASTERISK);
        break;
    }

    case ID_VIEW_PLAYER:
    {
        // Show top 1 user data
        MessageBox(NULL, L"User data", L"User", MB_OK | MB_ICONINFORMATION);
        break;
    }
    case ID_VIEW_SCORE:
    {
        // Get max score
        int max = GetMaxScore();
        LPCWSTR text = L"Max Score";
        MessageBox(NULL, intToWideChar(max), text, MB_OK | MB_ICONINFORMATION);
        break;
    }
    case ID_VIEW_LEADERBOARD:
    {
        hwndGoto = CreateDialogW(NULL, MAKEINTRESOURCE(IDD_LEADERBOARD), hWnd, LeaderboardDialog);
        ShowWindow(hwndGoto, SW_SHOW);
        break;
    }

        // Help
    case ID_HELP_INFOMATION:
    {
        ShowText_Information(hWnd);

        break;
    }
    case ID_HELP_SHORTCUT:
    {
        ShowText_Shortcut(hWnd);
        break;
    }
    case ID_HELP_ABOUT:
    {
        ShowText_About(hWnd);
        break;
    }

    case ID_TOOL_RESET:
    case ID_TOOL_UNDO:
    case ID_TOOL_REDO:
        MessageBox(NULL,L"Can't do this now",L"Abort!", MB_OK | MB_ICONASTERISK);
    default:
        return true;
    }
    return true;
}





// Game window class -----------------------------------------------------------------------
static unsigned __stdcall CreateNewWindow(void* data)
{
    // WaitForSingleObject(hMutex, INFINITE);
    GenerateSeed();

    // Get name of main window / menu window
    WCHAR windowName[MAX_LOADSTRING] = { 0 };
    LoadStringW(GetModuleHandle(NULL), IDS_APP_TITLE, windowName, MAX_LOADSTRING);

    WindowData* WinData = new WindowData(0, windowName, windowName,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        0, 0, 400, 600,
        NULL, NULL, GetModuleHandle(NULL), NULL);

    PlayerData* player = reinterpret_cast<PlayerData*>(data);

    WindowGame* GameInstance = new WindowGame(WinData);
    GameInstance->SetGame(player);
    SendMessage(GameInstance->GetHWND(), WM_COMMAND, ID_GAME_DRAW, 0);

    // Step 3: The Message Loop for the New Window
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    delete WinData;
    delete player;
    // ReleaseMutex(hMutex);
    return 0; // releasing any resources acquired by the thread
}




BOOL WindowGame::GetCommand(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int wmId = LOWORD(wParam);
    int wmEvent = HIWORD(wParam);
    Game2048* pMat = pGame->getGame()->getMatrix();
    GameData* ptrGame = pGame->getGame();

    switch (wmId)
    {
    case ID_HELP_INFOMATION:
    {
        ShowText_Information(hWnd);

        break;
    }
    case ID_HELP_SHORTCUT:
    {
        ShowText_Shortcut(hWnd);
        break;
    }
    case ID_HELP_ABOUT:
    {
        ShowText_About(hWnd);
        break;
    }

    case ID_FILE_NEW: // Create new game , change size,...
    {
        // Save user data to this
        pGame->CreateNewGameplay();
        SendMessageW(this->GetHWND(), WM_COMMAND, ID_GAME_DRAW, 0);
        MessageBoxW(hWnd, L"Create new game", L"Notification", MB_OK);
        break;
    }
    case ID_FILE_LOAD: // Load saved game
    {
        break;
    }
    case ID_FILE_SAVE: {
        pGame->writePlayerData(IntToStr8Digit(pGame->getID()));
        // MessageBoxW(hWnd, L"Load new game", L"Notification", MB_OK);

        break;
    }
    case ID_FILE_DELETE: // Delete current user
    { 
        pGame->GameOver();
        if (MessageBoxW(hWnd, L"Game over!", L"Notification", MB_RETRYCANCEL) == IDRETRY)
            SendMessageW(this->GetHWND(), WM_COMMAND, ID_FILE_NEW, 0);
        else
        {
            SendMessageW(this->GetHWND(), WM_CLOSE, 0, 0);
            DeleteUserByID(pGame->getID());
        }
        break;
    }

    case ID_VIEW_PLAYER:
    {
        PlayerData* user = pGame;
        HWND hwndGoto = CreateDialogParamW(NULL, MAKEINTRESOURCE(IDD_USER), hWnd,
                            UserDialog, reinterpret_cast<LPARAM>(user));
        ShowWindow(hwndGoto, SW_SHOW);
        break;
    }
    case ID_VIEW_SCORE:
    {
        // Get max score
        int max = GetMaxScore();
        LPCWSTR text = L"Max Score";
        MessageBox(NULL, intToWideChar(max), text, MB_OK | MB_ICONINFORMATION);
        break;
    }
    case ID_VIEW_LEADERBOARD:
    {
        HWND hwndGoto = CreateDialogW(NULL, MAKEINTRESOURCE(IDD_LEADERBOARD), hWnd, LeaderboardDialog);
        ShowWindow(hwndGoto, SW_SHOW);
        break;
    }

    case ID_TOOL_UNDO:
    {
        // BUG: after load game this not work properly
        pMat->setFolderPath(std::string(FOLDER_DATA) + "/" + IntToStr8Digit(pGame->getID())
            + "/" + IntToStr8Digit(pGame->getID()) + "_");
        if (!pMat->UndoHandle())
        {
            MessageBoxW(hWnd, L"Can't Undo", L"Notification", MB_OK);
        }
        break;
    }
    case ID_TOOL_REDO:
    {
        pMat->setFolderPath(std::string(FOLDER_DATA) + "/" + IntToStr8Digit(pGame->getID())
            + "/" + IntToStr8Digit(pGame->getID()) + "_");
        if (!pMat->RedoHandle())
        {
            MessageBoxW(hWnd, L"Can't Redo", L"Notification", MB_OK);
        }
        break;

    }

    // File
    case ID_GAME_OVER:
    {
        pGame->GameOver();

        List<UserName>* users = GetTop20();
        int score = pGame->getGame()->getMatrix()->getScore();
        int rank = FindRanking(pGame);
        if (rank < 1 || rank > 20) rank = 20;

        std::wstringstream wss;
        wss << L"Game over\nYour score: " << score << L"\nYour rank: " << rank;

        std::wstring wstr = wss.str();
        LPCWSTR text = wstr.c_str();
        if (ShowText_GameOver(hWnd, text) == IDRETRY)
        {
            // Start new game
            SendMessageW(this->GetHWND(), WM_COMMAND, ID_FILE_NEW, 0);
        }
        else
        {
            // Delete user
            SendMessageW(this->GetHWND(), WM_CLOSE, 0, 0);
            DeleteUserByID(pGame->getID());
        }
        break;
    }
    case IDC_AUTOPLAY:
    {
        // Spawn new cell
        pMat->SpawnSomeCells(1);
        // Delete next matrix
        deleteFilesFrom(pGame->getID(), pMat->getTurn());
        // Save turn
        ptrGame->setTurnToCurrentMatrix();
        // Set boolean value of prev matrix to true if Undo is on
        if (ptrGame->getGameMode()) pMat->setPrevMatrix(true);
        // Save current matrix
        ptrGame->writeGameData(std::to_string(pGame->getID()));
    }
    case ID_GAME_DRAW:
    {
        // Window box
        RECT clientRect;
        GetClientRect(hWnd, &clientRect);
        HDC hdc = GetDC(hWnd);
        int padding = clientRect.bottom/6;

        // Bottom box
        RECT down = { 0, padding * 5, clientRect.right, padding * 6 }; // 2 Row 
        DrawBottomBox(hdc, down);

        // Top Box
        RECT top = { 0, 0, clientRect.right, padding }; // 2 Row
        DrawTopBox(hdc, top);
        // Mid Box

        RECT matrix = { 0, padding, clientRect.right, padding * 5 }; // 4 Row
        DrawMatrix(hdc, matrix);

        // End Draw
        ReleaseDC(hWnd, hdc);
        return true;
    }

    default:
        return true;
    }

    return SendMessageW(this->GetHWND(), WM_COMMAND, ID_GAME_DRAW, 0);
}
BOOL WindowGame::GetKeyDown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId = LOWORD(wParam);
    int wmEvent = HIWORD(wParam);
    Game2048* game = pGame->getGame()->getMatrix();

    switch (wmId) {

        // Handle movement
    case 'A':
    case VK_LEFT:
    {
        if (game->MoveMatrixLeft())
        {
            MoveMatrix(this->GetHWND(), pGame);
        }
        else return SendMessageW(this->GetHWND(), WM_COMMAND, ID_GAME_OVER, 0);
        break;
    }
    case 'D':
    case VK_RIGHT:
    {
        if (game->MoveMatrixRight())
        {
            MoveMatrix(this->GetHWND(), pGame);
        }
        else return SendMessageW(this->GetHWND(), WM_COMMAND, ID_GAME_OVER, 0);
        break;
    }
    case 'W':
    case VK_UP:
    {
        if (game->MoveMatrixUp())
        {
            MoveMatrix(this->GetHWND(), pGame);
        }
        else return SendMessageW(this->GetHWND(), WM_COMMAND, ID_GAME_OVER, 0);
        break;
    }
    case 'S':
    case VK_DOWN:
    {
        if (game->MoveMatrixDown())
        {
            MoveMatrix(this->GetHWND(), pGame);
        }
        else return SendMessageW(this->GetHWND(), WM_COMMAND, ID_GAME_OVER, 0);
        break;
    }
    case 'I': // Information
    {
        SendMessageW(this->GetHWND(), WM_COMMAND, ID_VIEW_PLAYER, 0);
        break;
    }
    case 'E':
    {
        if(pGame->getPause() == true)
            SendMessageW(this->GetHWND(), WM_CLOSE, 0, 0);
        break;
    }

        // Handle Undo/Redo
    case 'U': // Undo
    {
        SendMessageW(this->GetHWND(), WM_COMMAND, ID_TOOL_UNDO, 0);
        break;
    }
    case 'R': // Redo
    {
        SendMessageW(this->GetHWND(), WM_COMMAND, ID_TOOL_REDO, 0);
        break;
    }
    default:
        return true;
    }
    // Save current matrix
    return true;
}



BOOL WindowGame::CreateMyWindow()
{
    //SetWindowPos(this->GetHWND(), HWND_TOPMOST, 0, 0, 0, 0,
    //                SWP_NOMOVE | SWP_NOSIZE);
    CenterWindow(this->GetHWND());
    
    return TRUE;
}
void WindowGame::DrawTopBox(HDC hdc, RECT rect)
{
    // Get matrix
    Game2048* pMat = pGame->getGame()->getMatrix();
    if (pMat->CheckEmptyMatrix()) return;

    // Get rect of top rect
    int cellWidth = (rect.right - rect.left) / 2;
    int cellHeight = (rect.bottom - rect.top);
    RECT box = { 0 }; COLORREF colorBox = { 0 }, colorText = { 0 };

    box = { rect.left + cellWidth / 8, rect.top + cellHeight / 8,
        rect.left + cellWidth - cellWidth / 8, rect.bottom - cellHeight / 8 };
    colorBox = COLOR_GRAY; colorText = COLOR_BLACK;
    DrawRectCentered(hdc, box, L"Turn:", pMat->getTurn(), colorBox, colorText);

    // Draw Matrix size
    box = { rect.left + cellWidth + cellWidth / 8, rect.top + cellHeight / 8,
        rect.left + cellWidth * 2 - cellWidth / 8, rect.bottom - cellHeight / 8 };
    colorBox = COLOR_GRAY; colorText = COLOR_BLACK;
    DrawRectCentered(hdc, box, L"Matrix size:", pMat->getRow(), colorBox, colorText);

}
void WindowGame::DrawBottomBox(HDC hdc, RECT rect) 
{
    // Get matrix
    Game2048* pMat = pGame->getGame()->getMatrix();
    if (pMat->CheckEmptyMatrix()) return;

    // Get rect of top rect
    int cellWidth = (rect.right - rect.left) / 2;
    int cellHeight = (rect.bottom - rect.top);
    RECT box = { 0 }; COLORREF colorBox = { 0 }, colorText = { 0 };

    box = { rect.left + cellWidth / 8, rect.top + cellHeight / 8,
            rect.left + cellWidth - cellWidth / 8, rect.bottom - cellHeight / 8 };
    colorBox = COLOR_GRAY; colorText = COLOR_BLACK;
    DrawRectCentered(hdc, box, L"Score:", pMat->getScore(), colorBox, colorText);

    box = { rect.left + cellWidth + cellWidth / 8, rect.top + cellHeight / 8,
        rect.left + cellWidth * 2 - cellWidth / 8, rect.bottom - cellHeight / 8 };
    colorBox = COLOR_GRAY; colorText = COLOR_BLACK;
    int max = max(pMat->getScore(), GetMaxScore());
    DrawRectCentered(hdc, box, L"Max:", max, colorBox, colorText);
}
void WindowGame::DrawMatrix(HDC hdc, RECT rect)
{
    // Get matrix
    Game2048* pMat = pGame->getGame()->getMatrix();
    if (pMat->CheckEmptyMatrix()) return;

    int cellWidth = (rect.right - rect.left) / pMat->getRow();
    int cellHeight = (rect.bottom - rect.top) / pMat->getCol();
    COLORREF colorBox = { 0 };

    // Draw matrix cells
    for (int i = 0; i < pMat->getRow(); ++i) {
        for (int j = 0; j < pMat->getCol(); ++j) {
            RECT cellRect = { rect.left + j * cellWidth,
                            rect.top + i * cellHeight,
                              rect.left + (j + 1) * cellWidth,
                            rect.top + (i + 1) * cellHeight};

            // Calculate a dynamic color based on the sum of row (i) and column (j) indices
            int indexSum = pMat->getPtr()[i][j];
            // int indexSum = pow(2,(i + 4 * j));

            colorBox = generateColorRefFromIndex(indexSum);

            // Draw a single cell with its corresponding value
            DrawCell(hdc, cellRect, indexSum, colorBox);
        }
    }


}
int WindowGame::CheckUserInput(HWND hWnd)
{
    // Find ID by name and pass
    // Return ID

    wchar_t* uName = new wchar_t[MAX_STR_SIZE];
    GetDlgItemText(hWnd, IDC_USERNAME, uName, MAX_STR_SIZE);
    wchar_t* uPass = new wchar_t[MAX_STR_SIZE];
    GetDlgItemText(hWnd, IDC_PASSWORD, uPass, MAX_STR_SIZE);
    //UserName* user = userList->findUser(uName, uPass);
    //if (user == NULL) return user->getID();
    return -1;
}




LRESULT CALLBACK AboutDialog(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        CenterWindow(hWnd);
        break;
    }
    case WM_COMMAND: 
    {
        if (LOWORD(wParam) == IDOK)
        {
            return SendMessageW(hWnd, WM_CLOSE, NULL, 0);
        }
        break;
    }
    case WM_CLOSE:
    {
        EndDialog(hWnd, 0);
    }
    default:
    {
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    }
    return DefWindowProcW(hWnd, message, wParam, lParam);
}
LRESULT CALLBACK UserDialog(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int ID = reinterpret_cast<int>(&lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Extract the data from lParam
        PlayerData* pPlayer = reinterpret_cast<PlayerData*>(lParam);
        UserData* pUser = pPlayer->getUser();
        GameData* pGame = pPlayer->getGame();

        // Set default values for controls
        SetDlgItemText(hWnd, IDC_USERNAME, pUser->getName());
        SetDlgItemText(hWnd, IDC_PASSWORD, pUser->getPass());
        SetDlgItemText(hWnd, IDC_LOCATION, pUser->getLocation());
        SetDlgItemText(hWnd, IDC_BIRTHDAY, timeToWideChar(pUser->getBirth()));
        SendDlgItemMessage(hWnd, IDC_GENDER, BM_SETCHECK, pUser->getGender(), 0);
        SendDlgItemMessage(hWnd, IDC_EASYMODE, BM_SETCHECK, pGame->getGameMode(), 0);
        int score = pGame->getMatrix()->getScore();
        int max = max(score, pUser->getScore());
        SetDlgItemText(hWnd, IDC_SCORE, intToWideChar(score));
        SetDlgItemText(hWnd, IDC_MAXSCORE, intToWideChar(max));
        SetDlgItemText(hWnd, IDC_TIME, timeToWideChar(pGame->getStartTime()));

        break;
    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == IDOK)
        {
            return SendMessageW(hWnd, WM_CLOSE, NULL, 0);
        }
        break;
    }
    case WM_CLOSE:
    {
        EndDialog(hWnd, 0);
    }
    default:
    {
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    }
    return DefWindowProcW(hWnd, message, wParam, lParam);
}
LRESULT CALLBACK LeaderboardDialog(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        CenterWindow(hWnd);
        std::string filename = "Users/Top20.bin";

        // Load data
        List<UserName>* users = GetTop20(filename);
        if (users == NULL) return false;
        Node<UserName>* temp = users->getHead();

        // Create listbox control
        HWND hListBox = GetDlgItem(hWnd, IDC_LEADERBOARD);
        // CreateWindow(L"LISTBOX", L"", WS_CHILD |
        //  WS_VISIBLE | WS_BORDER | LBS_STANDARD | LBS_USETABSTOPS
        // , 10, 40, 400, 500, hWnd, NULL, NULL, NULL);

        // Set fixed-width font for listbox
        HFONT hFont = (HFONT)GetStockObject(ANSI_FIXED_FONT);
        SendMessage(hListBox, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
        int num = 1;

        size_t maxNameLength = 25;
        // Set the width of the name column based on the longest name
        const int nameWidth = maxNameLength + 1; // Add some padding

        // Combine the three strings into a single wide string
        std::wstring rowData = L"0\tUSERNAME" +
            std::wstring(nameWidth - 8, L' ')
            + L"\tTIME\t\t\tSCORE";
        const wchar_t* rowDataPtr = rowData.c_str();

        SendDlgItemMessage(hWnd, IDC_LEADERBOARD, LB_ADDSTRING, 0, (LPARAM)rowDataPtr);


        while (temp != NULL)
        {
            UserName* us = temp->get();

            // Three wchar_t* strings
            const wchar_t* data1 = us->getName();
            const wchar_t* data2 = timeToWideChar(us->getTime());
            const wchar_t* data3 = intToWideChar(us->getScore());

            // Combine the three strings into a single wide string
            std::wstring rowData = IntToWideStr(num) + L"\t" + std::wstring(data1) +
                std::wstring(nameWidth - wcslen(data1), L' ') + L"\t" +
                std::wstring(data2) + L"\t" + std::wstring(data3);
            const wchar_t* rowDataPtr = rowData.c_str();

            SendDlgItemMessage(hWnd, IDC_LEADERBOARD, LB_ADDSTRING, 0, (LPARAM)rowDataPtr);

            temp = temp->pNext; num++;

        }
        int size = users->getSize();
        int max = users->getHead()->get()->getScore();

        // Convert size and max to strings
        wchar_t sizeString[10];
        wchar_t maxString[10];
        swprintf_s(sizeString, 10, L"%d", size);
        swprintf_s(maxString, 10, L"%d", max);

        // Set the text of the text boxes
        SetDlgItemText(hWnd, IDC_NUMBERPLAYERS, sizeString);
        SetDlgItemText(hWnd, IDC_MAXSCORE, maxString);

        SetDlgItemText(hWnd, IDC_USERNAME, L"NAME");
        SetDlgItemText(hWnd, IDC_SCORE, L"SCORE");
        SetDlgItemText(hWnd, IDC_TIME, L"TIME");


        delete users;
        break;

    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == IDOK)
        {
            return SendMessageW(hWnd, WM_CLOSE, NULL, 0);
        }
        break;
    }
    case WM_CLOSE:
    {
        EndDialog(hWnd, 0);
    }
    default:
    {
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    }
    return DefWindowProcW(hWnd, message, wParam, lParam);
}
LRESULT CALLBACK NewGameDialog(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId = LOWORD(wParam);
    PlayerData* player = NULL;
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Initialize combo box with items
        HWND hWndSize = GetDlgItem(hWnd, IDC_SELSIZE);
        SendMessage(hWndSize, CB_ADDSTRING, 0, (LPARAM)L"3");
        SendMessage(hWndSize, CB_ADDSTRING, 0, (LPARAM)L"4");
        SendMessage(hWndSize, CB_ADDSTRING, 0, (LPARAM)L"5");
        SendMessage(hWndSize, CB_ADDSTRING, 0, (LPARAM)L"6");
        SendMessage(hWndSize, CB_ADDSTRING, 0, (LPARAM)L"7");
        SendMessage(hWndSize, CB_ADDSTRING, 0, (LPARAM)L"8");
        SendMessage(hWndSize, CB_ADDSTRING, 0, (LPARAM)L"9");
        SendMessage(hWndSize, CB_ADDSTRING, 0, (LPARAM)L"10");
        SendMessage(hWndSize, CB_ADDSTRING, 0, (LPARAM)L"11");
        SendMessage(hWndSize, CB_ADDSTRING, 0, (LPARAM)L"12");
        // Set default selection
        SendMessage(hWndSize, CB_SELECTSTRING, (WPARAM)-1, (LPARAM)"4");
        
        // Initialize combo box with items
        HWND hWndSaveSlot = GetDlgItem(hWnd, IDC_SELPALLETE);
        SendMessage(hWndSaveSlot, CB_ADDSTRING, 0, (LPARAM)L"1");
        SendMessage(hWndSaveSlot, CB_ADDSTRING, 0, (LPARAM)L"2");
        SendMessage(hWndSaveSlot, CB_ADDSTRING, 0, (LPARAM)L"3");
        SendMessage(hWndSaveSlot, CB_ADDSTRING, 0, (LPARAM)L"4");
        SendMessage(hWndSaveSlot, CB_ADDSTRING, 0, (LPARAM)L"5");
        // Set default selection
        SendMessage(hWndSaveSlot, CB_SELECTSTRING, (WPARAM)-1, (LPARAM)"1"); // Change 1 to the index of the default item  

        break;
    }
    case WM_COMMAND:
    {
        switch (wmId)
        {
        case ID_FILE_OPEN:
        {
            SendMessageW(hWnd, WM_CLOSE, NULL, 0);
            return MessageBoxW(NULL,
                L"Can't create new user from your infomation\nTry reenter your name and password or load old game instead!!!"
                , L"Notification", MB_OK | MB_ICONINFORMATION);
        }
        case IDCANCEL:
        {
            return SendMessageW(hWnd, WM_CLOSE, NULL, 0);
        }

        case ID_FILE_NEW:
        {
            // Create new game


            // Check data is not empty str and not registered (TRUE AND FALSE)
            UserName* us = getUserFromDialog(hWnd);
            // Get list of user
            std::string filename = "Users/Top20.bin";            
            int ID = isUserDataRegistered(us, filename);
            bool check = us->CheckUserValid() && !(ID);
            delete us;
            if (!check) {
                return SendMessageW(hWnd, WM_COMMAND, ID_FILE_OPEN, 0);
            }
            
            // Create new data
            ID = Generate8DigitNumber();
            player = player->CreateNewPlayer(ID,hWnd);

            goto new_thread;
        }

        case ID_FILE_LOAD:
        {
            // Load old game

            // Check data is not empty str and was registered (TRUE AND TRUE)
            UserName* us = getUserFromDialog(hWnd);
            std::string filename = std::string(FOLDER_USER) + "/"
                + std::string(FOLDER_USER) + std::string(FILE_FORMAT);
            int ID = isUserDataRegistered(us,filename);
            bool check = us->CheckUserValid() && Check8DigitNumber(ID);
            delete us;
            if (!check) {
                return SendMessageW(hWnd, WM_COMMAND, ID_FILE_OPEN, 0);
            }

            // Load old data from file
            ID = ID;
            player = player->LoadOldPlayer(ID);

            if (player != NULL)
            {
                goto new_thread;
            }
            else
            {
                return SendMessageW(hWnd, WM_COMMAND, ID_FILE_OPEN, 0);
            }
        }

        default: {
            return (DefWindowProcW(hWnd, message, wParam, lParam));
        }
        break;
        }
    }
    case WM_CLOSE:
    {
        EndDialog(hWnd, 0);
    }
    default: {
        return (DefWindowProcW(hWnd, message, wParam, lParam));
    }
    }
    return (DefWindowProcW(hWnd, message, wParam, lParam));

new_thread:
    {
        // Create new thread        
        HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &CreateNewWindow, player, 0, NULL);
        if (hThread) CloseHandle(hThread);
    }
    return SendMessageW(hWnd, WM_CLOSE, NULL, 0);
}





BOOL MoveMatrix(HWND hWnd, PlayerData* pGame)
{
    Game2048* game = pGame->getGame()->getMatrix();
    SendMessageW(hWnd, WM_COMMAND, IDC_AUTOPLAY, 0);
    if (game->getWinCondition() && !pGame->getPause())
    {
        pGame->setPause(true);
        if (MessageBoxW(hWnd, L"You win!\nContinue?", L"Win!!!", MB_OKCANCEL) == IDCANCEL)
        {
            SendMessageW(hWnd, WM_COMMAND, ID_GAME_OVER, 0);
        }
    }
    return 0;
}

// Open file dialog
bool OpenFileDialog(HWND hWnd, LPWSTR filename, DWORD fileNameSize) {
    OPENFILENAMEW ofn;       // Common dialog box structure for wide characters
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = filename;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = fileNameSize;
    ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    return GetOpenFileNameW(&ofn);
}

// Show text box
BOOL ShowText_GameOver(HWND hWnd, LPCWSTR text)
{
    LPCWSTR name;
    name = L"Game over";
    return MessageBoxW(hWnd, text, name, MB_RETRYCANCEL);
}
void ShowText_About(HWND hWnd)
{
    LPCWSTR text, name;
    text = L"This game is made by Huynh Manh Tuong.\n"
           L"1/6/2024 - 10/6/2024";
    name = L"About";
    MessageBoxW(hWnd, text, name, MB_OK);
}
void ShowText_Information(HWND hWnd)
{
    LPCWSTR text, name;
    text = L"This is a simple 2048 for window\n";
    name = L"Information";
    MessageBoxW(hWnd, text, name, MB_OK);
}
void ShowText_Shortcut(HWND hWnd)
{
    LPCWSTR text, name;
    text = L"Press 'ASDW' or ARROW KEYS to move matrix\n"
        L"Press 'U' to undo matrix\n"
        L"Press 'R' to redo matrix\n"
        L"Press 'E' to exit game after win\n"
        L"Press 'I' to show stat\n";
    name = L"Shortcut";
    MessageBoxW(hWnd, text, name, MB_OK);
}

// Center window
void AddItemToListbox(HWND hWnd, LPCWSTR item)
{
    HWND hListbox = GetDlgItem(hWnd, IDC_LEADERBOARD);
    SendMessage(hListbox, LB_ADDSTRING, 0, (LPARAM)item);
}
BOOL CenterWindow(HWND hWnd) {
    RECT rect;
    if (GetWindowRect(hWnd, &rect)) {
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);

        int windowWidth = rect.right - rect.left;
        int windowHeight = rect.bottom - rect.top;

        int x = (screenWidth - windowWidth) / 2;
        int y = (screenHeight - windowHeight) / 2;

        return SetWindowPos(hWnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }
    return FALSE;
}
void DrawRectCentered(HDC hdc, RECT rect, const wchar_t* str, int total, COLORREF rectColor, COLORREF textColor) {
    // Draw filled rectangle
    HBRUSH hRectBrush = CreateSolidBrush(rectColor);
    FillRect(hdc, &rect, hRectBrush);
    DeleteObject(hRectBrush);

    // Draw rectangle outline
    COLORREF borderColor = RGB(0, 0, 0); // Black color for the border
    HPEN hPen = CreatePen(PS_SOLID, 1, borderColor);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);

    // Draw total value text
    wchar_t totalText[30];
    swprintf(totalText, 30, L"%s", str); // Only draw the string part first

    // Set text alignment
    SetTextAlign(hdc, TA_CENTER | TA_BASELINE);
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, textColor);

    // Calculate the center position of the rectangle for the text
    int xCenter = (rect.left + rect.right) / 2;
    int yCenter = (rect.top + rect.bottom) / 2 - 10; // Move text up by 10 pixels

    // Draw the text
    TextOutW(hdc, xCenter, yCenter, totalText, wcslen(totalText));

    // Prepare text for the number
    swprintf(totalText, 30, L"%d", total); // Now only the number part

    // Calculate the center position for the number
    yCenter += 20; // Move down by 20 pixels

    // Draw the number
    TextOutW(hdc, xCenter, yCenter, totalText, wcslen(totalText));
}
COLORREF generateColorRefFromIndex(int index, int x) {
    // Calculate RGB components based on the index
    if (index == 0) return RGB(255, 255, 255);
    x *= 10;
    int red = 255 - int(log2(index) * x * x);     // Red component
    int green = 255 - int(log2(index) * x);  // Green component
    int blue = 255 - int(log2(index) * x * x * x);   // Blue component

    // Use the RGB macro to create a COLORREF
    COLORREF color = RGB(red, green, blue);
    return color;
}
void DrawCell(HDC hdc, RECT cellRect, int value, COLORREF cellColor) {
    // Validate device context
    if (hdc == NULL) return;

    // Create and select brush for filling cell
    HBRUSH hBrush = CreateSolidBrush(cellColor);
    if (hBrush == NULL) return;
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    // Calculate the dimensions for the rounded rectangle
    int radius = 10; // Adjust this value to change the radius of the rounded corners
    int width = cellRect.right - cellRect.left;
    int height = cellRect.bottom - cellRect.top;

    // Draw the cell border with rounded corners
    // Draw the rounded rectangle outline
    HPEN hPen = CreatePen(PS_SOLID, 1, cellColor);
    if (hPen == NULL) {
        // Cleanup
        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
        return;
    }
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    RoundRect(hdc, cellRect.left, cellRect.top, cellRect.right, cellRect.bottom, radius, radius);
    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);

    // Fill the rounded rectangle with color
    RoundRect(hdc, cellRect.left, cellRect.top, cellRect.right, cellRect.bottom, radius, radius);

    // Cleanup
    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);

    // Prepare text for the value
    wchar_t text[10]; // Buffer size is set to 10
    swprintf_s(text, 10, L"%d", value); // Using swprintf_s to prevent buffer overflow

    // Set text alignment
    SetTextAlign(hdc, TA_CENTER | TA_BASELINE);
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(0, 0, 0));

    // Calculate the center position of the cell
    int xCenter = cellRect.left + (cellRect.right - cellRect.left) / 2;
    int yCenter = cellRect.top + (cellRect.bottom - cellRect.top) / 2;

    // Draw the text
    TextOutW(hdc, xCenter, yCenter, text, wcslen(text));
}