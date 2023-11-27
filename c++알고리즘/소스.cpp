#include <iostream>
using namespace std;

const int Max = 100;
int Stack[Max];
int height = 0;


void push(int x) {
	Stack[height++] = x;
}

int pop() {
	Stack[height--];
	return Stack[height];
}

void Bottom() {
	 cout << "Bottom: " << Stack[0] << endl;
	 
}
void Top() {
	cout << "Top: " << Stack[height-1] << endl;
}


int main() {
	push(10);
	push(8);
	push(6);
	push(24);
	push(53);
	push(5);
	cout << "Stack" << "\n" << endl;
	cout << "Top" << endl;
	for (int i = height-1; i >= 0; i--) {
			cout << Stack[i] << endl;
	}
	cout << "Bottom" << "\n" << endl;
	Bottom();
	Top();
	cout << pop() << endl;
	cout << pop() << endl;
	push(30);
	Bottom();
	Top();


	return 0;
}
