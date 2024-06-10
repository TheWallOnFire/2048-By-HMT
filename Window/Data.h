#pragma once

#include "Utils.h"
#include "Defined.h"
#include "Library.h" // Include C++ library
#include "framework.h" // Contain C library and windows.h


// --------------Player Infomation ---------------------
// Find user by name in Users.bin, return ID of that user,
// Then search for ID folder and open it
// Open related file below:
// 
// Users.bin -> Store all username and password, return their IDs
// 
// ID folder -> Store user by ID 
// -------------ID.bin -> store user data
// -------------ID_0.bin -> store game data
// -------------ID_1.bin -> store matrix data
// -------------ID_2.bin ................................



//------------------Point2D------------------------------------
struct Point2D
{
private:
    int x = 0, y = 0;

public:
    Point2D(int a = 0, int b = 0) :x(a), y(b) {};
    ~Point2D() {};

    int getX() const { return x; };
    int getY() const { return y; };

    friend std::ostream& operator<< (std::ostream& out, Point2D& p);
    friend std::istream& operator>> (std::istream& in, Point2D& p);
    bool operator== (Point2D& other);
};


//------------------------NODE STRUCT--------------------------------------
template <typename T> struct Node
{
    T* pData; // Ptr to data
    Node<T>* pNext; // Ptr to next node

    Node(T* d = NULL) :pData(d), pNext(NULL) {};
    ~Node() { delete pData; pData = NULL; };

    T* get() const { return pData; };
    void set(T*& d); // Mutate
    void print(); // Print data
};


//------------------------LINKED LIST------------------------------------
template <typename T> struct List
{
private:
    Node<T>* pHead;
    Node<T>* pTail;
    int size;

public:
    List() : pHead(NULL), pTail(NULL), size(0) {};
    ~List() { this->deleAll(); };

private:
    // -----------Adding new Node---------------------
    void addFirst(Node<T>*& pNode); // Add new node at the beginning
    void addLast(Node<T>*& pNode); // Add new node at the end
    void addMid(Node<T>*& pNode, int index); // Add new node by index

    // ---------------------Deleting new Node--------------------------
    void deleFirst(); // Delete first node
    void deleLast(); // Delete last node
    void deleMid(int); // Delete node by index

    // ----------------Sorting list-------------------------
    void sortHigh();
    void sortLow();

public:
    // ------------------Controlling method------------
    void addNode(T*&, int index = 0); // Add new node by value
    void deleByVal(T*); // Delete node by value
    void deleByIndex(int index = 0); // Delete node by Index
    void deleAll(); // Delete all node
    void sortList(int i = 0); // 0 for increase / 1 for decrease // 2 for??
    bool checkEmpty(); // Check empty list

    // --------------------Visualize list---------------------
    void showList();
    T* getNode(int);
    int getSize() const {return size;};
    Node<T>* getHead() const { return pHead; };
    Node<T>* getTail() const { return pTail; };

    // ------------------Finding node-------------------
    Node<T>* findByIndex(const int); // Find by index
    int findByValue(T*); //Find by value

    // ----------------Input/Output file-----------------------
    template <typename T>
    friend std::ostream& operator<<(std::ostream& out, List<T>& list);
    template <typename T>
    friend std::istream& operator>>(std::istream& in, List<T>& list);
};


// ------------------------ QUEUE STRUCT ---------------------------------
template <typename T> struct Queue
{
private:
    Node<T>* pHead;
    Node<T>* pTail;
public:
    void initQueue(); // Initialize Queue
    void enQueue(void* item); // Add item
    void deQueue(); // Remove item
    void closeQueue(); // Delete queue
    void* firstQueue(); // First item
    bool isEmpty(); // Check empty
    void takeAllQueue(); // Print queue
};


// ------------------------ STACK STRUCT ------------------------------
template <typename T> struct Stack
{
private:
    Node<T>* pHead;
    Node<T>* pTail;
public:
    void initStack(); // Initialize Stack
    void closeStack(); // Close stack and deallocated data
    void pushBack(void* item); // Push item
    void popStack(); // Pop item
    void* topStack(); // Get first item
    bool isEmpty(); // Check is empty
    void takeAllStack(); // Print stack
};


// ------------------------ Matrix Type --------------------------------
template<typename T> struct Matrix // Matrix class
{
    typedef T** MAT; // Alias for matrix

private: // Variable
    int mRow = 4, mCol = 4; // Number of row and column
    T baseVal = 0; // Minimum number spawned
    MAT pMat = NULL; // The main matrix pointer

protected: // Function

    // Check valid input for matrix
    bool CheckSize(int row, int col); // Check size valid
    bool CheckPtr(void* ptr); // Check pointer not nullptr

public: // Public Method

    Matrix(int x = 4, int y = 4) { setSize(x, y); };
    ~Matrix() { DeleteOldMatrix(); };

    void CreateNewMatrix(); // Create new Matrix
    void RandomizeMatrix(int min, int max);
    bool CheckEmptyMatrix(); // Check empty matrix

    void setSize(int, int);// Set size of matrix
    void setBase(T num) { baseVal = num; };
    void setMat(T** mat) { DeleteOldMatrix(); pMat = mat; };
    void setStartNum(T num) { baseVal = num; };

    // Get value from matrix
    int getRow() { return mRow; }; // Get row of matrix
    int getCol() { return mCol; }; // Get col of matrix
    MAT getPtr() { return pMat; }; // Get ptr to matrix
    T getStart() { return baseVal; }; // Get base value

    void ShowMatrix(); // Show matrix to terminal

private: // Function

    // Matrix creation
    void InitializeMatrix(); // Create matrix from mRow mCol
    void ResetMatrix(); // Reset value of matrix = 0
    void DeleteOldMatrix(); // Delete matrix data

public: // Function

    // File manipulate (Need fixed)
    void loadMat(std::string f); // Get matrix from file
    void saveMat(std::string f); // Save current matrix to file
    template <typename T>
    friend std::ostream& operator<<(std::ostream& out, Matrix<T>& mat);
    template <typename T>
    friend std::istream& operator>>(std::istream& in, Matrix<T>& mat);
    
public: // Math

    // Matrix conversion
    bool checkSquare(); // Check square matrix
    void transposeMat(); // Transposition the matrix
    void inverseMat(); // Reverse the matrix
    void flipMat(); // Flip the matrix
    void adjMat(); //
    Matrix<T>* subMat(int, int); // Create submatrix
    void rotateClockwise();

    // Matrix math
    void plusMat(T); // Plus with an number
    void plusMat(Matrix*); // Plus with another matrix 
    void multiMat(T); // Multiply with a number
    Matrix<T>* multiMat(Matrix<T>*); // Multiply with a matrix
    T deltaMat(); // Find delta of matrix
    T sumMat(); // Sum of the matrix
    T sumDiagonal(); // Sum of diagonal 
};


struct Game2048 : public Matrix<int>
{
private:
    std::string folder = {};

    int currScore = 0;
    int currTurn = 0;
    int startCells = 2; // Number of start cell
    int startValue = 2; // Value of spawn cell

    bool bPrev = false;
    bool bNext = false;
    bool bMode = false;

    bool bLose = false; // Check the end of the game
    bool bWin = false; // Check lose or win

    // Using linked list 
    List<Point2D>* emptyCell = NULL; // Store empty cells
    bool checkMerge = false;

public:
    // Constructor / Destructor
    Game2048(int s = 4, bool mode = false) : Matrix(s, s)
        { bMode = mode; };
    ~Game2048() { DeleteGame2048(); };

    void InitGame2048();
    void FindEmptyCells();
    void SpawnSomeCells(int num = 0);

    // Return value
    int getScore() const { return currScore; };
    int getTurn() const { return currTurn; };
    bool getLoseCondition() const { return bLose; };
    bool getWinCondition() const { return bWin; };

    // Set data
    bool setTurn(int turn) { currTurn = turn; return true; }
    bool setWinCondition(bool b = false) { bWin = b; return true; };
    bool setLoseCondition(bool b = false) {
        bLose = b; 
        bPrev = false;
        bNext = false;
        return true; 
    };
    bool setPrevMatrix(bool b = false) { bPrev = b; return true; }
    bool setFolderPath(std::string path) { folder = path; return true; };

    // Game handle
    bool readMat2048(std::string path);
    bool writeMat2048(std::string path);

    // Movement algorithm
    bool MoveMatrixLeft();
    bool MoveMatrixRight();
    bool MoveMatrixUp();
    bool MoveMatrixDown();

    // Undo / Redo
    bool UndoHandle();
    bool RedoHandle();
    
private:

    // Cell manipulate
    void DeleteGame2048();
    
    // Game mechanic
    bool SpawnNewCell();
    void MergeTwoCells(Point2D*, Point2D*); // Merge cell 2 into cell 1

    void AddToEmptyCell(Point2D*&); // Add empty node
    void RemoveFromEmptyCell(Point2D*); // Remove empty node
    void AddPoint(int p);

    // Checking 
    bool canMove();

    // Power up idea: 
    // 1) Double value of a chosen cell
    // 2) Delete a chosen cell
    // 3) Shuffle the matrix randomly
    // 4) Swap 2 chosen cells
    // 5) Teleport the chosen cell to random empty location
    // 6) Merge 2 equal cells in different location
};


class GameData
{   // Store in ID_0.bin.................................
private:
    // Get from dialog
    bool bLimit = false; // Set timelimit or not
    int size = 4; bool bMode = false;
    // DON'T USE THESE 2 FOR GAME, JUST FOR PASSING VALUE

    // bool autoplay , bool sound, int colorpallete?????

    // generated when create new game
    int gTurn = 0; // Find s by turn
    bool bOver = false; // lose is true
    Game2048* game2048 = NULL;

    std::time_t start_time = { 0 }; // Time created matrix
    std::time_t load_time = { 0 }; // Time open saved matrix
    std::time_t end_time = { 0 }; // Last time open matirx
    std::time_t played_time = { 0 }; // Total time play this matrix

public: // Function

    GameData() {};
    ~GameData() {};

    bool AllocateNewGame();
    bool EndingGame();

    // Get value
    bool getNewGameData(HWND hWnd);
    Game2048* getMatrix() const { return game2048; };
    bool getGameMode() const { return bMode; };
    std::time_t getStartTime() const { return start_time; }
    std::time_t getEndTime() const { return end_time; }
    std::time_t getPlayedTime() const { return played_time; }

    // Set value
    bool setTurnToCurrentMatrix() {
        gTurn = game2048->getTurn();
        return true;
    }

    // Read/Write
    bool readGameData(std::string id);
    bool writeGameData(std::string id);
    bool readMat2048(std::string uID);
    bool writeMat2048(std::string uID);
};

// When player not reach win condition then not save that game to userdata
// Until player reach win condition then compare it with max value then save it
class UserData
{
private:// Variable
    // Store in ID.bin.......................................

    // Get from dialog box
    wchar_t* uName = NULL;
    wchar_t* uPass = NULL;
    wchar_t* uLocate = NULL;
    bool uGender = false; // true: male, false: female
    std::time_t uBirth = 0; // Fix

    // Self generated when create new game
    int uMaxP = 0; // Maximum point
    std::time_t uTime =  0; // Time complete of that game
    std::time_t uPlayed = 0; // Total time of that game

    int uCount = 0; // Number of game
    bool uCurr = false; // True if was playing

public: // Function

    UserData() {};
    ~UserData() {};

    bool AllocateNewGame();
    bool FinishedLastGame(GameData* gData) { return true; }; // Fix

    bool getNewUserData(HWND hWnd);

    // Get data
    bool isPlaying() const { return uCurr; };
    bool getGender() const { return uGender; };
    wchar_t* getName() const { return uName; };
    wchar_t* getPass() const { return uPass; };
    wchar_t* getLocation() const { return uLocate; };
    int getScore() const { return uMaxP; };
    std::time_t getTime() const { return uTime; };
    std::time_t getBirth() const { return uBirth; };

    // Set value
    void setMaxPoint(int point) { uMaxP = point; };
    bool setHighestScore(std::time_t completed, std::time_t played, int score);

    bool readUserData(std::string id);
    bool writeUserData(std::string id) const;
};


class PlayerData
{
private:

    UserData* uData = NULL;
    GameData* gData = NULL;
    int ID = 0;
    int saveSlot = 1;

    bool pauseGame = false;

private: // function

    bool allocateData();

public: // Function

    PlayerData(){};
    ~PlayerData(){};

    PlayerData* CreateNewPlayer(int id, HWND hWnd);
    PlayerData* LoadOldPlayer(int id);

    bool getNewPlayerData(HWND hWnd);
    bool getOldPlayerData();

    bool CreateNewGameplay();
    bool CreateNewPlayerFiles();
    bool GameOver();

    int getID() const { return ID; };
    UserData* getUser() const { return uData; };
    GameData* getGame() const { return gData; };
    int getScore() const { return uData->getScore(); };
    int getSlot() const { return saveSlot; };


    bool setID(int id);


    bool readPlayerData(std::string id);
    bool writePlayerData(std::string id);
};


// Done
class UserName
{
private: // Variable
    wchar_t* uName = NULL;
    wchar_t* uPass = NULL;
    int ID = 0;
    int score = 0;
    std::time_t time = 0;

public: // Function
    UserName() {};
    ~UserName() {};

    // Set data
    bool setName(wchar_t* str) { uName = str; return true; }
    bool setPass(wchar_t* str) { uPass = str; return true; }
    bool setID(int id) { ID = id; return true; }
    bool setScore(int num) { score = num; return true; }
    bool setTime(time_t num) { time = num; return true; }

    // Get data
    wchar_t* getName() const { return uName; };
    wchar_t* getPass() const { return uPass; };
    int getID() const { return ID; };
    int getScore() const { return score; };
    std::time_t getTime() const { return time; };
    BOOL Convert(PlayerData* user);
    BOOL Copy(UserName&);

    bool CheckUserValid();
    bool deleteThis();


    friend std::ostream& operator<< (std::ostream& out, UserName& p);
    friend std::istream& operator>> (std::istream& in, UserName& p);
    bool operator== (UserName& other);
    bool operator< (UserName& other);
    bool operator> (UserName& other);
    bool operator<= (UserName& other);
    bool operator>= (UserName& other);
};



// File: 
// Resume.bin
// Top20.bin
UserName* getUserFromDialog(HWND hWnd);
List<UserName>* ReadUserData(std::string filename);
BOOL SaveUserData(std::string filename, List<UserName>* list);
BOOL RemoveDuplicate(List<UserName>* list);
BOOL isUserDataRegistered(UserName* data, std::string filename);
BOOL SaveUsers(std::string filename, UserName* username);
BOOL DeleteSomeUsers(std::string filename, int size);
BOOL DeleteUserByID(int id);
int GetMaxScore();


List<UserName>* GetTop20(std::string filename = "Users/Top20.bin");
BOOL AddTop20(std::string filename, UserData* us);
BOOL AddNewUser(std::string filename, UserData* us, int id);
BOOL AddNewUser(std::string filename, PlayerData* player);
BOOL RegisterNewUser(std::string filename, UserData* us, int id);



