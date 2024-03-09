#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

const int width = 25;
const int height = 20;

bool GameOver;
bool start = false;
int X, Y; //플레이어 좌표
int Wave, a;
int Score;
int x, y; //공 좌표
enum Move{RIGHT,LEFT,UP,DOWN};
Move Key;

void CursorView() { //콘솔 커서 제거
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = false; //false 커서 제거 true 커서 생성;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void gotoxy(int x, int y) {

	COORD pos = { x,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

void MainMenu() {
	cout << "\n\n" << "                                        ▩    ▩       ▩ ▩▩▩▩ ▩▩▩▩" << endl;
	cout << "                                        ▩   ▩▩      ▩ ▩    ▩ ▩    ▩" << endl;
	cout << "                                    ▩▩▩  ▩  ▩ ▩▩▩ ▩▩▩▩ ▩▩▩▩" << endl;
	cout << "                                    ▩  ▩   ▩▩  ▩  ▩       ▩ ▩" << endl;
	cout << "                                    ▩▩▩    ▩   ▩▩▩ ▩▩▩▩ ▩▩▩▩" << endl;

	cout << "\n\n" << "                                      시작하려면 아무키나 입력 하세요." << endl;
	if (_getch()) start = true;
}

void GameSet() {
	GameOver = false;
	Score = 0;
	Wave = 2;
	X = width / 2;
	Y = 19;
}//▩

void Screen() {
	system("cls");
	for (int i = 0; i < width-10; i++) cout << "▩";
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width+1; j++) {
			if (j == 0) cout << "▩";
			if (Y <= 15) Y = 15;
			else if (Y >= height) Y = 19;
			if (X <= width && X >= width) X = 1;
			if (i == Y && j == X) cout << "P";
			if (i == y && j == x) cout << "O";
				
			cout << " ";
			if (j == width) cout << "▩" << endl;
		}
	}
	for (int i = 0; i < width - 10; i++) cout << "▩";

	cout << endl;
	cout << "점수: " << Score;

}

void Moving() {
	if (_kbhit()) //키값을 입력받는 함수
	{
		switch (_getch()) //키값을 받기 위해 대기하는 함수
		{
		case 'w':
			Key = UP;
			break;
		case 's':
			Key = DOWN;
			break;
		case 'a':
			Key = LEFT;
			break;
		case 'd':
			Key = RIGHT;
			break;
		case 'x':
			GameOver = true;
			break;
		default:
			break;
		}
	};

	switch (Key)
	{
	default:
		break;
	case LEFT:
		X--;
		break;
	case RIGHT:
		X++;
		break;
	case UP:
		Y--;
		break;
	case DOWN:
		Y++;
		break;
	}
};

int BoomMoving() {
	while (x < width && y < 20) {//y값이 게임테이블을 탈출하는 문제상황이 발생함 -> and연산자를 활용
		return x = rand() % width;
		y = 1;
		if (y >= 20) { //폭탄을 재 생성 해야함 -> while문을 다시 실행하여 x,y좌표값을 초기화 시킴
			continue;
		}
			gotoxy(x, y);
			cout << "O";
	}
}



int plusMove() {
	while (true) {
		if (y < 20) {
			return y++;
		}
		else if (y == 20) {
			y = 1;
			Score += 10; //총알을 피하고 총알이 바닥에 닿으면 점수 증가
		}
		gotoxy(x + a, y);
		cout << "O";

		if (X >= width) X = width - 1;
		if (X < 1) X = 2;
		if (Y >= height) Y = height - 1;
	}
}



void End() {
	if (x == X && y == Y) GameOver = true;
	if (x + 1 == X && y+1 == Y) GameOver = true;//게임 종료 조건발동이 어려움 -> 종료 조건 난이도를 상승시킴 
	if (x + 2 == X && y+2 == Y) GameOver = true;
	if (x - 1 == X && y - 1 == Y) GameOver = true;
	if (x - 2 == X && y - 2 == Y) GameOver = true;
}

void GameStop() {
	cout << "\n\n" << "                                                  GameOver" << endl;
	cout << "                                                  점수: " << Score << endl;
}
	


int main() {
	CursorView();
	MainMenu();
	GameSet();
	while (!GameOver && start)
	{
		BoomMoving();
		Screen();
		Moving();
		plusMove();
		End();
		Sleep(100);
	}
	if (GameOver) {
		system("cls");
		GameStop();
	}
	return 0;
}