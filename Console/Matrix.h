#pragma once

template<typename T> struct Matrix // Matrix class
{
    // Setup for use
    typedef T** MAT; // Alias for matrix

private: // Variable
    MAT pMat; // The main matrix pointer
    int mRow, mCol; // Number of row and column
    T baseVal; // Minimum number spawned
    std::string file; // File store matrix

public: // Public Method
    Matrix(); // Constructor of object (create matrix for generic use)
    ~Matrix(); // Destructor of object

    void newMat(int = 0, int = 0);
    void randomMat(int, int);
    void startNum(T);

private:
    // Matrix creation
    void setSize(int, int);// Get size of matrix
    void initMat(); // Create matrix from mRow mCol
    void resetMat(); // Reset value of matrix = 0
    void deleMat(); // Delete matrix data

public:
    // File manipulate
    void setFile(std::string); // Setup file
    void loadMat(std::string f = file); // Get matrix from file
    void saveMat(std::string f = file); // Save current matrix to file
    template <typename T>
    friend std::ostream& operator<<(std::ostream& out, Matrix<T>& mat);
    template <typename T>
    friend std::istream& operator>>(std::istream& in, Matrix<T>& mat);
    void showMat(); // Show matrix to terminal

    // Visualize matrix
    int getRow() { return mRow; }; // Get row of matrix
    int getCol() { return mCol; }; // Get col of matrix
    MAT getPtr() { return pMat; }; // Get ptr to matrix

private: // Math
    // Matrix conversion
    void transposeMat(); // Transposition the matrix
    void inverseMat(); // Reverse the matrix
    void flipMat(); // Flip the matrix
    void adjMat(); //
    Matrix<T>* subMat(int, int); // Create submatrix

    // Matrix math
    void plusMat(T); // Plus with an number
    void plusMat(Matrix*); // Plus with another matrix 
    void multiMat(T); // Multiply with a number
    Matrix<T>* multiMat(Matrix<T>*); // Multiply with a matrix
    T deltaMat(); // Find delta of matrix
    T sumMat(); // Sum of the matrix
    T sumDiagonal(); // Sum of diagonal 

public:
    // Check valid input for matrix
    bool checkSize(int row, int col); // Check size valid
    bool checkPtr(void* ptr); // Check pointer nullptr
    bool checkSquare(); // Check square matrix
    bool checkEmpty(); // Check empty matrix
    void plusCell(int, int, T);

    // Menu
    void printMenu();
    void handleMenu(int cmd);
    void calculateMatrix();
    void modifyMatrix();
};