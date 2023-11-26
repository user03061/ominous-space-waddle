//덱 알고리즘
#include <iostream>
using namespace std;

const int MX = 1000000;
int dat[2 * MX + 1];
int head = MX, tail = MX;

void push_front(int x) {
	dat[--head] = x;
};

void push_back(int x) {
	dat[tail++] = x;
};

void pop_front(int x) {
	head++;
};

void pop_back(int x) {
	tail--;
};

int front() {
	return dat[head];
};

int back() {
	return dat[tail - 1];
}

void test() {
	push_back(30);
	cout << front() << '\n';
	cout << back() << '\n';
	push_front(25);
	push_back(12);
	cout << back() << '\n';
	push_back(62);
	pop_front(30);
	cout << front() << '\n';
	pop_front(30);
	cout << back() << '\n';
};

int main(void) {
	test();
}