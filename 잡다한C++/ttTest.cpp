#include <iostream>
#include <conio.h>  //키보드 입력 키 값을 받기 위해 사용
#include <windows.h> //system("cls") sleep()등을 사용하기 위해 추가

using namespace std;

bool End; //게임 종료 여부
int x, y, Score;  //조종할 캐릭터의 좌표와 점수
int aiX, aiY;
string GameOverMsg[3] = { "봇에게 맞았습니다..", "봇이 쎄게 때렸습니다..?", "봇이랑 충돌했습니다!!"};
int speed = 50; //게임 속도 지정
int PointX, PointY;  //점수를 얻기 위한 아이템 좌표
enum gamePan { width = 40, height = 27 }; //게임판 크기 설정
enum Move { STOP = 0, LEFT, RIGHT, UP, DOWN }; //움직이기 위한 정의 
Move Key;
int TailX[100], TailY[100];
int PlusTail = 1; //추가 꼬리

int CountSet[3][7][7] = {
	{
		2,2,2,2,2,2,2,
		0,0,0,0,0,0,2,
		0,0,0,0,0,0,2,
		2,2,2,2,2,2,2,
		0,0,0,0,0,0,2,
		0,0,0,0,0,0,2,
		2,2,2,2,2,2,2
	},
	{
		0,0,2,2,2,2,0,
		2,2,0,0,0,0,2,
		0,0,0,0,0,2,0,
		0,0,0,0,2,0,0,
		0,0,0,2,0,0,0,
		0,0,2,0,0,0,2,
		2,2,2,2,2,2,0
	},
	{
		0,0,0,2,0,0,0,
		0,0,2,2,0,0,0,
		0,0,0,2,0,0,0,
		0,0,0,2,0,0,0,
		0,0,0,2,0,0,0,
		0,0,0,2,0,0,0,
		2,2,2,2,2,2,2
	}

};


void CursorView() { //콘솔 커서 제거 - <- 요런 형태로 생긴 흰색 커서
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = false; //false 커서 제거 true 커서 생성;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void gotoxy(int x, int y) { //해당 위치에 프린트 출력 subScreen 함수에 적용
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void GameStart() {
	system("mode con col=50 lines=50 | title 메인메뉴");
	cout << "\033[1;46m" << "▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩" << "\033[0m" << endl; //cyan색
	cout << "\033[1;46m" << "▩                                                                                                      ▩" << "\033[0m" << endl;
	cout << "\033[1;46m" << "▩            ▩▩▩▩▩  ▩    ▩▩▩▩▩     ▩  ▩▩▩  ▩ ▩▩▩  ▩  ▩▩▩     ▩▩▩▩▩  ▩     ▩" << "\033[0m" << endl;
	cout << "\033[1;46m" << "▩                 ▩     ▩            ▩     ▩ ▩    ▩ ▩     ▩  ▩ ▩    ▩           ▩   ▩     ▩" << "\033[0m" << endl;
	cout << "\033[1;46m" << "▩               ▩ ▩    ▩    ▩▩▩▩▩ ▩▩▩ ▩    ▩ ▩  ▩▩   ▩ ▩    ▩          ▩    ▩     ▩" << "\033[0m" << endl;
	cout << "\033[1;46m" << "▩              ▩    ▩  ▩    ▩             ▩  ▩▩▩  ▩   ▩    ▩  ▩▩▩          ▩     ▩     ▩" << "\033[0m" << endl;
	cout << "\033[1;46m" << "▩             ▩      ▩ ▩    ▩▩▩▩▩     ▩          ▩  ▩     ▩ ▩▩▩▩        ▩      ▩     ▩" << "\033[0m" << endl;
	cout << "\033[1;46m" << "▩                                      ▩▩▩                              ▩          ▩       ▩     ▩" << "\033[0m" << endl;
	cout << "\033[1;46m" << "▩                                     ▩    ▩                             ▩                          ▩" << "\033[0m" << endl;
	cout << "\033[1;46m" << "▩                                     ▩    ▩                             ▩                          ▩" << "\033[0m" << endl;
	cout << "\033[1;46m" << "▩                                      ▩▩▩                                                          ▩" << "\033[0m" << endl;
	cout << "\033[1;46m" << "▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩" << "\033[0m" << endl;
	cout << "\033[1;33m" << "\n\n" << "                                      시작하려면 아무키나 입력 하세요." << "\033[0m" << endl;
	if (_getch());
}

void CountGame() {
	system("mode con cols=35 lines=20 | title 게임 카운트");
	system("cls");
	for (int j = 0; j < 7; j++) {
		if (CountSet[0][j][6]) cout << "\033[0m" << endl;
		for (int k = 0; k < 7; k++) {
			if (CountSet[0][j][k] == 0) cout << "  ";
			if (CountSet[0][j][k] == 2) cout << "\033[1;33m" << "▩"; //노랑색
		}
	}
	Sleep(1000);
	system("cls");
	for (int j = 0; j < 7; j++) {
		if (CountSet[0][j][6]) cout << "\033[0m" << endl;
		for (int k = 0; k < 7; k++) {
			if (CountSet[1][j][k] == 0) cout << "  ";
			if (CountSet[1][j][k] == 2) cout << "\033[1;32m" << "▩"; //초록색
		}
	}
	Sleep(1000);
	system("cls");
	for (int j = 0; j < 7; j++) {
		if (CountSet[0][j][6]) cout << "\033[0m" << endl;
		for (int k = 0; k < 7; k++) {
			if (CountSet[2][j][k] == 0) cout << "  ";
			if (CountSet[2][j][k] == 2) cout << "\033[1;33m" << "▩"; //노랑색
		}
	}
	Sleep(1000);
}
void Set() {
	End = false; //게임 진행
	Key = STOP;
	Score = 0;
	speed = 150;
	x = width / 2; //캐릭터가 중앙에 생성
	y = height / 2;
	PointX = rand() % width; //아이템이 랜덤 생성
	PointY = rand() % height;
}

void Screen() {
	system("cls");
	for (int i = 0; i < width - 18; i++) cout << "\33[1;43m" << "■"; //위쪽 벽 구성 (노랑)
	cout << "\033[0m" << endl; //탭
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) cout << "\33[1;43m" << "■";
			if (i == y && j == x) cout << "\33[1; 33m" << "O";
			else if (aiX == i && aiY == j) cout << "U";
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
				cout << "\33[1;43m" << "■";
		}
		cout << "\033[0m" << endl;
	}

	for (int i = 0; i < width - 18; i++) //하단 화면 구성
		cout << "\33[1;43m" << "■";
	cout << "\033[0m" << endl;

}



void subScreen() {
	gotoxy(width + 21, height - 10); //게임판 우측쯤에 아래 내용 생성
	cout << "\33[1;30m" << "점수:" << Score << "    WASD:이동 N:멈추기 X:게임종료" << "\033[0m" <<  endl;

	gotoxy(width + 21, height - 12);
	cout << "\33[1;30m" << "p키 게임속도 증가     l키 게임속도 감소" << "\033[0m" << endl;


}


void BotMoving() { //랜덤으로 봇이 움직임 봇 = "U"
	int ai = rand() % 4;
	if (ai == 1) aiX++;
	else if (ai == 2) aiX--;
	else if (ai == 3) aiY++;
	else if (ai == 4) aiY--;


	if (aiX >= width) aiX = 1; //봇이 게임판 밖으로 나가는걸 방지
	else if (aiX < 0) aiX = width - 1;
	if (aiY >= height) aiY = height - 1;
	else if (aiY < 0) aiY = 1;

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
		case 'p':
			if (speed >= 50) {
				speed -= 50;
				gotoxy(width + 21, height - 15);
				cout << "\33[1;32m" << " [ 게임속도 증가 -50 속도: " << speed << " ] " << "\033[0m" << endl;
			}
			break;
		case 'l':
				speed += 50;
				gotoxy(width + 21, height - 15);
				cout << "\33[1;30m" << " [ 게임속도 감소 +50 속도: " << speed << " ] " << "\033[0m" << endl;
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
		Swap2X = TailX[i];  //스왑
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
		gotoxy(width + 21, height - 17);
		cout << " [ 게임점수 +10 흭득 점수: " << Score << " ] " << endl;
		PlusTail++;  //꼬리 하나 증가 "o"
		PointX = rand() % width;
		PointY = rand() % height;
	}
	else if (PointX == aiX && PointY == aiY) {
		Score += 10; //점수 10점 부여
		PlusTail++;  //꼬리 하나 증가 "o"
		PointX = rand() % width;
		PointY = rand() % height;
	}

	if (aiX == y && aiY == x) End = true; //봇이랑 닿으면 게임 종료


}

void GameSpeed() {

	if (_kbhit())
	{
		switch (_getch())
		{
		case 'p':
			speed += 50;
			gotoxy(width + 21, height - 15);
			cout << "게임속도 +50 증가 속도: " << speed << endl;
			break;
		case 'l':
			speed -= 50;
			gotoxy(width + 21, height - 15);
			cout << "게임속도 -50 감소 속도: " << speed << endl;
			break;
		}
	}

}

void GameOverOK() {
	gotoxy(0, 3);
	cout << "\33[1;34m" << "                       ▩▩▩▩▩▩▩▩▩▩▩▩▩▩" << "\033[0m" << endl;
	cout << "\33[1;34m" << "                       ▩                        ▩" << "\033[0m" << endl;
	cout << "\33[1;34m" << "                       ▩       GameOver         ▩" << "\033[0m" << endl;
	cout << "\33[1;34m" << "                       ▩       점수:" <<  "            ▩    " << "\033[0m" << endl;
	cout << "\33[1;34m" << "                       ▩                        ▩" << "\033[0m" << endl;
	cout << "\33[1;34m" << "                       ▩▩▩▩▩▩▩▩▩▩▩▩▩▩" << "\033[0m" << endl;
	gotoxy(40, 6);
	cout << Score;
	cout << "\n\n";

	if (aiX == y && aiY == x) {
		gotoxy(25, 10);
		int msgSet = rand() % 3;
		cout << "\33[1;33m" << GameOverMsg[msgSet] << "\033[0m" <<  endl; //메세지 3개 중 1개 랜덤출력
	}

}


int main()
{
	CursorView();
	GameStart();
	CountGame();
	system("mode con cols=105 lines=40 | title 지렁이 키우기");
	Set();
	while (!End)
	{
		Screen();
		subScreen();
		Moving();
		BotMoving();
		SecondSet();
		Sleep(speed);
	}
	system("mode con cols=75 lines=30 | title");
	system("cls");
	GameOverOK();
	return 0;
	
}
