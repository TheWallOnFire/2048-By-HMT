#include "pch.h"
#include "Game.h"
#include "Types.h"

#include "Matrix.cpp"
#include "Structure.cpp"

using namespace std;

void testGame() {
    cout << "Testing game\n";
    Game2048* ptr = new Game2048;
    genRandSeed();
    ptr->getHelp();
    while (true) {
        cout << "Enter your command:";
        int key = _getch();
        cout << (char)key << "\n";
        ptr->controlMat(key);
    }
    delete ptr;
}
// -----------------------------Game 2048 -------------------------
Game2048::Game2048()
{
    currScore = 0;
    emptyCell = new List<Point2D>;
    checkMerge = true;
    cout << "Setup game!\n";
}
Game2048::~Game2048()
{
    dele2048();
}
void Game2048::init2048(int size) 
{
    newMat(size, size);
    checkMerge = true;
    getEmptyCell();
    spawnManyCell(2);
}
void Game2048::dele2048()
{
    delete emptyCell; emptyCell = NULL;
}

// ---------------Game menu----------------
void Game2048::getHelp()
{
    cout << "--------------Matrix--------------------------\n";
    cout << "Press '0' to show matrix and get size\n";
    cout << "Press '1' to create a matrix\n";
    cout << "Press '2' to see empty cell\n";

    cout << "Press direction key or WSAD to move matrix\n";
    cout << "Press 'h' to get help\n";
    cout << "Press ESCAPE to exit\n";
    cout << "----------------------------------------\n";
}
void Game2048::controlMat(int cmd)
{
    switch (cmd) {
    case KEY_ESCAPE:
    {
        cout << "Testing ended!\n";
        exit(0);
    }
    case KEY_H:
    {
        getHelp();
        break;
    }
    case KEY_Q: // MENU
    case KEY_Z: // UNDO
    case KEY_X: // REDO
    case KEY_M: // SAVE
    case KEY_N: // LOAD
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
        cout << "Create matrix 2048\n";
        cout << "Enter size of matrix: ";
        int size; cin >> size;
        init2048(size);
        break;
    }
    case KEY_TWO:
    {
        cout << "Empty cells list\n";
        emptyCell->showList();
        break;
    }
    case 0:
    {
        cmd = _getch();
        controlMat(cmd);
        break;
    }
    case KEY_A: case KEY_LEFT:
    {
        cout << "Move left\n"; moveLeft();
        spawnCell(); break;
    }
    case KEY_D: case KEY_RIGHT:
    {
        cout << "Move right\n"; moveRight();
        spawnCell(); break;
    }
    case KEY_W: case KEY_UP:
    {
        cout << "Move up\n"; moveUp();
        spawnCell(); break;
    }
    case KEY_S: case KEY_DOWN:
    {
        cout << "Move down\n"; moveDown();
        spawnCell(); break;
    }
    default:
        break;
    }
}

// -------------Move------------------------------------------
void Game2048::moveLeft() {
    MAT pMat = getPtr(); int mRow = getRow(); int mCol = getCol(); checkMerge = false;
    for (int i = 0; i < mRow; i++) {
        int k = 0; // Start from the first column on the left
        for (int j = 1; j < mCol; j++) { // Start from the second column
            if (j == k) continue;
            if (pMat[i][j] != 0) {
                if (pMat[i][k] == 0) {
                    Point2D* p1 = new Point2D(i, j);
                    Point2D* p2 = new Point2D(i, k);
                    mergeCell(p1, p2);
                    continue;
                }
                else if (pMat[i][j] == pMat[i][k]) {
                    Point2D* p1 = new Point2D(i, j);
                    Point2D* p2 = new Point2D(i, k);
                    mergeCell(p1, p2);
                }
                else j--;
                k++; // Decrement k when no merge occurs
            }
        }
    }
    cout << "Moved matrix lefty\n";
}
void Game2048::moveRight() {
    MAT pMat = getPtr(); int mRow = getRow(); int mCol = getCol(); checkMerge = false;
    for (int i = 0; i < mRow; i++) {
        int k = mCol - 1;
        for (int j = mCol - 2; j >= 0; j--) {
            if (j == k) continue;
            if (pMat[i][j] != 0) {
                if (pMat[i][k] == 0) {
                    Point2D* p1 = new Point2D(i, j);
                    Point2D* p2 = new Point2D(i, k);
                    mergeCell(p1, p2);
                    continue;
                }
                else if (pMat[i][j] == pMat[i][k]) {
                    Point2D* p1 = new Point2D(i, j);
                    Point2D* p2 = new Point2D(i, k);
                    mergeCell(p1, p2);
                }
                else j++;
                k--; // Decrement k when no merge occurs
            }
        }
    }
    cout << "Moved matrix righty!\n";
}
void Game2048::moveUp() {
    MAT pMat = getPtr(); int mRow = getRow(); int mCol = getCol(); checkMerge = false;
    for (int i = 0; i < mCol; i++) {
        int k = 0;
        for (int j = k + 1; j < mRow; j++) {
            if (j == k) continue;
            if (pMat[j][i] != 0) {
                if (pMat[k][i] == 0) {
                    Point2D* p1 = new Point2D(j, i);
                    Point2D* p2 = new Point2D(k, i);
                    mergeCell(p1, p2);
                    continue;
                }
                else if (pMat[j][i] == pMat[k][i]) {
                    Point2D* p1 = new Point2D(j, i);
                    Point2D* p2 = new Point2D(k, i);
                    mergeCell(p1, p2);
                }
                else j--;
                k++; // Decrement k when no merge occurs
            }
        }
    }
    cout << "Moved matrix upward!\n";
}
void Game2048::moveDown() {
    MAT pMat = getPtr(); int mRow = getRow(); int mCol = getCol(); checkMerge = false;
    for (int i = 0; i < mCol; i++) {
        int k = mRow - 1;
        for (int j = k - 1; j >= 0; j--) {
            if (j == k) continue;
            if (pMat[j][i] != 0) {
                if (pMat[k][i] == 0) {
                    Point2D* p1 = new Point2D(j, i);
                    Point2D* p2 = new Point2D(k, i);
                    mergeCell(p1, p2);
                    continue;
                }
                else if (pMat[j][i] == pMat[k][i]) {
                    Point2D* p1 = new Point2D(j, i);
                    Point2D* p2 = new Point2D(k, i);
                    mergeCell(p1, p2);
                }
                else j++;
                k--; // Decrement k when no merge occurs
            }
        }
    }
    cout << "Moved matrix downward!\n";
}

// --------------------Cell------------------------------------
void Game2048::getEmptyCell()
{
    if (checkEmpty()) return;
    for (int i = 0; i < getRow(); i++) {
        for (int j = 0; j < getCol(); j++) {
            if (getPtr()[i][j] == 0) {
                Point2D* p = new Point2D(i, j);
                addNode(p);
            }
        }
    }
    cout << "Find all empty node!\n";
    emptyCell->showList();
}
void Game2048::spawnManyCell(int n) {
    for (int i = 0; i < n; i++) {
        checkMerge = true;
        spawnCell();
    }
}
void Game2048::spawnCell()
{
    if (!checkMerge) {
        cout << "No swap occur!\n";
        return;
    }
    if (emptyCell->checkEmpty()) {
        cout << "No more empty cell!\n";
        return;
    }
    int index = getRandNum(0, emptyCell->getSize() - 1);
    int value = getRandNumbWithProb(2, 4, 90);
    cout << "Create cell in index " << index << " that has value " << value << "\n";
    Point2D* p = emptyCell->findByIndex(index)->get();
    cout << *p << "\n";
    getPtr()[p->getX()][p->getY()] = value;
    emptyCell->deleByIndex(index);
    emptyCell->showList();
    system("cls");
    showMat();
    checkMerge = false;
    cout << "-------Create cell in index " << index << " that has value " << value << "\n";
}
void Game2048::mergeCell(Point2D* p1, Point2D* p2)
{ // Add p1 to p2
    getPtr()[p2->getX()][p2->getY()] += getPtr()[p1->getX()][p1->getY()];
    getPtr()[p1->getX()][p1->getY()] = 0;
    addNode(p1);
    deleNode(p2);
    checkMerge = true;
    cout << "Merge cell " << *p1 << " and " << *p2 << "\n";
}
void Game2048::addNode(Point2D* &p)
{
    if (emptyCell->findByValue(p) == -1) {
        emptyCell->addNode(p);
        cout << "Added cell " << *p << "\n";
    }
    else cout << "No valid node!\n";
}
void Game2048::deleNode(Point2D* p)
{
    if (emptyCell->findByValue(p) != -1) {
        emptyCell->deleByVal(p);
        cout << "Deleted cell " << *p << "\n";
    }
    else cout << "No valid node!\n";
}

//class BaseMenu
//{
//public:
//    BaseMenu() { m_MenuText = "This shouldn't ever be shown!"; } // This is the constructor - we use it to set class-specific information. Here, each menu object has its own menu text.
//    virtual ~BaseMenu() { } // This is the virtual destructor. It must be made virtual, else you get memory leaks - it's not a quick explanation, I recommend you read up on it
//    virtual BaseMenu* getNextMenu(int iChoice, bool& iIsQuitOptionSelected) = 0; // This is a 'pure virtual method', as shown by the "= 0". It means it doesn't do anything. It's used to set up the framework
//    virtual void printText() // This is made virtual, but doesn't *have* to be redefined. In the current code I have written, it is not redefined as we store the menu text as a string in the object
//    {
//        std::cout << m_MenuText << std::endl;
//    }
//
//protected:
//    std::string m_MenuText; // This string will be shared by all children (i.e. derived) classes
//};
//
//class FirstMenu : public BaseMenu // We're saying that this FirstMenu class is a type of BaseMenu
//{
//    FirstMenu()
//    {
//        m_MenuText = "Main Menu\n"                         // What we are doing here is setting up the string to be displayed later
//            + "Please make your selection\n"       // What we are doing here is setting up the string to be displayed later
//            + "1 - Start game\n"                   // What we are doing here is setting up the string to be displayed later
//            + "2 - Options\n"                      // What we are doing here is setting up the string to be displayed later
//            + "3 - Quit\n"                         // What we are doing here is setting up the string to be displayed later
//            + "Selection: ";                       // What we are doing here is setting up the string to be displayed later
//    }
//
//    BaseMenu* getNextMenu(int choice, bool& iIsQuitOptionSelected) // This is us actually defining the pure virtual method above
//    {
//        BaseMenu* aNewMenu = 0; // We're setting up the pointer here, but makin sure it's null (0)
//
//        switch (choice) // Notice - I have only done "options". You would obviously need to do this for all of your menus
//        {
//        case 2:
//        {
//            aNewMenu = new SecondMenu; // We're creating our new menu object here, and will send it back to the main function below
//        }
//
//        case 3:
//        {
//            // Ah, they selected quit! Update the bool we got as input
//            iIsQuitOptionSelected = true;
//        }
//
//        default:
//        {
//            // Do nothing - we won't change the menu
//        }
//
//        }
//
//        return aNewMenu; // Sending it back to the main function
//    }
//
//};
//
//class SecondMenu : public BaseMenu
//{
//    SecondMenu()
//    {
//        m_MenuText = "OptionsMenu\n"
//            + "Please make your selection\n"
//            + "1 - ????"
//            + "2 - dafuq?";
//    }
//
//    BaseMenu* getNextMenu(int choice, bool& iIsQuitOptionSelected) // This is us actually defining the pure virtual method above
//    {
//        BaseMenu* aNewMenu = 0; // We're setting up the pointer here, but makin sure it's null (0)
//
//        switch (choice) // Notice - I have only done options. You would obviously need to do this for all of your menus
//        {
//        case 1:
//        {
//            aNewMenu = new FirstMenu; // We're creating our new menu object here, and will send it back to the main function below
//        }
//        break;
//        case 2:
//        {
//            aNewMenu = new FirstMenu; // We're creating our new menu object here, and will send it back to the main function below
//        }
//        break;
//
//        default:
//        {
//            // Do nothing - we won't change the menu
//        }
//
//        }
//
//        return aNewMenu; // Sending it back to the main function
//    }
//};
//
//int main(int argc, char** argv)
//{
//    BaseMenu* aCurrentMenu = new FirstMenu; // We have a pointer to our menu. We're using a pointer so we can change the menu seamlessly.
//    bool isQuitOptionSelected = false;
//    while (!isQuitOptionSelected) // We're saying that, as long as the quit option wasn't selected, we keep running
//    {
//        aCurrentMenu.printText(); // This will call the method of whichever MenuObject we're using, and print the text we want to display
//
//        int choice = 0; // Always initialise variables, unless you're 100% sure you don't want to.
//        cin >> choice;
//
//        BaseMenu* aNewMenuPointer = aBaseMenu.getNextMenu(choice, isQuitOptionSelected); // This will return a new object, of the type of the new menu we want. Also checks if quit was selected
//
//        if (aNewMenuPointer) // This is why we set the pointer to 0 when we were creating the new menu - if it's 0, we didn't create a new menu, so we will stick with the old one
//        {
//            delete aCurrentMenu; // We're doing this to clean up the old menu, and not leak memory.
//            aCurrentMenu = aNewMenuPointer; // We're updating the 'current menu' with the new menu we just created
//        }
//    }
//
//    return true;
//}
// 