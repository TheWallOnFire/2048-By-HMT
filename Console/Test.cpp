#include "pch.h"
#include "Test.h"
#include "Types.h"

#include "Matrix.cpp"
#include "Structure.cpp"
using namespace std;

void testMenu() {
	printMenu();
	while (true) {
		int keycode = _getch();
		if (keycode == KEY_ZERO);
		else if (keycode == KEY_ONE) testNode();
		else if (keycode == KEY_TWO) testLinkedList();
		else if (keycode == KEY_THREE) testQueue();
		else if (keycode == KEY_FOUR) testStack();
		else if (keycode == KEY_FIVE) testMatrix();
		else if (keycode == KEY_SIX) testRandom();
		else if (keycode == KEY_SEVEN) testKey();
		else if (keycode == KEY_EIGHT) testObjectList();
		else if (keycode == KEY_NINE) testColor();

		else if (keycode == KEY_ESCAPE) break;
		else if (keycode == KEY_H) printMenu();
		else;
	}
	exit(0);
}

void printMenu() {
	cout << "----------------Testing mode--------------------\n";
	cout << "Press '0' to test \n";
	cout << "Press '1' to test node\n";
	cout << "Press '2' to test linked list\n";
	cout << "Press '3' to test queue\n";
	cout << "Press '4' to test stack\n";
	cout << "Press '5' to test matrix\n";
	cout << "Press '6' to test random\n";
	cout << "Press '7' to test key\n";
	cout << "Press '8' to test testObjectList\n";
	cout << "Press '9' to test color\n";

	cout << "Press 'h' to get help\n";
	cout << "Press ESCAPE to exit\n";
	cout << "----------------------------------------\n";
}

void testNode() {
	cout << "Testing node!\n";
	Node<int>* ptr = new Node<int>;
	ptr->printMenu();
	while (true) {
		cout << "Enter your command:";
		int key = _getch();
		cout << (char) key << "\n";
		ptr->handleMenu(key);
	}
	delete ptr;
}
void testLinkedList() {
	cout << "Testing linked list!\n";
	List<int>* ptr = new List<int>;
	ptr->printMenu();
	while (true) {
		cout << "Enter your command:";
		int key = _getch();
		cout << (char) key << "\n";
		ptr->handleMenu(key);
	}
	delete ptr;
}
void testQueue() {
	cout << "Testing queue!\n";
	Queue<int>* ptr = new Queue<int>;
	ptr->initQueue();
	ptr->printMenu();
	while (true) {
		cout << "Enter your command:";
		int key = _getch();
		cout << (char)key << "\n";
		ptr->handleMenu(key);
	}
	ptr->closeQueue();
}
void testStack() {
	cout << "Testing stack!\n";
	Stack<int>* ptr = new Stack<int>;
	ptr->initStack();
	ptr->printMenu();
	while (true) {
		cout << "Enter your command:";
		int key = _getch();
		cout << (char)key << "\n";
		ptr->handleMenu(key);
	}
	ptr->closeStack();
}

void testMatrix() {
	cout << "Testing matrix!\n";
	Matrix<int>* ptr = new Matrix<int>;
	ptr->printMenu();
	while (true) {
		cout << "Enter your command:";
		int key = _getch();
		cout << (char)key << "\n";
		ptr->handleMenu(key);
	}
	delete ptr;
}
void testRandom() {
	cout << "Testing randomness!\n";
	cout << "Random number:" << getRandNum(0, 1000) << "\n";
}
void testKey() {
	cout << "Testing keycode!\n";
	while (true) {
		int keycode = _getch();
		std::cout << keycode << "\n";
		if (keycode == KEY_ESCAPE) exit(0);
	}
}

void testObjectList() {
	cout << "Testing list that store object!\n";
}

void testColor()
{
	cout << "Test color!\n";
	cout << "Enter some test!\n";
	string s; getline(cin, s);
	cout << s << "\n";
	testMenu();
}