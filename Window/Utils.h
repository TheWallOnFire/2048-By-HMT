#pragma once

#pragma warning(push,3)
#include <windows.h>
#include <string>
#pragma warning(pop)




// Open console
void RedirectIOToConsole();
// Function to create Directory
bool CreateNewDirectory(const std::wstring& path);
// Get Error
std::string GetLastErrorAsString();
// Delete folder
bool deleteFolderContents(const std::wstring& path);
bool deleteFolder(const std::wstring& path);
bool deleteFile(const std::string& filePath);
void deleteFilesFrom(int ID, int startNumber);
bool GetOpenFilePath(WCHAR* filePath, const WCHAR* filter = L"All Files (*.*)\0*.*\0", HWND hwndParent = NULL);





// Random number
void GenerateSeed(); // Setup seed for randomize
int RandomizeNumber(int, int); // Random a number in a range
int RandomizeNumber(int, int, int); // Random a number base on percent
int Generate8DigitNumber();
int calculateElapsedTime(time_t startTime);


// Get ID as 8-digit string
std::string IntToStr8Digit(int id);
bool Check8DigitNumber(int id);
// Function to convert an integer to wstring
std::wstring IntToWideStr(int number);
wchar_t* intToWideChar(int value);


// Function to convert a double to wstring
std::wstring DoubleToWideStr(double number);
// Check wchar_t
bool isWhitespace(const wchar_t* str);
// Trim wchar_t*
wchar_t* trimWhitespace(wchar_t* str);
// Bool to text
std::wstring boolToText(bool value);





// Convert SYSTEMTIME / time_t
void TimeToSysTime(time_t t, SYSTEMTIME& st);
time_t SystTimeToTime(const SYSTEMTIME& st);
time_t getCurrentTime();
wchar_t* timeToWideChar(time_t time);




// Save and Load time_t to a binary file
void SaveTimeToFile(time_t t, const std::string& filename);
bool LoadTimeFromFile(time_t& t, const std::string& filename);
