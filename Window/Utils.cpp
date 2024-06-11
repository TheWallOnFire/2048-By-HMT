#include "Defined.h"
#include "Utils.h"
#include "Library.h" // Include C++ library


// Open console
void RedirectIOToConsole() {
    // Allocate a console for this application
    AllocConsole();

    // Redirect standard input/output/error to the console
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);

    // Synchronize C++ streams with C streams
    std::ios::sync_with_stdio(true);
}
// Get Error
std::string GetLastErrorAsString() {
    // Retrieve the last error code
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0) {
        return std::string(); // No error message has been recorded
    }

    LPSTR messageBuffer = nullptr;

    // Format the message from the system's message table
    size_t size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    std::string message(messageBuffer, size);

    // Free the buffer allocated by FormatMessage
    LocalFree(messageBuffer);

    return message;
}
bool CreateNewDirectory(const std::wstring& path) {
    if (!CreateDirectoryW(path.c_str(), NULL)) {
        DWORD error = GetLastError();
        if (error != ERROR_ALREADY_EXISTS) {
            std::wcerr << L"Failed to create directory: " << error << std::endl;
            return false;
        }
    }
    return true;
}
// Helper function to delete files and folders within a directory
bool deleteFolderContents(const std::wstring& path) {
    std::wstring searchPath = path + L"\\*";
    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::wcerr << L"Failed to list folder contents. Error code: " << GetLastError() << std::endl;
        return false;
    }

    do {
        const std::wstring item = findData.cFileName;
        if (item != L"." && item != L"..") {
            std::wstring fullPath = path + L"\\" + item;

            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                // Recursively delete subdirectories
                if (!deleteFolder(fullPath)) {
                    FindClose(hFind);
                    return false;
                }
            }
            else {
                // Delete files
                if (!DeleteFile(fullPath.c_str())) {
                    std::wcerr << L"Failed to delete file " << fullPath << L". Error code: " << GetLastError() << std::endl;
                    FindClose(hFind);
                    return false;
                }
            }
        }
    } while (FindNextFile(hFind, &findData) != 0);

    FindClose(hFind);

    return true;
}
bool deleteFolder(const std::wstring& path) {
    // First delete the contents of the folder
    if (!deleteFolderContents(path)) {
        return false;
    }

    // Attempt to remove the directory itself
    if (RemoveDirectory(path.c_str())) {
        return true;
    }
    else {
        std::wcerr << L"Failed to delete folder " << path << L". Error code: " << GetLastError() << std::endl;
        return false;
    }
}
bool deleteFile(const std::string& filePath) {
    // Attempt to delete the file
    if (remove(filePath.c_str()) == 0) {
        std::cout << "File successfully deleted: " << filePath << std::endl;
        return true;
    }
    else {
        std::perror("Error deleting file");
        return false;
    }
}
void deleteFilesFrom(int ID, int startNumber) {
    for (int i = startNumber; ; ++i) {
        std::stringstream ss;
        ss << FOLDER_DATA << "/" << ID << "/" 
            << ID << "_" << i << FILE_FORMAT;
        std::string fileName = ss.str();

        if (!deleteFile(fileName)) {
            // Stop if a file cannot be deleted (assuming it doesn't exist)
            break;
        }
    }
}
// Open folder and chose a file
bool GetOpenFilePath(WCHAR* filePath, const WCHAR* filter, HWND hwndParent) {
    // Initialize the OPENFILENAME structure
    OPENFILENAME ofn = { 0 };
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hwndParent; // Parent window
    ofn.lpstrFilter = filter; // Filter for file types
    ofn.lpstrFile = filePath; // Buffer to store the selected file path
    ofn.nMaxFile = MAX_PATH; // Size of lpstrFile buffer
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER; // File must exist and path must be valid

    // Display the Open File dialog
    if (GetOpenFileName(&ofn)) {
        // User selected a file
        return true;
    }
    else {
        // User canceled the dialog or an error occurred
        DWORD dwError = CommDlgExtendedError();
        if (dwError != 0) {
            std::cerr << "Error occurred while opening file dialog. Error code: " << dwError << std::endl;
        }
        else {
            std::cout << "User canceled the file dialog." << std::endl;
        }
        return false;
    }
}


// Generate a random seed based on the current system time
void GenerateSeed() {
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);
    std::cout << "Random seed generated: " << seed << "\n";
}
// Generate a random number between 'minValue' and 'maxValue'
int RandomizeNumber(int min, int max) {
    return min + (rand() % (max - min + 1));
}
// Generate a random number based on a given percentage
int RandomizeNumber(int min, int max, int prob) {
    int rand = RandomizeNumber(0, 100);
    if (rand < prob) {
        return min;
    }
    else {
        return max;
    }
}
// Generate random number
int Generate8DigitNumber() {
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(10000000, 99999999); // Range from 10,000,000 to 99,999,999

    // Generate and return a random 8-digit number
    return distrib(gen);
}
// Counter
int calculateElapsedTime(time_t startTime) {
    time_t currentTime;
    time(&currentTime);

    // Calculate the elapsed time in seconds
    int elapsedTime = difftime(currentTime, startTime);

    return elapsedTime;
}




// Get ID as string
std::string IntToStr8Digit(int id) {
    std::ostringstream oss;
    oss << std::setw(8) << std::setfill('0') << id;
    return oss.str();
}
bool Check8DigitNumber(int id)
{
    return (id / 10000000);
}
// Function to convert an integer to wstring
std::wstring IntToWideStr(int number) {
    return std::to_wstring(number);
}
wchar_t* intToWideChar(int value) {
    // Define the buffer size. Assuming the integer won't exceed 32 characters, including the null terminator.
    const size_t bufferSize = 32;
    wchar_t* buffer = (wchar_t*)malloc(bufferSize * sizeof(wchar_t));
    if (!buffer) {
        std::wcerr << L"Memory allocation failed" << std::endl;
        return nullptr;
    }

    // Convert the integer to a wide string
    if (swprintf(buffer, bufferSize, L"%d", value) < 0) {
        std::wcerr << L"swprintf failed" << std::endl;
        free(buffer);
        return nullptr;
    }

    return buffer;
}



// Function to convert a double to wstring
std::wstring DoubleToWideStr(double number) {
    return std::to_wstring(number);
}
// Check wchar_t
bool isWhitespace(const wchar_t* str) {
    if (str == L"") return false;
    while (*str != L'\0') {
        if (!iswspace(*str)) // Check if the character is not a whitespace
            return false;
        str++; // Move to the next character
    }
    return true;
}
// Trim wchar_t
wchar_t* trimWhitespace(wchar_t* str) {
    // Trim leading spaces
    while (iswspace(*str)) {
        str++;
    }

    // If the string is empty or contains only whitespace
    if (*str == L'\0') {
        return str;
    }

    // Trim trailing spaces
    wchar_t* end = str + wcslen(str) - 1;
    while (end > str && iswspace(*end)) {
        *end = L'\0';
        end--;
    }

    return str;
}
// Bool to text
std::wstring boolToText(bool value) {
    return value ? L"true" : L"false";
}




// Convert time_t to SYSTEMTIME
void TimeToSysTime(time_t t, SYSTEMTIME& st) {
    ULARGE_INTEGER ull;
    ull.QuadPart = static_cast<ULONGLONG>(t) + 11644473600ULL; // Add the epoch difference
    ull.QuadPart *= 10000000ULL; // Convert to 100-nanosecond intervals

    FILETIME ft;
    ft.dwLowDateTime = ull.LowPart;
    ft.dwHighDateTime = ull.HighPart;

    FileTimeToSystemTime(&ft, &st);
}
// Convert SYSTEMTIME to time_t
time_t SystTimeToTime(const SYSTEMTIME& st)
{
    FILETIME ft;
    SystemTimeToFileTime(&st, &ft);

    ULARGE_INTEGER uli;
    uli.LowPart = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;

    // Convert 100-nanosecond intervals into seconds
    ULONGLONG intervals = uli.QuadPart / 10000000ULL;

    // Subtract the difference between 1601-01-01 and 1970-01-01
    const ULONGLONG epochDiff = 11644473600ULL;
    intervals -= epochDiff;

    return static_cast<time_t>(intervals);

}
// Function to get current time as a string
time_t getCurrentTime() {
    // Get the current time as time_t
    time_t currentTime;
    time(&currentTime);

    // Optionally, print the current time in a human-readable format
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &currentTime);
    std::cout << "Current time: " << buffer << std::endl;

    return currentTime;
}

// Timet to wstring
wchar_t* timeToWideChar(time_t time) {
    // Convert time_t to tm structure
    struct tm timeInfo;
    localtime_s(&timeInfo, &time); // Use localtime_s for thread-safe conversion

    // Define the format and calculate the buffer size
    const size_t bufferSize = 100;
    wchar_t* buffer = (wchar_t*)malloc(bufferSize * sizeof(wchar_t));
    if (!buffer) {
        std::wcerr << L"Memory allocation failed" << std::endl;
        return nullptr;
    }

    // Format the tm structure into a wide string
    if (wcsftime(buffer, bufferSize, L"%Y-%m-%d %H:%M:%S", &timeInfo) == 0) {
        std::wcerr << L"wcsftime failed" << std::endl;
        free(buffer);
        return nullptr;
    }

    return buffer;
}


// Save time_t to a binary file
void SaveTimeToFile(time_t t, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    outFile.write(reinterpret_cast<const char*>(&t), sizeof(time_t));
    outFile.close();
}
// Load time_t from a binary file
bool LoadTimeFromFile(time_t& t, const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return false;
    }
    inFile.read(reinterpret_cast<char*>(&t), sizeof(time_t));
    inFile.close();
    return inFile.good();
}

