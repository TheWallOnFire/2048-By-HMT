#include "pch.h"
#include "Structure.h"
#include "Types.h"
using namespace std;

// -------------------------------------NODE IMPLEMENT---------------------------------------
template <typename T> Node<T>::Node() {
    pData = NULL; pNext = NULL;
    cout << "Created empty node!\n";
}
template <typename T> Node<T>::~Node() {
    delete pData; pData = nullptr;
    cout << "Deleted node!\n";
}
template <typename T> T* Node<T>::get() const {
    cout << "Get data pointer from node! ";
    return pData;
}
template <typename T> void Node<T>::set(T* &data) {
    if (pData != nullptr) delete pData;
    pData = data; data = nullptr;
    cout << "Set new value to node!\n";
}
template <typename T> void Node<T>::show() {
    cout << "This node is: ";
    if (pData == NULL) {
        cout << "Empty node!!!\n";
        return;
    }
    cout << *pData << "\n";
}

// ---------------------------Handle Menu ------------------------------
template <typename T> void Node<T>::printMenu() {
    cout << "--------------------Node Menu--------------------------\n";
    cout << "Press '0' to print node\n";
    cout << "Press '1' to set node\n";
    cout << "Press '2' to randomize value\n";

    cout << "Press 'h' to get help\n";
    cout << "Press ESCAPE to exit\n";
    cout << "-------------------------------------------------------\n";
}
template <typename T> void Node<T>::handleMenu(int cmd) {
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
        show();
        break;
    }
    case KEY_ONE:
    {
        T* pData = new T;
        cout << "Enter data: \n";
        cin >> *pData;
        set(pData);
        break;
    }
    case KEY_TWO:
    {
        cout << "Randomize node\n";
        int min, max;
        cout << "Enter min max value:";
        cin >> min >> max;
        T* pData = new T;
        *pData = getRandNum(min, max);
        set(pData);
        break;
    }
    default:
    {
        cout << "Unknown command\n";
        break;
    }
    }
}

// ----------------LINKED LIST--------------------------------- //
// ---------------Linked list setup------------------------------
template <typename T> List<T>::List() {
    pHead = nullptr; pTail = nullptr; size = 0;
    cout << "Created empty linked list!\n";
}
template <typename T> List<T>::~List() {
    deleAll();
    cout << "Deleted the list!\n";
}

// -------------------Handle Menu -----------------------
template <typename T> void List<T>::printMenu() {
    cout << "--------------Linked List--------------------------\n";
    cout << "Press '0' to show list and get size\n";
    cout << "Press '1' to add node by index\n";
    cout << "Press '2' to delete node by value\n";
    cout << "Press '3' to delete node by index\n";
    cout << "Press '4' to sort list\n";
    cout << "Press '5' to save list to a file\n";
    cout << "Press '6' to load list from a file\n";
    cout << "Press '7' to delete linked list\n";

    cout << "Press 'h' to get help\n";
    cout << "Press ESCAPE to exit\n";
    cout << "----------------------------------------\n";
}
template <typename T> void List<T>::handleMenu(int cmd) {
    switch (cmd)
    {
    case KEY_ESCAPE:
    {
        cout << "Testing ended!\n";
        exit(0);
    }
    case KEY_H:
    {
        printMenu(); break;
    }
    case KEY_ZERO:
    {
        showList();
        cout << "Size of linked list: " << getSize() << "\n";
        break;
    }
    case KEY_ONE: 
    {
        cout << "Enter the location (index) of new node: ";
        cin >> cmd;
        cout << "Enter value for new node: ";
        T* data = new T;
        /*cin >> *data;*/
        *data = getRandNum(0, 10000);
        addNode(data, cmd); break;
    }
    case KEY_TWO: 
    {
        cout << "Enter value for deleting node: ";
        T* data = new T; cin >> *data;
        deleByVal(data); break;
    }
    case KEY_THREE: 
    {
        cout << "Enter index of deleting node: ";
        cin >> cmd;
        deleByIndex(cmd); break;
    }
    case KEY_FOUR:
    {
        cout << "Enter 0 for increment, 1 for decrement: ";
        cin >> cmd;
        sortList(cmd); break;
    }
    case KEY_FIVE:
    {
        string fname;
        cout << "Enter file location (file name): ";
        cin >> fname;
        saveList(fname); break;
    }
    case KEY_SIX:
    {
        string fname;
        cout << "Enter file location (file name): ";
        cin >> fname;
        loadList(fname); break;
    }
    case KEY_SEVEN:
    {
        cout << "Delete all node!\n1";
        deleAll();;break;
    }
    default:
    {
        cout << "Unknown command\n";
        break;
    }
    }
}

// ------------------Add new node--------------------------------------------
template <typename T> void List<T>::addFirst(Node<T>*& pNode) {
    pNode->pNext = pHead;
    pHead = pNode; pNode = NULL; size++;
    cout << "Add new node " << *(pHead->pData) << " to the beginning of the list...\n";
}
template <typename T>  void List<T>::addLast(Node<T>* &pNode) {
    pTail->pNext = pNode;
    pTail = pNode; pNode = NULL; size++;
    cout << "Add new node " << *(pHead->pData) << " to the end of the list...\n";
}
template <typename T> void List<T>::addMid(Node<T>* &pNode, int index) {
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
    Node<T>* pTemp = pHead;
    pHead = pHead->pNext;
    delete pTemp; size--;
    cout << "Delete node from the beginning of the list...\n";
}
template <typename T> void List<T>::deleLast() {
    Node<T>* pTemp = pHead;
    while (pTemp->pNext != pTail) pTemp = pTemp->pNext;
    delete pTail; pTail = pTemp; size--;
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

// ---------------Sort list---------------------------------- //
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
template <typename T>  void List<T>::addNode(T* &data, int index) {
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
    while (pHead != nullptr) {
        deleFirst();
    }
    pTail = nullptr;
    cout << "Delete all node from the list...\n";
}
template <typename T> void List<T>::sortList(int i) {
    if (checkEmpty()) return;
    if (i == 0) sortHigh();
    else if (i == 1) sortLow();
}
template <typename T> void List<T>::addList(int s) {
    if (size != 0) deleAll();
    //for (int i = 0; i < s; i++) {
    //    addNode(nullptr);
    //}
}
template<typename T>
bool List<T>::checkEmpty()
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
template <typename T> int List<T>::getSize() {
    return size;
}
template <typename T> T* List<T>::getNode(int index) {
    if (size == 0) {
        cout << "Empty linked list!\n";
        return nullptr;
    }
    Node<T>* pTemp = findByIndex(index);
    return pTemp->pData;
}
template <typename T> Node<T>* List<T>::getHead() {
    return pHead;
}
template <typename T> Node<T>* List<T>::getTail() {
    return pTail;
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
    if (checkEmpty()) return -1;
    Node<T>* pTemp = pHead;
    for (int i = 0; i < size; i++) {
        if (pTemp->pData == NULL) return -1;
        if (*(pTemp->pData) == *data) return i;
        pTemp = pTemp->pNext;
    }
    cout << "Can't find index of this node!\n";
    return -1;
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
template <typename T> void List<T>::loadList(string filename) {
    ifstream input(filename, ios::binary);
    if (input.eof()) {
        cout << "Can't open file!\n";
        return;
    }
    input >> *this;
    input.close();
    cout << "Load file!\n";
}
template <typename T> void List<T>::saveList(string filename) {
    ofstream output(filename, ios::binary);
    output << *this;
    output.close();
    cout << "Save file!\n";
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

// -------------------Handle Menu -----------------------
template <typename T> void Queue<T>::printMenu() {
    cout << "--------------Queue--------------------------\n";
    cout << "Press '0' to show queue and get size\n";
    cout << "Press '1' to add new item\n";
    cout << "Press '2' to remove item\n";
    cout << "Press '3' to get first item\n";
    cout << "Press '4' to close queue\n";
    cout << "Press '5' to check if empty\n";

    cout << "Press 'h' to get help\n";
    cout << "Press ESCAPE to exit\n";
    cout << "----------------------------------------\n";
}
template <typename T> void Queue<T>::handleMenu(int cmd) {
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
        takeAllQueue();
        break;
    }
    case KEY_ONE:
    {
        cout << "Enter value for new item: ";
        T* data = new T;
        cin >> *data;
        enQueue(data);
        break;
    }
    case KEY_TWO:
    {
        deQueue();
        cout << "Deleted first node\n";
        break;
    }
    case KEY_THREE:
    {
        void* data = firstQueue();
        if (data == NULL) cout << "Empty queue\n";
        else cout << "First node is: " << static_cast<T*>(data) << "\n";
        break;
    }
    case KEY_FOUR:
    {
        closeQueue();
        cout << "Deleted queue\n";
        break;
    }
    case KEY_FIVE:
    {
        cout << isEmpty() << "\n";
        break;
    }
    default:
    {
        cout << "Unknown command\n";
        break;
    }
    }
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
template<typename T> void Stack<T>::takeAllStack(){
    Node<T>* current = pHead;
    while (current != nullptr) {
        // Print or process current->data
        cout << *(current->pData) << " ";
        current = current->pNext;
    }
    cout << "\n";
}
// -------------------Handle Menu -----------------------
template <typename T> void Stack<T>::printMenu() {
    cout << "--------------Stack--------------------------\n";
    cout << "Press '0' to show stack and get size\n";
    cout << "Press '1' to add new item\n";
    cout << "Press '2' to remove item\n";
    cout << "Press '3' to get first item\n";
    cout << "Press '4' to close stack\n";
    cout << "Press '5' to check if empty\n";

    cout << "Press 'h' to get help\n";
    cout << "Press ESCAPE to exit\n";
    cout << "----------------------------------------\n";
}
template <typename T> void Stack<T>::handleMenu(int cmd) {
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
        takeAllStack();
        break;
    }
    case KEY_ONE:
    {
        cout << "Enter value for new item: ";
        T* data = new T;
        cin >> *data;
        pushBack(data);
        break;
    }
    case KEY_TWO:
    {
        popStack();
        cout << "Delete first node!\n";
        break;
    }
    case KEY_THREE:
    {
        void* data = topStack();
        if (data == NULL) cout << "No value\n";
        else cout << "First node is: " << static_cast<T*>(data) << "\n";
        break;
    }
    case KEY_FOUR:
    {
        closeStack();
        cout << "Deleted stack!\n";
        break;
    }
    case KEY_FIVE:
    {
        cout << isEmpty() << "\n";
        break;
    }
    default:
    {
        cout << "Unknown command\n";
        break;
    }
    }
}