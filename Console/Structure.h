#pragma once

//------------------------NODE STRUCT--------------------------------------
template <typename T> struct Node // Node struct
{
    // ------------ Pointer of node-----------------------
    T* pData; // Ptr to data
    Node<T>* pNext; // Ptr to next node

    // ------------- List of functions -----------------------
    Node();// Constructor
    ~Node(); // Destructor
    T* get() const; // Accessor
    void set(T*& d); // Mutate
    void show(); // Print data

    // ------------------Show list of tools------------------
    void printMenu();
    void handleMenu(int cmd);
};

//---------------LINKED LIST--------------------------------------------
template <typename T> struct List // Linked List struct
{
private:
    Node<T>* pHead;
    Node<T>* pTail; // Head and Tail ptr
    int size; // Count size of linked list

public:
    // ----------------------Linked list setup-----------------------
    List();
    ~List();

    // -----------------Show list of tools--------------------
    void printMenu();
    void handleMenu(int cmd);

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
    void addList(int s);// Create an empty list
    bool checkEmpty(); // Check empty list

    // --------------------Visualize list---------------------
    void showList();
    int getSize();
    T* getNode(int);
    Node<T>* getHead();
    Node<T>* getTail();

    // ------------------Finding node-------------------
    Node<T>* findByIndex(const int); // Find by index
    int findByValue(T*); //Find by value

    // ----------------Input/Output file-----------------------
    template <typename T>
    friend std::ostream& operator<<(std::ostream& out, List<T>& list);
    template <typename T>
    friend std::istream& operator>>(std::istream& in, List<T>& list);

    void loadList(std::string filename);
    void saveList(std::string filename);
};

// ------------------------ QUEUE STRUCT --------------------
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

    // ------------------Show list of tools------------------
    void printMenu();
    void handleMenu(int cmd);
};

// ------------------------ STACK STRUCT --------------------
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

    // ------------------Show list of tools------------------
    void printMenu();
    void handleMenu(int cmd);
};