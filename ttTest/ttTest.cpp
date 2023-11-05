#include <iostream>
#include <conio.h>  //키보드 입력 키 값을 받기 위해 사용
#include <windows.h>

using namespace std;

bool End; //게임 종료 여부
const int width = 30;
const int height = 22;
int x, y, Score;  //조종할 캐릭터의 좌표와 점수
int PointX, PointY;  //점수를 얻기 위한 아이템 좌표
enum Move {STOP = 0, LEFT, RIGHT, UP, DOWN}; //움직이기 위한 정의 
Move Key;
int TailX[100], TailY[100];
int PlusTail = 1; //추가 꼬리


void Set() {
	End = false; //게임 진행
  	Key = STOP;
	Score = 0; 
	x = width / 2; //캐릭터가 중앙에 생성
	y = height / 2; 
	PointX = rand() % width; //아이템이 랜덤 생성
	PointY = rand() % height;
}

void Screen() {
	system("cls");
	for (int i = 0; i < width - 13; i++) cout << "■"; //위쪽 벽 구성
	cout << endl; //탭
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) cout << "■";
			if (i == y && j == x)
				cout << "O";
			else if (i == PointY && j == PointX)  //포인트 텍스트 생성
				cout << "P";
			else
			{
				bool print = false;
				for (int k = 0; k < PlusTail; k++)
				{
					if (TailX[k] == j && TailY[k] == i)
					{
						cout << "o";
						print = true; //true로 바꾸어 꼬리를 하나 그린다
					}
				}
				if (!print)
					cout << " ";
			}
			if (j == width - 1)  //오른쪽 벽 구성
				cout << "■";
		}
		cout << endl;
	}

	for (int i = 0; i < width - 13; i++) //하단 화면 구성
		cout << "■";
	cout << endl;
	cout << "점수:" << Score << "    WASD:이동 N:멈추기 X:게임종료" << endl;
}

void Moving() {
	if (_kbhit()) //키값을 입력받는 함수: #include <conio.h>
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
		case 'n':
			Key = STOP;
			break;
		case 'x':
			End = true;
			break;
		}
	}

	switch (Key)  //위 스위치/케이스 문에서 적용된 key값의 동작을 위해 다시 스위치/케이스 문 작성
	{
	case LEFT:  
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

}


void SecondSet() {
	int SwapX = TailX[0];  //초기 꼬리값을 0
	int SwapY = TailY[0];
	int Swap2X, Swap2Y;
	TailX[0] = x;
	TailY[0] = y;
	for (int i = 1; i < PlusTail; i++) 
	{
		Swap2X = TailX[i];  //스왑 알고리즘
		Swap2Y = TailY[i];
		TailX[i] = SwapX;
		TailY[i] = SwapY;
		SwapX = Swap2X;
		SwapY = Swap2Y;
	}

	if (x >= width) x = 0;  //캐릭터가 벽을 넘을 경우 위치를 조정하기 위해 조건문 설정
	else if (x < 0) x = width - 1;

	if (y >= height) y = 0;
	else if (y < 0) y = height - 1;

	if (PointX == x && PointY == y) {  //캐릭터의 좌표와 Point포인트의 좌표가 겹칠 경우 포인트를 재생성
		Score += 10; //점수 10점 부여
		PlusTail++;  //꼬리 하나 증가 "o"
		PointX = rand() % width; 
		PointY = rand() % height;
	
	}
}


int main() 
{
	Set();
	while (!End)
	{
		Screen();
		Moving();
		SecondSet();
		Sleep(50);
	}
	return 0;
}