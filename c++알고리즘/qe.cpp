//큐는 선입선출 가장 먼저 들어온 데이터가 처리된다
//	pop <- 값ㅣ값ㅣ값ㅣ <- push
//  front ------------  back

#include <iostream>

using namespace std;

const int MAX = 20000905;
bool check;
int dat1[MAX];
int high1 = 0;
int low1 = 0;


void push1(int x) {
	dat1[low1++] = x;
};

void pop1() {
	high1++;
};

int back1() {
	return dat1[low1 - 1];
};

int front1() {
	return dat1[high1];
}

void test() {
	push1(10); push1(20); push1(30);
	cout << front1() << '\n';
	cout << back1() << '\n';
	pop1(); pop1();
	push1(15); push1(25);
	cout << front1() << '\n';
	cout << back1() << '\n';
}
int main(void) {
	test();
};