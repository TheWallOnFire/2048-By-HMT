#pragma once

#include "Matrix.h"
#include "Types.h"
#include "Structure.h"


void testGame(); // Key 9

struct Game2048 : public Matrix<int>
{
    // Code for 2048 game
private:
    long long currScore;
    bool checkMerge;
    int currTurn;

    bool mNext = false;
    bool mPrev = false;

    int emptyCells; // Number of empty cells of matrix
    int startCells; // Number of beginning cells of matrix

    int score; // Score of this game
    bool over; // Check the end of the game
    bool won; // Check lose or win
    bool pause; // Check pause game

    // Using linked list 
    List<Point2D>* emptyCell; // Store empty cells


public:
    // Constructor / Destructor
    Game2048();
    ~Game2048();

    // Game handle
    void init2048(int size);
    void dele2048();

    // Menu
    void getHelp();
    void controlMat(int);

private:
    // Movement algorithm
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    // Cell manipulate
    void getEmptyCell();
    void spawnManyCell(int n);
    void spawnCell();
    void mergeCell(Point2D*, Point2D*); // Merge cell 2 into cell 1
    void addNode(Point2D*&); // Add empty node
    void deleNode(Point2D*); // Remove empty node

    // Power up idea: 
    // 1) Double value of a chosen cell
    // 2) Delete a chosen cell
    // 3) Shuffle the matrix randomly
    // 4) Swap 2 chosen cells
    // 5) Teleport the chosen cell to random empty location
    // 6) Merge 2 equal cells in different location
};

struct GameMenu
{
private:
    Infomation player;
    int turn;

    Game2048 game;
    Queue<std::string>* redoTab; // Store next matrix
    Queue<std::string>* undoTab; // Store back matrix

    // Draw screen

public:
    void gameLoop();
    void gameScreen();
    
    void gameMenu();
    void mainMenu();
    void optionsMenu();
};