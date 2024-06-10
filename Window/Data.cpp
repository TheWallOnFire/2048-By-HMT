#include "Data.h"
#include "resource.h"
#include "Defined.h"
using namespace std;

// ----------------------------Point 2D-------------------------------
std::ostream& operator<<(std::ostream& out, Point2D& p)
{
    out << "(" << p.x << "," << p.y << ")";
    return out;
}
std::istream& operator>>(std::istream& in, Point2D& p)
{
    in >> p.x >> p.y;
    return in;
}

bool Point2D::operator==(Point2D& other)
{
    return (x == other.getX()) && (y == other.getY());
}

// --------------------NODE IMPLEMENT-----------------------
template <typename T> void Node<T>::set(T*& data) {
    if (pData != nullptr) delete pData;
    pData = data; data = nullptr;
    cout << "Set new value to node!\n";
}
template <typename T> void Node<T>::print() {
    cout << "This node is: ";
    if (pData == NULL) {
        cout << "Empty node!!!\n";
        return;
    }
    cout << *pData << "\n";
}





// ----------------LINKED LIST--------------------------------- //


// ------------------Add new node--------------------------------------------
template <typename T> void List<T>::addFirst(Node<T>*& pNode) {
    pNode->pNext = pHead;
    pHead = pNode; pNode = NULL; size++;
    cout << "Add new node " << *(pHead->pData) << " to the beginning of the list...\n";
}
template <typename T>  void List<T>::addLast(Node<T>*& pNode) {
    pTail->pNext = pNode;
    pTail = pNode; pNode = NULL; size++;
    cout << "Add new node " << *(pHead->pData) << " to the end of the list...\n";
}
template <typename T> void List<T>::addMid(Node<T>*& pNode, int index) {
    Node<T>* pTemp = findByIndex(index);
    T* data = pNode->pData;

    // Add new node after index node
    pNode->pNext = pTemp->pNext;
    pTemp->pNext = pNode;
    // Swap value pointer of 2 node
    pNode->pData = pTemp->pData;
    pTemp->pData = data;

    cout << "Add new node " << *(pTemp->pData) << " to the index " << index << " of the list...\n";
    size++; pNode = nullptr;
}


// --------------------Delete a node-----------------------------
template <typename T> void List<T>::deleFirst() {
    if (pHead == nullptr) return;
    Node<T>* pTemp = pHead;
    pHead = pHead->pNext;
    delete pTemp; size--;
    cout << "Delete node from the beginning of the list...\n";
}
template <typename T> void List<T>::deleLast() {
    Node<T>* pTemp = pHead;
    while (pTemp->pNext != pTail) pTemp = pTemp->pNext;
    delete pTail; pTail = pTemp; pTail->pNext = NULL; size--;
    cout << "Delete node from the last of the list...\n";
}
template <typename T> void List<T>::deleMid(int index) {
    Node<T>* pTemp = findByIndex(index - 1);
    if (pTemp == NULL) {
        cout << "Can't delete node\n";
        return;
    }
    Node<T>* dele = pTemp->pNext;
    pTemp->pNext = dele->pNext;
    delete dele; size--;
    cout << "Delete node from the index " << index << " of the list...\n";
}


// ---------------Sort list----------------------------------
template <typename T> void List<T>::sortHigh() {
    Node<T>* min;
    for (Node<T>* p = pHead; p->pNext != nullptr; p = p->pNext) {
        min = p;
        for (Node<T>* q = p->pNext; q != nullptr; q = q->pNext) {
            if (*(q->pData) < *(min->pData)) {
                min = q;
            }
        }
        T* tmp = min->pData;
        min->pData = p->pData;
        p->pData = tmp;
        tmp = nullptr;
    }
    min = nullptr;
    cout << "Sort from low to high\n";
}
template <typename T> void List<T>::sortLow() {
    Node<T>* max;
    for (Node<T>* p = pHead; p->pNext != nullptr; p = p->pNext) {
        max = p;
        for (Node<T>* q = p->pNext; q != nullptr; q = q->pNext) {
            if (*(q->pData) > *(max->pData)) {
                max = q;
            }
        }
        T* tmp = max->pData;
        max->pData = p->pData;
        p->pData = tmp;
        tmp = nullptr;
    }
    max = nullptr;
    cout << "Sort from high to low\n";
}


// --------------Main function-----------------------------------
template <typename T>  void List<T>::addNode(T*& data, int index) {
    Node<T>* pNode = new Node<T>();
    pNode->pData = data;
    if (size == 0) {
        cout << "Empty list added\n";
        pHead = pNode; pTail = pNode;
        size++; return;
    }
    if (index < 1) addFirst(pNode);
    else if (index > size - 1) addLast(pNode);
    else addMid(pNode, index);
}
template <typename T> void List<T>::deleByVal(T* data) {
    if (checkEmpty()) return;
    int index = findByValue(data);
    if (index < size && index >= 0) deleByIndex(index);
    else cout << "Can't delete node!\n";
}
template <typename T> void List<T>::deleByIndex(int index) {
    if (checkEmpty()) return;
    if (index == 0) deleFirst();
    else if (index == size - 1) deleLast();
    else deleMid(index);
}
template <typename T> void List<T>::deleAll() {
    if (checkEmpty()) return;
    while (pHead != nullptr && size > 0) {
        deleFirst();
    }
    pHead = NULL; pTail = nullptr;
    cout << "Delete all node from the list...\n";
}
template <typename T> void List<T>::sortList(int i) {
    if (checkEmpty() || size < 2) return;
    if (i == 0) sortHigh();
    else if (i == 1) sortLow();
}
template<typename T> bool List<T>::checkEmpty()
{
    bool check = (size == 0) || (pHead == NULL) || (pTail == NULL);
    if (check) cout << "Empty linked list!\n";
    return check;
}


// -------------------Visualize------------------------------ //
template <typename T> void List<T>::showList() {
    if (checkEmpty()) return;
    Node<T>* pTemp = pHead;
    cout << "Print list...\n";
    for (int i = 0; i < size; i++) {
        if (pTemp->pData == NULL) cout << "Null ";
        else cout << *(pTemp->get()) << "\n";
        pTemp = pTemp->pNext;
    }
}
template <typename T> T* List<T>::getNode(int index) {
    if (size == 0) {
        cout << "Empty linked list!\n";
        return nullptr;
    }
    Node<T>* pTemp = findByIndex(index);
    return pTemp->pData;
}

// ----------------- Find a node -------------------------------- //
template <typename T> Node<T>* List<T>::findByIndex(const int index) {
    if (checkEmpty()) return NULL;
    if (index < 0 || index >= size) {
        cout << "There is no node in this index!\n";
        return nullptr;
    }
    if (index == size - 1) return pTail;
    else if (index == 0) return pHead;
    Node<T>* pTemp = pHead;
    for (int i = 0; i < index; i++) pTemp = pTemp->pNext;
    return pTemp;
}
template <typename T> int List<T>::findByValue(T* data) {
    if (checkEmpty()) return FLAG_NOT_HERE;
    Node<T>* pTemp = pHead;
    for (int i = 0; i < size; i++) {
        if (pTemp->pData == NULL) return FLAG_NOT_HERE;
        if (*(pTemp->pData) == *data) return i;
        pTemp = pTemp->pNext;
    }
    cout << "Can't find index of this node!\n";
    return FLAG_NOT_HERE;
}


// ----------------Output file-----------------------
template <typename T>
std::ostream& operator<<(std::ostream& out, List<T>& list) {
    out << list.getSize() << "\n";
    Node<T>* pTemp = list.getHead();
    for (int i = 0; i < list.getSize(); i++) {
        out << *(pTemp->get()) << "\n";
        pTemp = pTemp->pNext;
    }
    std::cout << "Save list...\n";
    return out;
}
template <typename T>
std::istream& operator>>(std::istream& in, List<T>& list) {
    int size; in >> size;
    //list.setSize(size);
    list.addList(list.size);
    for (int i = 0; i < size; i++) {
        T* pData = new T;
        in >> *pData;
        list.addNode(pData, size);
    }
    std::cout << "\nLoad list...\n";
    return in;
}


// -----------------------QUEUE------------------------- /
template <typename T> void Queue<T>::initQueue() {
    pHead = nullptr;
    pTail = nullptr;
}
template <typename T> void Queue<T>::enQueue(void* item) {
    Node<T>* newNode = new Node<T>;
    newNode->pData = static_cast<T*>(item);
    newNode->pNext = nullptr;

    if (isEmpty()) {
        pHead = newNode;
        pTail = newNode;
    }
    else {
        pTail->pNext = newNode;
        pTail = newNode;
    }
}
template <typename T> void Queue<T>::deQueue() {
    if (isEmpty()) {
        return;
    }
    Node<T>* pTemp = pHead;
    pHead = pHead->pNext;
    delete pTemp;
}
template <typename T> void Queue<T>::closeQueue() {
    while (!isEmpty()) {
        deQueue();
    }
}
template <typename T> void* Queue<T>::firstQueue() {
    if (isEmpty()) {
        return nullptr;
    }
    return pHead->pData;
}
template <typename T> bool Queue<T>::isEmpty() {
    return pHead == nullptr;
}
template <typename T> void Queue<T>::takeAllQueue() {
    Node<T>* current = pHead;
    while (current != nullptr) {
        // Print or process current->data
        cout << *(current->pData) << " ";
        current = current->pNext;
    }
    cout << "\n";
}





// -----------------------STACK------------------------- /
template <typename T> void Stack<T>::initStack() {
    pHead = nullptr;
    pTail = nullptr;
}
template <typename T> void Stack<T>::closeStack() {
    while (!isEmpty()) {
        popStack();
    }
}
template <typename T> void Stack<T>::pushBack(void* item) {
    Node<T>* newNode = new Node<T>;
    newNode->pData = static_cast<T*>(item);
    newNode->pNext = pHead;
    pHead = newNode;
}
template <typename T> void Stack<T>::popStack() {
    if (isEmpty()) {
        return;
    }
    Node<T>* pTemp = pHead;
    pHead = pHead->pNext;
    delete pTemp;
}
template <typename T> void* Stack<T>::topStack() {
    if (isEmpty()) {
        return nullptr;
    }
    return pHead->pData;
}
template <typename T> bool Stack<T>::isEmpty() {
    return pHead == nullptr;
}
template<typename T> void Stack<T>::takeAllStack() {
    Node<T>* current = pHead;
    while (current != nullptr) {
        // Print or process current->data
        cout << *(current->pData) << " ";
        current = current->pNext;
    }
    cout << "\n";
}





// -----------------Matrix--------------------------------------


template<typename T>
void Matrix<T>::CreateNewMatrix()
{
    DeleteOldMatrix();
    InitializeMatrix();
    ResetMatrix();
    cout << "Matrix created!\n";
}
template<typename T>
void Matrix<T>::RandomizeMatrix(int min, int max) {
    if (min > max) {
        cout << "Min value > Max value error!\n";
        return;
    }
    if (CheckEmptyMatrix()) return;
    for (int i = 0; i < mRow; i++) {
        for (int j = 0; j < mCol; j++) {
            pMat[i][j] = RandomizeNumber(min, max);
        }
    }
    cout << "Randomized matrix!\n";
}

// -------------------------------------------------------
template<typename T> void Matrix<T>::setSize(int row, int col) {
    if (!CheckSize(row, col)) {
        mRow = 0; mCol = 0;
        cout << "Size error!\n";
        return;
    }
    else {
        mRow = row; mCol = col;
        cout << "Size updated!\n";
    }
}
template<typename T> void Matrix<T>::InitializeMatrix() {
    if (!CheckSize(mRow, mCol)) {
        cout << "Matrix doesn't have realistic size!\n";
        return;
    }
    pMat = new T * [mRow];
    if (!CheckPtr(pMat)) {
        cout << "Can't allocate data!\n";
        return;
    }
    for (int i = 0; i < mRow; i++) {
        pMat[i] = new T[mCol];
        if (!CheckPtr(pMat[i])) {
            cout << "Can't allocate data!\n";
            DeleteOldMatrix();
            return;
        }
    }
    cout << "Allocated space for matrix!\n";
}
template<typename T> void Matrix<T>::ResetMatrix() {
    if (CheckEmptyMatrix()) return;
    for (int i = 0; i < mRow; i++) {
        for (int j = 0; j < mCol; j++) {
            pMat[i][j] = baseVal;
        }
    }
    cout << "Reset matrix!\n";
}
template<typename T> void Matrix<T>::DeleteOldMatrix() {
    if (CheckEmptyMatrix()) return;
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
template <typename T> void Matrix<T>::loadMat(string f) {
    fstream input(f, ios::in || ios::binary);
    if (!input) {
        cout << "EMPTY FILE!\n";
        return;
    }
    input >> *this; input.close();
    cout << "Loaded matrix from file " << f << "\n";
}
template<typename T> void Matrix<T>::saveMat(string f) {
    fstream output(f, ios::out || ios::binary);
    output << *this; output.close();
    cout << "Saved matrix into file " << f << "\n";
}
template <typename T>
std::ostream& operator<<(std::ostream& out, Matrix<T>& mat) {
    if (mat.CheckEmptyMatrix()) return out;
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
    if (!mat.CheckEmptyMatrix()) mat.DeleteOldMatrix();
    int row, col; in >> row >> col;
    mat.setSize(row, col); mat.InitializeMatrix();
    for (int i = 0; i < mat.getRow(); i++) {
        for (int j = 0; j < mat.getCol(); j++) {
            in >> mat.pMat[i][j];
        }
    }
    cout << "Loading matrix completed!\n";
    return in;
}
template<typename T> void Matrix<T>::ShowMatrix() {
    if (CheckEmptyMatrix()) return;
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
    if (CheckEmptyMatrix()) return;
    for (int i = 0; i < mRow; i++) {
        for (int j = i + 1; j < mCol; j++) {
            swap(*(*(pMat + i) + j), *(*(pMat + j) + i));
        }
    }
    cout << "Transpose matrix successfully\n";
}
template<typename T> // Not done
void Matrix<T>::inverseMat() {
    if (CheckEmptyMatrix()) return;
}
template<typename T> // Not done
void Matrix<T>::flipMat() {
    if (CheckEmptyMatrix()) return;
}
template<typename T> // Not done
void Matrix<T>::adjMat() {
    if (CheckEmptyMatrix()) return;
}
template<typename T> // Not done
Matrix<T>* Matrix<T>::subMat(int row, int col) {
    if (CheckEmptyMatrix()) return NULL;
}
template<typename T>
void Matrix<T>::rotateClockwise()
{
    if( mRow != mCol) return;
    for (int i = 0; i < mRow / 2; ++i) {
        for (int j = i; j < mRow - i - 1; ++j) {
            int temp = pMat[i][j];
            pMat[i][j] = pMat[mRow - j - 1][i];
            pMat[mRow - j - 1][i] = pMat[mRow - i - 1][mRow - j - 1];
            pMat[mRow - i - 1][mRow - j - 1] = pMat[j][mRow - i - 1];
            pMat[j][mRow - i - 1] = temp;
        }
    }
}
template<typename T> void Matrix<T>::plusMat(T num) {
    if (CheckEmptyMatrix()) return;
    for (int i = 0; i < mRow; i++) {
        for (int j = 0; j < mCol; j++) {
            pMat[i][j] += num;
        }
    }
    cout << "Plus matrix with number " << num << "\n";
}
template<typename T> void Matrix<T>::plusMat(Matrix* mat) {
    if (CheckEmptyMatrix()) return;
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
    if (CheckEmptyMatrix()) return;
    for (int i = 0; i < mRow; i++) {
        for (int j = 0; j < mCol; j++) {
            pMat[i][j] *= num;
        }
    }
    cout << "Multiply matrix with number " << num << "\n";
}
template<typename T> //Need fixing
Matrix<T>* Matrix<T>::multiMat(Matrix<T>* mat) {
    if (CheckEmptyMatrix()) return nullptr;
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
    if (CheckEmptyMatrix()) return 0;
}
template<typename T> T Matrix<T>::sumMat() {
    if (CheckEmptyMatrix()) return 0;
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
    if (CheckEmptyMatrix()) return 0;
    if (checkSquare()) {} return 0;
    T temp = 0;
    for (int i = 0; i < mRow; i++) {
        temp += pMat[i][i];
    }
    cout << "Sum of diagonal is " << temp << "\n";
    return temp;
}


// -------------------------------------------------------
template<typename T> bool Matrix<T>::CheckSize(int row, int col) {
    if (row < 1 || col < 1) {
        cout << "Size error!\n";
        return false;
    }
    return true;
}
template<typename T> bool Matrix<T>::CheckPtr(void* ptr) {
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
template<typename T> bool Matrix<T>::CheckEmptyMatrix() {
    if (!CheckPtr(pMat) || !CheckSize(mRow, mCol)) {
        cout << "THIS IS AN EMPTY MATRIX! ABORT!\n";
        return true;
    }
    return false;
}




// -----------------------------Game 2048 -------------------------
void Game2048::InitGame2048()
{
    CreateNewMatrix();
    FindEmptyCells();
    checkMerge = true;
    SpawnSomeCells(); // Spawn cell
}
void Game2048::DeleteGame2048()
{
    delete emptyCell; emptyCell = NULL;
}

bool Game2048::readMat2048(std::string filename)
{
    ifstream input(filename, ios::binary);
    if (!input) {
        std::cerr << "Error opening file\n";
        return false;
    }

    // Read everything else
    input.read(reinterpret_cast<char*>(&currScore), sizeof(currScore));
    input.read(reinterpret_cast<char*>(&currTurn), sizeof(currTurn));
    input.read(reinterpret_cast<char*>(&startCells), sizeof(startCells));
    input.read(reinterpret_cast<char*>(&startValue), sizeof(startValue));
    input.read(reinterpret_cast<char*>(&bPrev), sizeof(bPrev));
    input.read(reinterpret_cast<char*>(&bNext), sizeof(bNext));
    input.read(reinterpret_cast<char*>(&bMode), sizeof(bMode));
    input.read(reinterpret_cast<char*>(&bLose), sizeof(bLose));
    input.read(reinterpret_cast<char*>(&bWin), sizeof(bWin));

    // Read size
    int rows = 0, cols = 0, start = 0;
    input.read(reinterpret_cast<char*>(&rows), sizeof(int));
    input.read(reinterpret_cast<char*>(&cols), sizeof(int));
    input.read(reinterpret_cast<char*>(&start), sizeof(int));
    this->setSize(rows, cols);
    this->setBase(start);

    // Allocate memory for the array
    int** array = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        array[i] = new int[cols];
    }

    // Read the array data from the file
    for (int i = 0; i < rows; ++i) {
        input.read(reinterpret_cast<char*>(array[i]), cols * sizeof(int));
    }

    this->setMat(array);

    input.close();
    return true;
}

bool Game2048::writeMat2048(std::string filename)
{
    ofstream output(filename, ios::binary);
    if (!output) {
        std::cerr << "Error opening file\n";
        return false;
    }

    // Write data of game
    output.write(reinterpret_cast<const char*>(&currScore), sizeof(currScore));
    output.write(reinterpret_cast<const char*>(&currTurn), sizeof(currTurn));
    output.write(reinterpret_cast<const char*>(&startCells), sizeof(startCells));
    output.write(reinterpret_cast<const char*>(&startValue), sizeof(startValue));
    output.write(reinterpret_cast<const char*>(&bPrev), sizeof(bPrev));
    output.write(reinterpret_cast<const char*>(&bNext), sizeof(bNext));
    output.write(reinterpret_cast<const char*>(&bMode), sizeof(bMode));
    output.write(reinterpret_cast<const char*>(&bLose), sizeof(bLose));
    output.write(reinterpret_cast<const char*>(&bWin), sizeof(bWin));

    // Write matrix data
    int rows = getRow(), cols = getCol(), start = getStart();
    output.write(reinterpret_cast<const char*>(&rows), sizeof(rows));
    output.write(reinterpret_cast<const char*>(&cols), sizeof(cols));
    output.write(reinterpret_cast<const char*>(&start), sizeof(start));
    int** matrix = getPtr();
    // Write the array data to the file
    for (int i = 0; i < rows; ++i) {
        output.write(reinterpret_cast<const char*>(matrix[i]), cols * sizeof(int));
    }

    output.close();
    return true;
}


// -------------Move------------------------------------------
bool Game2048::MoveMatrixLeft() {
    if (!canMove()) return false;

    MAT ptr = getPtr(); checkMerge = false;
    int row = getRow(); int col = getCol(); 

    for (int i = 0; i < row; i++) {
        int k = 0; // Start from the first column on the left
        for (int j = 1; j < col; j++) { // Start from the second column
            if (j == k) continue;
            if (ptr[i][j] != 0) {
                if (ptr[i][k] == 0) {
                    Point2D* p1 = new Point2D(i, j);
                    Point2D* p2 = new Point2D(i, k);
                    MergeTwoCells(p1, p2);
                    continue;
                }
                else if (ptr[i][j] == ptr[i][k]) {
                    Point2D* p1 = new Point2D(i, j);
                    Point2D* p2 = new Point2D(i, k);
                    MergeTwoCells(p1, p2);
                    AddPoint(getPtr()[int(p2->getX())][int(p2->getY())]);
                }
                else j--;
                k++; // Decrement k when no merge occurs
            }
        }
    }
    cout << "Moved matrix lefty\n";
    return true;
}
bool Game2048::MoveMatrixRight() {
    if (!canMove()) return false;

    MAT ptr = getPtr(); checkMerge = false;
    int row = getRow(); int col = getCol();

    for (int i = 0; i < row; i++) {
        int k = col - 1;
        for (int j = col - 2; j >= 0; j--) {
            if (j == k) continue;
            if (ptr[i][j] != 0) {
                if (ptr[i][k] == 0) {
                    Point2D* p1 = new Point2D(i, j);
                    Point2D* p2 = new Point2D(i, k);
                    MergeTwoCells(p1, p2);
                    continue;
                }
                else if (ptr[i][j] == ptr[i][k]) {
                    Point2D* p1 = new Point2D(i, j);
                    Point2D* p2 = new Point2D(i, k);
                    MergeTwoCells(p1, p2);
                    AddPoint(getPtr()[int(p2->getX())][int(p2->getY())]);
                }
                else j++;
                k--; // Decrement k when no merge occurs
            }
        }
    }
    cout << "Moved matrix righty!\n";
    return true;
}
bool Game2048::MoveMatrixUp() {
    if (!canMove()) return false;
    MAT ptr = getPtr(); checkMerge = false;
    int row = getRow(); int col = getCol();

    for (int i = 0; i < col; i++) {
        int k = 0;
        for (int j = k + 1; j < row; j++) {
            if (j == k) continue;
            if (ptr[j][i] != 0) {
                if (ptr[k][i] == 0) {
                    Point2D* p1 = new Point2D(j, i);
                    Point2D* p2 = new Point2D(k, i);
                    MergeTwoCells(p1, p2);
                    continue;
                }
                else if (ptr[j][i] == ptr[k][i]) {
                    Point2D* p1 = new Point2D(j, i);
                    Point2D* p2 = new Point2D(k, i);
                    MergeTwoCells(p1, p2);
                    AddPoint(getPtr()[int(p2->getX())][int(p2->getY())]);
                }
                else j--;
                k++; // Decrement k when no merge occurs
            }
        }
    }
    cout << "Moved matrix upward!\n";
    return true;
}
bool Game2048::MoveMatrixDown() {
    if (!canMove()) return false;
    MAT ptr = getPtr(); checkMerge = false;
    int row = getRow(); int col = getCol();
    for (int i = 0; i < col; i++) {
        int k = row - 1;
        for (int j = k - 1; j >= 0; j--) {
            if (j == k) continue;
            if (ptr[j][i] != 0) {
                if (ptr[k][i] == 0) {
                    Point2D* p1 = new Point2D(j, i);
                    Point2D* p2 = new Point2D(k, i);
                    MergeTwoCells(p1, p2);
                    continue;
                }
                else if (ptr[j][i] == ptr[k][i]) {
                    Point2D* p1 = new Point2D(j, i);
                    Point2D* p2 = new Point2D(k, i);
                    MergeTwoCells(p1, p2);
                    AddPoint(getPtr()[int(p2->getX())][int(p2->getY())]);
                }
                else j++;
                k--; // Decrement k when no merge occurs
            }
        }
    }
    cout << "Moved matrix downward!\n";
    return true;
}

bool Game2048::UndoHandle()
{
    bPrev = (currTurn > 1);
    if (bPrev && bMode && readMat2048(folder + to_string(currTurn - 1) + FILE_FORMAT))
    {
        bNext = true; // bMode true -> can undo/redo
        writeMat2048(folder + to_string(currTurn) + FILE_FORMAT);
        return true;
    }
    bPrev = false;
    return false;
}

bool Game2048::RedoHandle()
{
    if (bNext && bMode && readMat2048(folder + to_string(currTurn + 1) + FILE_FORMAT))
    {
        bPrev = true;
        writeMat2048(folder + to_string(currTurn) + FILE_FORMAT);
        return true;
    }
    bNext = false;
    return false;
}


// --------------------Cell------------------------------------
void Game2048::FindEmptyCells()
{
    delete emptyCell;
    emptyCell = new List<Point2D>;

    if (CheckEmptyMatrix()) return;
    for (int i = 0; i < getRow(); i++) {
        for (int j = 0; j < getCol(); j++) {
            if (getPtr()[i][j] == 0) {
                Point2D* p = new Point2D(i, j);
                AddToEmptyCell(p);
            }
        }
    }
    cout << "Find all empty node!\n";
    emptyCell->showList();
}
void Game2048::SpawnSomeCells(int num) {
    if (num == 0) num = startCells;
    if (checkMerge != true) return;
    
    for (int i = 0; i < num; i++) {
        SpawnNewCell();
    }
    setTurn(currTurn+1);
    checkMerge = false;
    // Save matrix
}
bool Game2048::SpawnNewCell()
{
    if (!checkMerge) return false;
    if (emptyCell->checkEmpty()) {
        cout << "No more empty cell!\n";
        return false;
    }
    int index = RandomizeNumber(0, emptyCell->getSize() - 1);
    int value = RandomizeNumber(2, 4, 90);
    cout << "Create cell in index " << index << " that has value " << value << "\n";
    Point2D* p = emptyCell->findByIndex(index)->get();
    cout << *p << "\n";
    getPtr()[int(p->getX())][int(p->getY())] = value;
    emptyCell->deleByIndex(index);
    emptyCell->showList();
    system("cls"); ShowMatrix();
    if(emptyCell->checkEmpty()) bLose = !canMove();
    cout << "-------Create cell in index " << index << " that has value " << value << "\n";
    return true;
}
void Game2048::MergeTwoCells(Point2D* p1, Point2D* p2)
{ // Add p1 to p2
    getPtr()[int(p2->getX())][int(p2->getY())]
        += getPtr()[int(p1->getX())][int(p1->getY())];
    getPtr()[int(p1->getX())][int(p1->getY())] = 0;
    AddToEmptyCell(p1);
    RemoveFromEmptyCell(p2);

    checkMerge = true;
    cout << "Merge cell " << *p1 << " and " << *p2 << "\n";
}
void Game2048::AddToEmptyCell(Point2D*& p)
{
    if (emptyCell->findByValue(p) == -1) {
        emptyCell->addNode(p);
        cout << "Added cell " << *p << "\n";
    }
    else cout << "No valid node!\n";
}
void Game2048::RemoveFromEmptyCell(Point2D* p)
{
    if (emptyCell->findByValue(p) != -1) {
        emptyCell->deleByVal(p);
        cout << "Deleted cell " << *p << "\n";
    }
    else cout << "No valid node!\n";
}


// Function to check if the 2048 matrix can move
bool Game2048::canMove() {
    for (int i = 0; i < getRow(); ++i) {
        for (int j = 0; j < getCol(); ++j) {
            // Check if current cell is zero (empty)
            if (getPtr()[i][j] == 0) {
                return true;
            }
            // Check right neighbor for possible merge
            if (j + 1 < getRow() && getPtr()[i][j] == getPtr()[i][j + 1]) {
                return true;
            }
            // Check bottom neighbor for possible merge
            if (i + 1 < getCol() && getPtr()[i][j] == getPtr()[i + 1][j]) {
                return true;
            }
        }
    }
    return false;
}
void Game2048::AddPoint(int p) {
    currScore += p;
    bWin = bWin || (p == 2048);
};



// GameData........................................

// Game data struct............................
bool GameData::AllocateNewGame()
{   // Create new matrix
    if (game2048 != NULL) {
        delete game2048;
        game2048 = NULL;
    }
    game2048 = new Game2048(size,bMode);
    if (game2048 == NULL) return false;
    // Can pass starting value here!!!
    // startcell and startvalue

    // Create matrix
    game2048->InitGame2048();
    gTurn = game2048->getTurn();
    bOver = false;

    start_time = getCurrentTime();
    load_time = start_time;
    played_time = 0;
    return true;
}
bool GameData::EndingGame()
{
    bOver = true;
    end_time = getCurrentTime();
    played_time += (end_time - load_time);
    getMatrix()->setLoseCondition(true);

    return true;
}
bool GameData::readGameData(std::string id)
{   // FILE: "ID/ID_0.bin"
    std::string filename = std::string(FOLDER_DATA) + "/" + id + "/" + id + "_0" + std::string(FILE_FORMAT);
    ifstream input(filename, ios::binary);
    if (!input) {
        std::cerr << "Error opening file\n";
        return false;
    }

    // Read the data from the file
    // Read number
    input.read(reinterpret_cast<char*>(&bLimit), sizeof(bLimit));
    input.read(reinterpret_cast<char*>(&size), sizeof(size));
    input.read(reinterpret_cast<char*>(&bMode), sizeof(bMode));
    input.read(reinterpret_cast<char*>(&bOver), sizeof(bOver));
    input.read(reinterpret_cast<char*>(&gTurn), sizeof(gTurn));
    // Read time_t
    input.read(reinterpret_cast<char*>(&start_time), sizeof(start_time));
    input.read(reinterpret_cast<char*>(&end_time), sizeof(end_time));
    input.read(reinterpret_cast<char*>(&played_time), sizeof(played_time));
    load_time = getCurrentTime();

    input.close();
    game2048 = new Game2048();
    readMat2048(id);
    return true;
}
bool GameData::writeGameData(std::string id)
{   // FILE: "ID/ID_0.bin"
    std::string filename = std::string(FOLDER_DATA) + "/" + id + "/" + id + "_0" + std::string(FILE_FORMAT);
    ofstream output(filename, ios::binary);
    if (!output) {
        std::cerr << "Error opening file\n";
    }

    // Calculate time
    end_time = getCurrentTime();
    played_time += end_time - load_time;

    // Write data members to the file
    // Write number
    output.write(reinterpret_cast<const char*>(&bLimit), sizeof(bLimit));
    output.write(reinterpret_cast<const char*>(&size), sizeof(size));
    output.write(reinterpret_cast<const char*>(&bMode), sizeof(bMode));
    output.write(reinterpret_cast<const char*>(&bOver), sizeof(bOver));
    output.write(reinterpret_cast<const char*>(&gTurn), sizeof(gTurn));
    // Write time_t
    output.write(reinterpret_cast<const char*>(&start_time), sizeof(start_time));
    output.write(reinterpret_cast<const char*>(&end_time), sizeof(end_time));
    output.write(reinterpret_cast<const char*>(&played_time), sizeof(played_time));

    output.close();
    writeMat2048(id);
    return true;

}
bool GameData::readMat2048(std::string id)
{
    if (this->gTurn > 0) {
        // Read matrix
        std::string filename = std::string(FOLDER_DATA) + "/" + id + "/" + id + "_" + to_string(gTurn) + std::string(FILE_FORMAT);
        game2048->readMat2048(filename);
        game2048->FindEmptyCells();
    }

    return true;
}
bool GameData::writeMat2048(std::string id)
{
    if (this->gTurn > 0) {
        // Read matrix
        std::string filename = std::string(FOLDER_DATA) + "/" + id + "/" + id + "_" + to_string(gTurn) + std::string(FILE_FORMAT);
        game2048->writeMat2048(filename);
    }

    return true;
}

bool GameData::getNewGameData(HWND hWnd)
{
    // Get from dialog
    bLimit = IsDlgButtonChecked(hWnd, IDC_TIMER);
    bMode = IsDlgButtonChecked(hWnd, IDC_EASYMODE);
    wchar_t* sizer = new wchar_t[MAX_STR_SIZE];
    GetDlgItemText(hWnd, IDC_SELSIZE, sizer, MAX_STR_SIZE);
    size = std::stoi(sizer);

    return true;
}

// User data struct..............................

bool UserData::AllocateNewGame()
{
    uCount++;
    uCurr = true;
    // Get Max point
    return true;
}


bool UserData::getNewUserData(HWND hWnd)
{
    // Get from dialog
    uName = new wchar_t[MAX_STR_SIZE];
    GetDlgItemText(hWnd, IDC_USERNAME, uName, MAX_STR_SIZE);
    trimWhitespace(uName);
    uPass = new wchar_t[MAX_STR_SIZE];
    GetDlgItemText(hWnd, IDC_PASSWORD, uPass, MAX_STR_SIZE);
    trimWhitespace(uPass);
    uLocate = new wchar_t[MAX_STR_SIZE];
    GetDlgItemText(hWnd, IDC_LOCATION, uLocate, MAX_STR_SIZE);
    uGender = IsDlgButtonChecked(hWnd, IDC_GENDER);
    trimWhitespace(uLocate);

    SYSTEMTIME st = { 0 }; HWND hDateTimePicker = {0};

    hDateTimePicker = GetDlgItem(hWnd, IDC_BIRTHDAY);
    if (SendMessage(hDateTimePicker, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == 0)
    {
        uBirth = SystTimeToTime(st);
    }
    return true;
}
bool UserData::setHighestScore(std::time_t completed, std::time_t played, int score)
{
    if (score > uMaxP) {
        uTime = completed;
        uPlayed = played;
        uMaxP = score;
        uCurr = false;
    }
    // Save to top20
    AddTop20("Users/top20.bin", this);
    return true;
}


bool UserData::readUserData(std::string id)
{   // FILE: "Users/ID.bin"
    std::string filename = std::string(FOLDER_USER) + "/" + id + std::string(FILE_FORMAT);
    ifstream input(filename, ios::binary);
    if (!input) {
        std::cerr << "Error opening file\n";
        return false;
    }

    // Read data members

    // Read number
    // input.read(reinterpret_cast<char*>(&uID), sizeof(uID));
    input.read(reinterpret_cast<char*>(&uGender), sizeof(uGender));
    input.read(reinterpret_cast<char*>(&uMaxP), sizeof(uMaxP));
    input.read(reinterpret_cast<char*>(&uCount), sizeof(uCount));
    input.read(reinterpret_cast<char*>(&uCurr), sizeof(uCurr));

    // Read time_t
    input.read(reinterpret_cast<char*>(&uBirth), sizeof(uBirth));
    input.read(reinterpret_cast<char*>(&uTime), sizeof(uTime));
    input.read(reinterpret_cast<char*>(&uPlayed), sizeof(uPlayed));

    // Read wchar_t*
    size_t length = 0; wchar_t* buffer = { 0 }; wchar_t ch = { 0 };
    if (uName != NULL) {
        delete uName;
        uName = NULL;
    }
    if (uPass != NULL)
    {
        delete uPass;
        uName = NULL;
    }
    if (uLocate != NULL) 
    {
        delete uLocate;
        uName = NULL;
    }

    input.read(reinterpret_cast<char*>(&length), sizeof(length));
    buffer = new wchar_t[length];
    input.read(reinterpret_cast<char*>(buffer), length * sizeof(ch));
    uName = buffer;

    input.read(reinterpret_cast<char*>(&length), sizeof(length));
    buffer = new wchar_t[length];
    input.read(reinterpret_cast<char*>(buffer), length * sizeof(ch));
    uPass = buffer;

    input.read(reinterpret_cast<char*>(&length), sizeof(length));
    buffer = new wchar_t[length];
    input.read(reinterpret_cast<char*>(buffer), length * sizeof(ch));
    uLocate = buffer;


    input.close();
    return true;
}
bool UserData::writeUserData(std::string id) const
{   // FILE: "Users/ID.bin"

    std::string filename = std::string(FOLDER_USER) + "/" + id + std::string(FILE_FORMAT);
    ofstream output(filename, ios::binary);
    if (!output) {
        std::cerr << "Error opening file\n";
        return false;
    }

    // Write data members to the file
    output.write(reinterpret_cast<const char*>(&uGender), sizeof(uGender));
    output.write(reinterpret_cast<const char*>(&uMaxP), sizeof(uMaxP));
    output.write(reinterpret_cast<const char*>(&uCount), sizeof(uCount));
    output.write(reinterpret_cast<const char*>(&uCurr), sizeof(uCurr));
    // Write time_t
    output.write(reinterpret_cast<const char*>(&uBirth), sizeof(uBirth));
    output.write(reinterpret_cast<const char*>(&uTime), sizeof(uTime));
    output.write(reinterpret_cast<const char*>(&uPlayed), sizeof(uPlayed));
    
    // Write char*
    size_t length = 0; wchar_t ch = { 0 };

    // Write the length of the string (including null terminator) to the file
    length = wcslen(uName) + 1;
    output.write(reinterpret_cast<const char*>(&length), sizeof(length));
    output.write(reinterpret_cast<const char*>(uName), length * sizeof(ch));

    length = wcslen(uPass) + 1;
    output.write(reinterpret_cast<const char*>(&length), sizeof(length));
    output.write(reinterpret_cast<const char*>(uPass), length * sizeof(ch));

    length = wcslen(uLocate) + 1;
    output.write(reinterpret_cast<const char*>(&length), sizeof(length));
    output.write(reinterpret_cast<const char*>(uLocate), length * sizeof(ch));

    output.close();

    return true;
}


// PlayerData struct ========================
bool PlayerData::allocateData() {
    // Uninitialize data - Allocate space
    uData = new UserData();
    gData = new GameData();
    if (gData == NULL || uData == NULL) return false;
    return true;
}
PlayerData* PlayerData::CreateNewPlayer(int id, HWND hWnd)
{
    PlayerData* player = new PlayerData;
    player->allocateData();
    player->setID(id);

    // Create data from HWND Dialog
    player->getNewPlayerData(hWnd); // Just get data from dialog
    player->CreateNewGameplay(); // Create new game

    // Save to file
    wchar_t* slot = new wchar_t[MAX_STR_SIZE];
    GetDlgItemText(hWnd, IDC_SELPALLETE, slot, MAX_STR_SIZE);
    player->saveSlot = std::stoi(slot);

    std::string filename = std::string(FOLDER_USER) + "/" + std::string(FILE_USER)
        + std::string(FILE_FORMAT);
    AddNewUser(filename, player);
    return player;
}

PlayerData* PlayerData::LoadOldPlayer(int id)
{
    PlayerData* player = new PlayerData;
    player->allocateData();
    player->setID(id);

    // Check empty data
    
    // Load data from corresponding files
    if (!player->readPlayerData(IntToStr8Digit(player->ID)))
    {
        delete player;
        player = NULL;
    }

    return player;
}

bool PlayerData::getNewPlayerData(HWND hWnd)
{
    // Only get data from dialog, not create game
    if (!uData->getNewUserData(hWnd)) return false;
    if (!gData->getNewGameData(hWnd)) return false;
    return true;
}

bool PlayerData::CreateNewGameplay()
{   // Create new game from data

    // CREATE ANOTHER FUNCTION FOR SAVING SCORE IF THAT GAME IS OVER!
    uData->FinishedLastGame(gData);

    // Change uData
    uData->AllocateNewGame();

    // Change gData
    gData->AllocateNewGame();

    // Save data
    CreateNewPlayerFiles();

    return false;
}



bool PlayerData::CreateNewPlayerFiles()
{

    // Delete saved file
    deleteFolderContents(std::wstring(FOLDER_DATA_W) + L"/" + IntToWideStr(ID));

    // Check empty data
    if (this->uData == NULL || this->gData == NULL) return false;

    // Create new directory store user file
    CreateNewDirectory(L"Data/" + IntToWideStr(ID));

    // Write player data
    writePlayerData(IntToStr8Digit(this->ID));
    // readPlayerData(IntToStr8Digit(this->ID));
    return true;
}

bool PlayerData::GameOver()
{   
    gData->EndingGame();
    uData->setHighestScore(gData->getEndTime(),gData->getPlayedTime(), 
        gData->getMatrix()->getScore());
    // Delete old file
    std::wstring folder = L"Data/" + IntToWideStr(getID());
    deleteFolderContents(folder);
    return true;
}

bool PlayerData::writePlayerData(std::string id) {
    if (!uData->writeUserData(id)) return false;
    if (!gData->writeGameData(id)) return false;
    return true;
}

bool PlayerData::setID(int id)
{
    ID = id; return true;
}

bool PlayerData::readPlayerData(std::string id) {

    if (!uData->readUserData(id)) return false;
    // Load previous game
    if (!gData->readGameData(id)) return false;
    return true;
}


// Username

BOOL UserName::Convert(PlayerData* user)
{
    UserData* us = user->getUser();
    if (us == NULL) return false;
    uName = us->getName();
    uPass = us->getPass();
    ID = user->getID();
    score = us->getScore();
    time = us->getTime();

    return 0;
}
BOOL UserName::Copy(UserName& us)
{
    this->ID = us.getID();
    this->uName = us.getName();
    this->uPass = us.getPass();
    this->score = us.getScore();
    this->time = us.getTime();
    return 0;
}
bool UserName::CheckUserValid()
{
    // Return false if the string is empty
    bool check = isWhitespace(uName) || isWhitespace(uPass);
    return !check;
}

bool UserName::deleteThis()
{
    delete uName; uName = nullptr;
    delete uPass; uPass = nullptr;
    return true;
}


std::ostream& operator<<(std::ostream& out, UserName& p)
{
    // TODO: insert return statement here
    return out;
}
std::istream& operator>>(std::istream& in, UserName& p)
{
    // TODO: insert return statement here
    return in;
}
bool UserName::operator==(UserName& other)
{
    int b = wcscmp(this->uName, other.uName);
    return !b;
}

bool UserName::operator<(UserName& other)
{
    if (score < other.score) return true;
    else if (score == other.score) return (time > other.time);
    else return false;
}
bool UserName::operator>(UserName& other)
{
    if (score > other.score) return true;
    else if (score == other.score) return (time > other.time);
    else return false;
}
bool UserName::operator<=(UserName& other)
{
    int b = (score <= other.score);
    return b;
}
bool UserName::operator>=(UserName& other)
{
    int b = (score >= other.score);
    return b;
}






UserName* getUserFromDialog(HWND hWnd)
{
    // Get from dialog
    wchar_t* uName = new wchar_t[MAX_STR_SIZE];
    GetDlgItemText(hWnd, IDC_USERNAME, uName, MAX_STR_SIZE);
    wchar_t* uPass = new wchar_t[MAX_STR_SIZE];
    GetDlgItemText(hWnd, IDC_PASSWORD, uPass, MAX_STR_SIZE);

    // Trim str
    UserName* us = new UserName;
    us->setName(trimWhitespace(uName));
    us->setPass(trimWhitespace(uPass));

    return us;
}




// Function to read user data from binary file and store in a of structs
List<UserName>* ReadUserData(std::string filename) {
    // Check open file
    std::ifstream input(filename, std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return NULL;
    }

    // Check data allocated
    List<UserName>* users = new List<UserName>;
    if (users == NULL) {
        std::cerr << "Can't create user list\n";
        return NULL;
    }

    // Read data from file
    UserName* us = nullptr;
    size_t length = 0; wchar_t* buffer = { 0 };
    int num = 0; std::time_t time = { 0 };

    while (!input.eof()) {
        input.read(reinterpret_cast<char*>(&num), sizeof(int));
        if (input.eof()) break;
        us = new UserName;
        us->setID(num);

        input.read(reinterpret_cast<char*>(&length), sizeof(length));
        buffer = new wchar_t[length];
        input.read(reinterpret_cast<char*>(buffer), length * sizeof(buffer[0]));
        us->setName(buffer);

        input.read(reinterpret_cast<char*>(&length), sizeof(length));
        buffer = new wchar_t[length];
        input.read(reinterpret_cast<char*>(buffer), length * sizeof(buffer[0]));
        us->setPass(buffer);

        input.read(reinterpret_cast<char*>(&num), sizeof(int));
        us->setScore(num);

        input.read(reinterpret_cast<char*>(&time), sizeof(std::time_t));
        us->setTime(time);

        // Create a new UserData instance and add it to the list
        users->addNode(us,users->getSize());
    }

    // Close the file
    input.close();
    return users;
}

BOOL SaveUserData(std::string filename, List<UserName>* list)
{
    deleteFile(filename);
    Node<UserName>* temp = list->getHead();
    while (temp != NULL)
    {
        SaveUsers(filename, temp->get());
        temp = temp->pNext;
    }
    return TRUE;
}

BOOL RemoveDuplicate(List<UserName>* list)
{
    Node<UserName>* node = list->getHead();

    while (node != NULL)
    {
        Node<UserName>* temp = node->pNext;
        while (temp != NULL)
        {
            if (temp->pData == node->pData)
            {

                // list->deleByVal();
            }
            temp = temp->pNext;
        }

    }

    return 0;
}

BOOL isUserDataRegistered(UserName* data, std::string filename)
{
    if (data == NULL) return FALSE;

    int ID = FLAG_EMPTY;
    List<UserName>* users = ReadUserData(filename);
    if (users == NULL) {
        delete users;
        return ID;
    }

    // Get ID
    ID = users->findByValue(data);
    if (ID == FLAG_NOT_HERE) {
        delete users;
        return FLAG_EMPTY;
    }
    else {
        UserName* us = users->findByIndex(ID)->get();
        if (wcscmp(data->getPass(), us->getPass())) // Different
        {
            ID = 1;
        }
        else
        {
            ID = us->getID();
        }
    }

    // Deallocate
    delete users;
    return ID;
}

// Save user to resume file
BOOL SaveUsers(std::string filename, UserName* username)
{
    if (username == NULL) return FALSE;

    ofstream read(filename, std::ios::binary | std::ios::app);
    if (!read) {
        std::cerr << "Error opening file\n";
        return false;
    }

    int uID = username->getID();
    read.write(reinterpret_cast<const char*>(&uID), sizeof(uID));

    wchar_t* name = username->getName();
    size_t length = wcslen(name) + 1;
    read.write(reinterpret_cast<const char*>(&length), sizeof(length));
    read.write(reinterpret_cast<const char*>(name), length * sizeof(wchar_t));

    wchar_t* pass = username->getPass();
    length = wcslen(pass) + 1;
    read.write(reinterpret_cast<const char*>(&length), sizeof(length));
    read.write(reinterpret_cast<const char*>(pass), length * sizeof(wchar_t));

    int uScore = username->getScore();
    read.write(reinterpret_cast<const char*>(&uScore), sizeof(uScore));

    time_t time = username->getTime();
    read.write(reinterpret_cast<const char*>(&time), sizeof(time));

    read.close();
    return 0;
}

// Delete first registered users until only a number of user remained
BOOL DeleteSomeUsers(std::string filename, int size)
{
    // Check and delete user file
    List<UserName>* users = ReadUserData(filename);
    while (users->getSize() > size) {
        Node<UserName>* us = users->getHead();
        DeleteUserByID(us->get()->getID());
        users->deleByIndex(0);
    }
    SaveUserData(filename, users);

    delete users;
    return 0;
}

BOOL DeleteUserByID(int id)
{
    std::wstring filename = L"Data/" + IntToWideStr(id);
    deleteFolderContents(filename);
    deleteFolder(filename);
    deleteFile("Users/" + IntToStr8Digit(id) + ".bin");
    return 0;
}

int GetMaxScore()
{
    List<UserName>* users = GetTop20();
    if (users == NULL) return 0;
    
    // return first person score
    int max = users->getHead()->get()->getScore();

    delete users;
    return max;
}




List<UserName>* GetTop20(std::string filename)
{
    // Open file top20
    List<UserName>* users = ReadUserData(filename);
    if (users == NULL) return NULL;

    users->sortList(1); // Decrease
    return users;
}

// Save user to top20
BOOL AddTop20(std::string filename, UserData* us)
{
    if (us == NULL) return FALSE;

    // Check if this user is in the file and modify data
    AddNewUser(filename, us, 123);
    List<UserName>* users = GetTop20(filename);
    if (users != NULL)
    {
        Node<UserName>* head = users->getHead();
        Node<UserName>* tail = users->getTail();
        while (head != NULL && tail != NULL)
        {
            if (*head->pData == *tail->pData && head != tail)
            {
                // Find duplicate and decide to swap it or not
                if (*head->pData < *tail->pData)
                {
                    head->pData->Copy(*tail->pData);
                }
                users->deleByIndex(users->getSize() - 1);
                break;
            }
            head = head->pNext;
        }
        users->sortList(0); // Sort increase
        DeleteSomeUsers(filename, 20);
        SaveUserData(filename, users);
    }

    delete users;
    return 0;
}


BOOL AddNewUser(std::string filename, UserData* us, int id)
{
    if (us == NULL) return FALSE;

    // Write new player to users.bin
    ofstream read(filename, std::ios::binary | std::ios::app);
    if (!read) {
        std::cerr << "Error opening file\n";
        return FALSE;
    }

    // Save id
    int uID = id;
    read.write(reinterpret_cast<const char*>(&uID), sizeof(uID));

    // Save name
    wchar_t* name = us->getName();
    size_t length = wcslen(name) + 1;
    read.write(reinterpret_cast<const char*>(&length), sizeof(length));
    read.write(reinterpret_cast<const char*>(name), length * sizeof(wchar_t));

    // Save pass
    wchar_t* pass = us->getPass();
    length = wcslen(pass) + 1;
    read.write(reinterpret_cast<const char*>(&length), sizeof(length));
    read.write(reinterpret_cast<const char*>(pass), length * sizeof(wchar_t));

    // Save score
    int uScore = us->getScore();
    read.write(reinterpret_cast<const char*>(&uScore), sizeof(uScore));

    // Save time
    time_t time = us->getTime();
    read.write(reinterpret_cast<const char*>(&time), sizeof(time));

    read.close();
    return TRUE;
}

BOOL AddNewUser(std::string filename, PlayerData* player)
{
    if (player == NULL) return FALSE;

    List<UserName>* users = ReadUserData(filename);
    if (users != NULL)
    {
        Node<UserName>* slot = users->findByIndex(player->getSlot() - 1);
        if (slot != NULL)
        {
            // Find duplicate data and remove it
            UserName* data = slot->get();
            DeleteUserByID(data->getID());
            data->Convert(player);
            SaveUserData(filename, users);
            return true;
        }
    }
    AddNewUser(filename, player->getUser(), player->getID());
    delete users;
    return TRUE;
}

BOOL RegisterNewUser(std::string filename, UserData* us, int id)
{
    if (us == NULL) return FALSE;
    if (AddNewUser(filename, us, id)) DeleteSomeUsers(filename, 5);
    return TRUE;
}



