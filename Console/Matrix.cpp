#include "pch.h"
#include "Matrix.h"
#include "Types.h"
#include "Structure.h"

using namespace std;

// -----------------Matrix--------------------------------------
template<typename T> // Not done
Matrix<T>::Matrix() {
    pMat = NULL;
    mRow = 0; mCol = 0;
    startNum(0);
    setFile("matrix.txt");
}
template<typename T> Matrix<T>::~Matrix() {
    deleMat();
}

template<typename T>
void Matrix<T>::newMat(int row, int col)
{
    deleMat();
    setSize(row, col);
    initMat();
    resetMat();
    cout << "Matrix created!\n";
}
template<typename T> 
void Matrix<T>::randomMat(int min, int max) {
    if (min > max) {
        cout << "Min value > Max value error!\n";
        return;
    }
    if (checkEmpty()) return;
    for (int i = 0; i < mRow; i++) {
        for (int j = 0; j < mCol; j++) {
                pMat[i][j] = getRandNum(min, max);
        }
    }
    cout << "Randomized matrix!\n";
}
template<typename T> void Matrix<T>::startNum(T num) {
    baseVal = num;
    cout << "Changed starting value!\n";
}

// -------------------------------------------------------
template<typename T> void Matrix<T>::setSize(int row, int col) {
    if (!checkSize(row, col)) {
        mRow = 0; mCol = 0;
        cout << "Size error!\n";
        return;
    }
    else {
        mRow = row; mCol = col;
        cout << "Size updated!\n";
    }
}
template<typename T> void Matrix<T>::initMat() {
    if (!checkSize(mRow, mCol)) {
        cout << "Matrix doesn't have realistic size!\n";
        return;
    }
    pMat = new T * [mRow];
    if (!checkPtr(pMat)) {
        cout << "Can't allocate data!\n";
        return;
    }
    for (int i = 0; i < mRow; i++) {
        pMat[i] = new T[mCol];
        if (!checkPtr(pMat[i])) {
            cout << "Can't allocate data!\n";
            deleMat();
            return;
        }
    }
    cout << "Allocated space for matrix!\n";
}
template<typename T> void Matrix<T>::resetMat() {
    if (checkEmpty()) return;
    for (int i = 0; i < mRow; i++) {
        for (int j = 0; j < mCol; j++) {
            pMat[i][j] = baseVal;
        }
    }
    cout << "Reset matrix!\n";
}
template<typename T> void Matrix<T>::deleMat() {
    if (checkEmpty()) return;
    for (int i = 0; i < mRow; i++) {
        if (pMat[i] != NULL) {
            cout << "Deleting row " << i << "\n";
            delete[] pMat[i]; pMat[i] = nullptr;
        }
    }
    delete[] pMat; pMat = nullptr;
    cout << "Deleted Matrix!\n";
}

// ------------------In/Out File-------------------------------------
template <typename T> void Matrix<T>::setFile(string f) {
    file = f; cout << "Now read/write from " << file << "\n";
}
template <typename T> void Matrix<T>::loadMat(string f) {
    fstream input(f, ios::in || ios::binary);
    if (!input) {
        cout << "EMPTY FILE!\n";
        return;
    }
    input >> *this; input.close();
    cout << "Loaded matrix from file " << f <<"\n";
}
template<typename T> void Matrix<T>::saveMat(string f) {
    fstream output(f, ios::out || ios::binary);
    output << *this; output.close();
    cout << "Saved matrix into file " << f << "\n";
}
template <typename T>
std::ostream& operator<<(std::ostream& out, Matrix<T>& mat) {
    if (mat.checkEmpty()) return out;
    out << mat.getRow() << " " << mat.getCol() << "\n";
    for (int i = 0; i < mat.mRow; i++) {
        for (int j = 0; j < mat.mCol; j++) {
            out << mat.pMat[i][j] << " ";
        } out << "\n";
    }
    cout << "Saving matrix completed!\n";
    return out;
}
template <typename T>
std::istream& operator>>(std::istream& in, Matrix<T>& mat) {
    if (!mat.checkEmpty()) mat.deleMat();
    int row, col; in >> row >> col;
    mat.setSize(row,col); mat.initMat();
    for (int i = 0; i < mat.getRow(); i++) {
        for (int j = 0; j < mat.getCol(); j++) {
            in >> mat.pMat[i][j];
        }
    }
    cout << "Loading matrix completed!\n";
    return in;
}
template<typename T> void Matrix<T>::showMat() {
    if (checkEmpty()) return;
    cout << setfill('_') << setw(mRow * 10) << "\n";
    for (int i = 0; i < mRow; i++) {
        for (int j = 0; j < mCol; j++) {
            cout << "|" << setw(8) << pMat[i][j];
        }
        cout << "|\n" << setfill('_') << setw(mRow * 10) << "\n";
    }
    cout << "Showing matrix!\n";
}

// -----------------Math--------------------------------------
template<typename T> void Matrix<T>::transposeMat() {
    if (checkEmpty()) return;
    for (int i = 0; i < mRow; i++) {
        for (int j = i + 1; j < mCol; j++) {
            swap(*(*(pMat + i) + j), *(*(pMat + j) + i));
        }
    }
    cout << "Transpose matrix successfully\n";
}
template<typename T> // Not done
void Matrix<T>::inverseMat() {
    if (checkEmpty()) return;
}
template<typename T> // Not done
void Matrix<T>::flipMat() {
    if (checkEmpty()) return;
}
template<typename T> // Not done
void Matrix<T>::adjMat() {
    if (checkEmpty()) return;
}
template<typename T> // Not done
Matrix<T>* Matrix<T>::subMat(int row, int col) {
    if (checkEmpty()) return NULL;
}
template<typename T> void Matrix<T>::plusMat(T num) {
    if (checkEmpty()) return;
    for (int i = 0; i < mRow; i++) {
        for (int j = 0; j < mCol; j++) {
            pMat[i][j] += num;
        }
    }
    cout << "Plus matrix with number " << num << "\n";
}
template<typename T> void Matrix<T>::plusMat(Matrix* mat) {
    if (checkEmpty()) return;
    if (mat->getRow() != mRow || mat->getCol() != mCol) {
        cout << "Different dimension error\n";
        return;
    }
    for (int i = 0; i < mRow; i++) {
        for (int j = 0; j < mCol; j++) {
            pMat[i][j] += mat[i][j];
        }
    }
    cout << "Plus matrix with matrix\n";
}
template<typename T> void Matrix<T>::multiMat(T num) {
    if (checkEmpty()) return;
    for (int i = 0; i < mRow; i++) {
        for (int j = 0; j < mCol; j++) {
            pMat[i][j] *= num;
        }
    }
    cout << "Multiply matrix with number " << num << "\n";
}
template<typename T> //Need fixing
Matrix<T>* Matrix<T>::multiMat(Matrix<T>* mat) {
    if (checkEmpty()) return nullptr;
    if (mat->getRow() != mCol) {
        cout << "Different dimension error\n";
        return nullptr;
    }
    Matrix<T>* temp = new Matrix<T>(mCol, mat->getCol());
    for (int i = 0; i < temp->getRow(); i++) {
        for (int j = 0; j < temp->getCol(); j++) {
            T sum = 0;
            for (int k = 0; k < mCol; k++) {
                sum += pMat[i][k] * mat->pMat[k][j];
            }
            temp[i][j] = sum;
        }
    }
    cout << "Multiply matrix with matrix\n";
    return temp;
}
template<typename T> // Not done
T Matrix<T>::deltaMat() {
    if (checkEmpty()) return 0;
}
template<typename T> T Matrix<T>::sumMat() {
    if (checkEmpty()) return 0;
    T temp = 0;
    for (int i = 0; i < mRow; i++) {
        for (int j = 0; j < mCol; j++) {
            temp += pMat[i][j];
        }
    }
    cout << "Sum of matrix is " << temp << "\n";
    return temp;
}
template<typename T> T Matrix<T>::sumDiagonal() {
    if (checkEmpty()) return 0;
    if (checkSquare()) {} return 0;
    T temp = 0;
    for (int i = 0; i < mRow; i++) {
        temp += pMat[i][i];
    }
    cout << "Sum of diagonal is " << temp << "\n";
    return temp;
}

// -------------------------------------------------------
template<typename T> bool Matrix<T>::checkSize(int row, int col) {
    if (row < 1 || col < 1) {
        cout << "Size error!\n";
        return false;
    }
    return true;
}
template<typename T> bool Matrix<T>::checkPtr(void* ptr) {
    if (ptr == nullptr) {
        cout << "Pointer point to NULL!\n";
        return false;
    }
    return true;

}
template<typename T> bool Matrix<T>::checkSquare() {
    if (mRow == mCol) cout << "This is a square matrix!\n";
    else cout << "This is not a square matrix!\n";
    return mRow == mCol;
}
template<typename T> bool Matrix<T>::checkEmpty() {
    if (!checkPtr(pMat) || !checkSize(mRow,mCol)) {
        cout << "THIS IS AN EMPTY MATRIX! ABORT!\n";
        return true;
    }
    return false;
}

template<typename T>
void Matrix<T>::plusCell(int x, int y, T data)
{
    pMat[x][y] += data;
}

// -------------------Handle Menu -----------------------
template <typename T> void Matrix<T>::printMenu() {
    cout << "--------------Matrix--------------------------\n";
    cout << "Press '0' to show matrix and get size\n";
    cout << "Press '1' to create a matrix\n";
    cout << "Press '2' to randomize matrix\n";
    cout << "Press '3' to calculate value from matrix\n";
    cout << "Press '4' to modify value of matrix\n";
    cout << "Press '5' to \n";
    cout << "Press '6' to \n";
    cout << "Press '7' to change file location\n";
    cout << "Press '8' to save matrix to file\n";
    cout << "Press '9' to load matrix from file\n";

    cout << "Press 'h' to get help\n";
    cout << "Press ESCAPE to exit\n";
    cout << "----------------------------------------\n";
}
template <typename T> void Matrix<T>::handleMenu(int cmd) {
    switch (cmd)
    {
    case KEY_ESCAPE:
    {
        cout << "Testing ended!\n";
        exit(0);
    }
    case KEY_H:
    {
        printMenu();
        break;
    }
    case KEY_ZERO:
    {
        cout << "Show matrix:\n";
        showMat();
        cout << "Size of matrix: (" << getRow() << ")("
            << getCol() << ")\n";
        break;
    }
    case KEY_ONE:
    {
        cout << "Create matrix\n";
        cout << "Enter size of matrix (row col): ";
        int row, col; cin >> row >> col;
        newMat(row, col);
        break;
    }
    case KEY_TWO:
    {
        cout << "Randomize matrix\n";
        cout << "Enter min max value:";
        int min, max; cin >> min >> max;
        randomMat(min, max);
        break;
    }
    case KEY_THREE:
    {
        calculateMatrix();
        break;
    }
    case KEY_FOUR:
    {
        modifyMatrix();
        break;
    }
    case KEY_FIVE:
    {
    }
    case KEY_SIX:
    {
    }
    case KEY_SEVEN:
    {
    }
    case KEY_EIGHT: // Save
    {
        string fname;
        cout << "Enter file location (file name): ";
        cin >> fname;
        saveMat(fname); break;
    }
    case KEY_NINE: // Load
    {
        string fname;
        cout << "Enter file location (file name): ";
        cin >> fname;
        loadMat(fname); break;
    }
    default:
    {
        cout << "Unknown command\n";
        break;
    }
    }
}
template<typename T> void Matrix<T>::calculateMatrix() {
    cout << "--------------Matrix calculation--------------------------\n";
    cout << "Press '0' to return to previous\n";
    cout << "Press '1' to \n";
    cout << "Press '2' to \n";
    cout << "Press '3' to \n";
    cout << "Press '4' to \n";
    cout << "Press '5' to \n";
    cout << "Press '6' to \n";
    cout << "Press '7' to \n";
    cout << "Press '8' to \n";
    cout << "Press '9' to \n";

    cout << "Press ESCAPE to exit\n";
    cout << "----------------------------------------\n";

    cout << "Enter your command:";
    int cmd = _getch();
    cout << (char)cmd << "\n";

    switch (cmd)
    {
    case KEY_ESCAPE:
    {
        cout << "Testing ended!\n";
        exit(0);
    }
    case KEY_H:
    {
        printMenu();
        break;
    }
    case KEY_ZERO:
    {
    }
    case KEY_ONE:
    {
    }
    case KEY_TWO:
    {
    }
    case KEY_THREE:
    {
    }
    case KEY_FOUR:
    {
    }
    case KEY_FIVE:
    {
    }
    case KEY_SIX:
    {
    }
    default:
    {
        cout << "Unknown command\n";
        break;
    }
    }
}
template<typename T> void Matrix<T>::modifyMatrix() {
    cout << "--------------Matrix calculation--------------------------\n";
    cout << "Press '0' to return to previous\n";
    cout << "Press '1' to \n";
    cout << "Press '2' to \n";
    cout << "Press '3' to \n";
    cout << "Press '4' to \n";
    cout << "Press '5' to \n";
    cout << "Press '6' to \n";
    cout << "Press '7' to \n";
    cout << "Press '8' to \n";
    cout << "Press '9' to \n";

    cout << "Press ESCAPE to exit\n";
    cout << "----------------------------------------\n";

    cout << "Enter your command:";
    int cmd = _getch();
    cout << (char)cmd << "\n";

    switch (cmd)
    {
    case KEY_ESCAPE:
    {
        cout << "Testing ended!\n";
        exit(0);
    }
    case KEY_ZERO:
    {
    }
    case KEY_ONE:
    {
    }
    case KEY_TWO:
    {
    }
    case KEY_THREE:
    {
    }
    case KEY_FOUR:
    {
    }
    case KEY_FIVE:
    {
    }
    case KEY_SIX:
    {
    }
    default:
    {
    }
    }
}