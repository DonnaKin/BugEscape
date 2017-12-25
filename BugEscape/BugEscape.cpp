#define _CRT_SECURE_NO_WARNINGS
//헤더파일
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#define STICK 15 //스테이지 별 최대 장애물 갯수
#define SPEED 20 // 장애물 속도
#define COUNT 3   // 레벨마다 늘어날 장애물 갯수

using namespace std;

//프로토타입
void gotoxy(int x, int y); //끝
void GameWay(); //끝
void GameStart();
void choiceScreen(int choice); //끝 
void GameEnd(); //끝
void Result();
void Ranking(); // 랭크화면
void scoreCompare(); // 점수비교
void getRank(); // 파일에서 랭크 정보들 가져오기
void saveRank(); //랭크 파일에 저장
void rankInput(int); //랭킹관련 정보 입력
void Cursor(int n);//커서 깜박깜박
BOOL IsKeyDown(int Key); //키보드 입력

//int score = 0;
struct Player {
	int rank;
	int score = 0;
	char name[20];
};

struct OBSTACLE
{
	int x, y, wait;
};

//메인
int main() {
	//창크기고정
	system("mode con cols=110 lines=35");
	Cursor(0);
	ifstream ifile;

	char line[200]; // 한 줄씩 읽어서 임시로 저장할 공간

	ifile.open("screen.txt");  // 파일 열기

	if (ifile.is_open())
	{
		while (ifile.getline(line, sizeof(line))) // 한 줄씩 읽어 처리를 시작한다.
		{
			cout << line << endl; // 내용 출력
		}
	}

	ifile.close(); // 파일 닫기
	gotoxy(37, 21);
	//선택화면 출력
	cout << "아무키나 누르면 시작합니다." << endl;
	gotoxy(98, 33);
	cout << "2502 김민경";
	_getch();
	system("cls");
	choiceScreen(0);

	return 0;
}

//메뉴 선택
void choiceScreen(int choice) {
	system("cls");
	system("mode con cols=110 lines=35");
	ifstream ifile;

	char line[200]; // 한 줄씩 읽어서 임시로 저장할 공간

	ifile.open("menu.txt");  // 파일 열기

	if (ifile.is_open())
	{
		while (ifile.getline(line, sizeof(line))) // 한 줄씩 읽어 처리를 시작한다.
		{
			cout << line << endl; // 내용 출력
		}
		cout << endl;
	}
	ifile.close(); // 파일 닫기
	cout << "                                  선택하세요>> ";
	choice = 0;
	cin >> choice;
	switch (choice)
	{
	case 1: system("cls"); GameWay(); break;
	case 2: system("cls"); GameStart(); break;
	case 3: system("cls"); Ranking(); break;
	case 4: system("cls"); GameEnd(); break;
	default: system("cls"); 
			gotoxy(40,15); 
			cout << "올바른 숫자를 선택해주세요!" << endl; 
			Sleep(500); 
			choiceScreen(0);
	}
}

//게임 방법
void GameWay() {
	system("cls");
	system("mode con cols=110 lines=35");
	ifstream ifile;

	char line[200]; // 한 줄씩 읽어서 임시로 저장할 공간

	ifile.open("GameWay.txt");  // 파일 열기

	if (ifile.is_open())
	{
		while (ifile.getline(line, sizeof(line))) // 한 줄씩 읽어 처리를 시작한다.
		{
			cout << line << endl; // 내용 출력
		}
		cout << endl;
	}
	ifile.close(); // 파일 닫기

	cout << "                                  선택하세요>> ";
	int choice_1 = 0;
	cin >> choice_1;
	switch (choice_1)
	{
	case 1: GameStart(); break;
	case 2: choiceScreen(0); break;
	default: cout << "올바른 숫자를 선택해주세요!" << endl;
	}
	gotoxy(98, 33);
	cout << "2502 김민경";
}

Player player[7];
struct OBSTACLE ob[STICK], user;
int i, check = 1, evade = 0,level = 1;
int speed = 75 - level * SPEED;
// 레벨업에 필요한 장애물개수
int levelup = 10 + level * 10;
int gamescore = 0;
//게임 시작
void GameStart() {
	system("cls");
	system("mode con cols=110 lines=35");
	//생명 표시
	system("color 0");
	int count = 5 + level * COUNT;
	// 장애물 개수 체크
	if (count >= STICK) count = STICK - 1;
	// 스피드 체크. (최소값이 10 보다 작지 않도록 저정)
	if (speed < 10) speed = 10;
	// 시작위치
	user.x = 50;
	user.y = 26;
	// 장애물 초기화
	for (i = 0; i<count; i++)
	{
		ob[i].x = rand()%50+24;
		ob[i].y = 3;
		ob[i].wait = rand() % 100;
	}
	player[i].score = 0;
	int life = 3;
	while (life!=0)
	{
		gamescore = evade * 10;
		// 스피드
		Sleep(speed);
		system("cls");
		// 게임 환경 출력.
		cout << "생명 : " << life << endl;
		cout<<"[Bug Escape]\tLEVEL"<<level<<"\n점수 : "<< gamescore;
		gotoxy(20, 30);
		cout<<"▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤";
		cout << "▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤";
		gotoxy(98, 33);
		cout << "2502 김민경";
		// 움직임 처리
		if (IsKeyDown(VK_LEFT))
		{
			if (user.x > 20)
			{
				user.x--;
				if (IsKeyDown(VK_DOWN))
					user.x--;
			}
		}
		if (IsKeyDown(VK_RIGHT))
		{
			if (user.x <= 70)
			{
				user.x++;
				if (IsKeyDown(VK_DOWN) && user.x <= 22)
					user.x++;
			}
		}
		// 캐릭터 출력
		gotoxy(user.x, user.y);
		cout << "┐┌";
		gotoxy(user.x, user.y + 1);
		cout<<"-■-";
		gotoxy(user.x, user.y + 2);
		cout<<"┘└";
		// 장애물 움직임 처리
		system("color 0");
		for (i = 0; i<count; i++)
		{
			if (ob[i].wait > 0)
			{
				// 대기시간 동안 장애물 대기하기
				ob[i].wait--;
			}
			else
			{
				// 장애물 아래로 이동
				ob[i].y++;
				// 장애물이 제일 밑에 도착 했을 때
				if (ob[i].y >= 29)
				{
					ob[i].x = rand() % 50 +24;
					ob[i].y = 3;
					evade++;  // 피한 장애물개수 카운트
				}
				// 장애물 출력
				gotoxy(ob[i].x, ob[i].y);
				printf("----------------------------");

				// 충돌 체크
				if (ob[i].x - user.x < 10 && ob[i].y == user.y)
				{
					check = 0;
					--life;
				}
				
			}
		}
		// 피한 장애물의 개수가 15개면 레벨업
		/*if (evade > levelup) {
			system("cls");
			gotoxy(45,15);
			cout << "STAGE 2" << endl;
			//Sleep(500);
				scoreCompare();
				break;
		}*/
		if (life == 1) { //생명이 1이면 빨간색으로 바뀜
			system("color 47");
		}
		else system("color 0");
	}
	
	system("cls");
	Sleep(1000);
	Result();
	gamescore = 0;
	evade = 0;
	system("color 0");
	choiceScreen(0);
	exit(0);
}

void Result() {
	system("cls");
	system("color 0");
	system("mode con cols=110 lines=35");
	gotoxy(45, 10);
	cout << "------------------" << endl;
	gotoxy(45, 11);
	cout << "  최종 단계 : 1" << endl;
	gotoxy(45, 12);
	cout << "  점수 : " << gamescore <<endl;
	gotoxy(45, 13);
	cout << "------------------" << endl;
	gotoxy(98, 33);
	cout << "2502 김민경";
	Sleep(500);
	scoreCompare();
}

void Ranking() {
	getRank();
	system("cls");
	system("mode con cols=110 lines=35");
	system("Color 0");
	gotoxy(31, 7);
	cout << "  ─────────────────";
	gotoxy(31, 9);
	cout << "                순위                  ";
	gotoxy(31, 11);
	cout << "  ─────────────────";
	for (int i = 0; i < 5; i++) {
		gotoxy(38, 13 + i * 2);
		printf("%4d %10s %5d\n", player[i].rank, player[i].name, player[i].score);
	}
	gotoxy(88, 29);
	cout << "2502 김민경";

	char choose = _getch();
	choiceScreen(0);
}

void getRank() {
	system("cls");
	system("color 0");
	system("mode con cols=110 lines=35");
	ifstream ifile;

	ifile.open("score.txt");

	if (ifile.is_open()) {
		for (int i = 0; i < 5; i++) {
			ifile >> player[i].rank;
			ifile >> player[i].name;
			ifile >> player[i].score;
		}
	}
}

void saveRank() {
	system("cls");
	system("color 0");
	system("mode con cols=110 lines=35");
	ofstream ofile("score.txt");

	for (int i = 0; i < 5; i++) {
		ofile << i + 1 << "\t" << player[i].name << "\t" << player[i].score << endl;
	}

	ofile.close();
}

void scoreCompare() {
	getRank();
	system("cls");
	system("color 0");
	system("mode con cols=110 lines=35");
	
	for (int i = 0; i < 5; i++) {
		if (player[i].score<gamescore) {
			rankInput(i);
			saveRank();

			system("cls");
			gotoxy(40, 14);
			cout << "랭 킹 등 록 완 료";
			Sleep(1000);
			break;
		}
	}
}

void rankInput(int a) {
	char n[20];

	system("cls");
	system("color 0");
	system("mode con cols=110 lines=35");
	gotoxy(30, 14);
	cout << "최종점수는 "<<gamescore << "점입니다\n";
	gotoxy(30, 15);
	cout<<"이름을 입력해주세요 >> ";
	cin>>n;
	
	for (int i = 4; i >= a; i--) {
		strcpy(player[i].name, player[i - 1].name);
		player[i].score = player[i - 1].score;
	}

	strcpy(player[a].name, n);
	player[a].score = gamescore;
}

void GameEnd() {
	system("cls");
	system("color 0");
	ifstream ifile;

	char line[200]; // 한 줄씩 읽어서 임시로 저장할 공간

	ifile.open("End.txt");  // 파일 열기

	if (ifile.is_open())
	{
		while (ifile.getline(line, sizeof(line))) // 한 줄씩 읽어 처리를 시작한다.
		{
			cout << line << endl; // 내용 출력
		}
		cout << endl;
	}
	ifile.close(); // 파일 닫기
	gotoxy(45, 21);
	cout << "종료되었습니다~!!!" << endl;
	gotoxy(98, 33);
	cout << "2502 김민경";
}

//좌표지정
void gotoxy(int x, int y)
{
	COORD pos = { (short)x,(short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//커서 깜박깜박
void Cursor(int n) {
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = n;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

//키보드 입력
BOOL IsKeyDown(int Key)
{
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}