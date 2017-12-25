#define _CRT_SECURE_NO_WARNINGS
//�������
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#define STICK 15 //�������� �� �ִ� ��ֹ� ����
#define SPEED 20 // ��ֹ� �ӵ�
#define COUNT 3   // �������� �þ ��ֹ� ����

using namespace std;

//������Ÿ��
void gotoxy(int x, int y); //��
void GameWay(); //��
void GameStart();
void choiceScreen(int choice); //�� 
void GameEnd(); //��
void Result();
void Ranking(); // ��ũȭ��
void scoreCompare(); // ������
void getRank(); // ���Ͽ��� ��ũ ������ ��������
void saveRank(); //��ũ ���Ͽ� ����
void rankInput(int); //��ŷ���� ���� �Է�
void Cursor(int n);//Ŀ�� ���ڱ���
BOOL IsKeyDown(int Key); //Ű���� �Է�

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

//����
int main() {
	//âũ�����
	system("mode con cols=110 lines=35");
	Cursor(0);
	ifstream ifile;

	char line[200]; // �� �پ� �о �ӽ÷� ������ ����

	ifile.open("screen.txt");  // ���� ����

	if (ifile.is_open())
	{
		while (ifile.getline(line, sizeof(line))) // �� �پ� �о� ó���� �����Ѵ�.
		{
			cout << line << endl; // ���� ���
		}
	}

	ifile.close(); // ���� �ݱ�
	gotoxy(37, 21);
	//����ȭ�� ���
	cout << "�ƹ�Ű�� ������ �����մϴ�." << endl;
	gotoxy(98, 33);
	cout << "2502 ��ΰ�";
	_getch();
	system("cls");
	choiceScreen(0);

	return 0;
}

//�޴� ����
void choiceScreen(int choice) {
	system("cls");
	system("mode con cols=110 lines=35");
	ifstream ifile;

	char line[200]; // �� �پ� �о �ӽ÷� ������ ����

	ifile.open("menu.txt");  // ���� ����

	if (ifile.is_open())
	{
		while (ifile.getline(line, sizeof(line))) // �� �پ� �о� ó���� �����Ѵ�.
		{
			cout << line << endl; // ���� ���
		}
		cout << endl;
	}
	ifile.close(); // ���� �ݱ�
	cout << "                                  �����ϼ���>> ";
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
			cout << "�ùٸ� ���ڸ� �������ּ���!" << endl; 
			Sleep(500); 
			choiceScreen(0);
	}
}

//���� ���
void GameWay() {
	system("cls");
	system("mode con cols=110 lines=35");
	ifstream ifile;

	char line[200]; // �� �پ� �о �ӽ÷� ������ ����

	ifile.open("GameWay.txt");  // ���� ����

	if (ifile.is_open())
	{
		while (ifile.getline(line, sizeof(line))) // �� �پ� �о� ó���� �����Ѵ�.
		{
			cout << line << endl; // ���� ���
		}
		cout << endl;
	}
	ifile.close(); // ���� �ݱ�

	cout << "                                  �����ϼ���>> ";
	int choice_1 = 0;
	cin >> choice_1;
	switch (choice_1)
	{
	case 1: GameStart(); break;
	case 2: choiceScreen(0); break;
	default: cout << "�ùٸ� ���ڸ� �������ּ���!" << endl;
	}
	gotoxy(98, 33);
	cout << "2502 ��ΰ�";
}

Player player[7];
struct OBSTACLE ob[STICK], user;
int i, check = 1, evade = 0,level = 1;
int speed = 75 - level * SPEED;
// �������� �ʿ��� ��ֹ�����
int levelup = 10 + level * 10;
int gamescore = 0;
//���� ����
void GameStart() {
	system("cls");
	system("mode con cols=110 lines=35");
	//���� ǥ��
	system("color 0");
	int count = 5 + level * COUNT;
	// ��ֹ� ���� üũ
	if (count >= STICK) count = STICK - 1;
	// ���ǵ� üũ. (�ּҰ��� 10 ���� ���� �ʵ��� ����)
	if (speed < 10) speed = 10;
	// ������ġ
	user.x = 50;
	user.y = 26;
	// ��ֹ� �ʱ�ȭ
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
		// ���ǵ�
		Sleep(speed);
		system("cls");
		// ���� ȯ�� ���.
		cout << "���� : " << life << endl;
		cout<<"[Bug Escape]\tLEVEL"<<level<<"\n���� : "<< gamescore;
		gotoxy(20, 30);
		cout<<"�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�";
		cout << "�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�";
		gotoxy(98, 33);
		cout << "2502 ��ΰ�";
		// ������ ó��
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
		// ĳ���� ���
		gotoxy(user.x, user.y);
		cout << "����";
		gotoxy(user.x, user.y + 1);
		cout<<"-��-";
		gotoxy(user.x, user.y + 2);
		cout<<"����";
		// ��ֹ� ������ ó��
		system("color 0");
		for (i = 0; i<count; i++)
		{
			if (ob[i].wait > 0)
			{
				// ���ð� ���� ��ֹ� ����ϱ�
				ob[i].wait--;
			}
			else
			{
				// ��ֹ� �Ʒ��� �̵�
				ob[i].y++;
				// ��ֹ��� ���� �ؿ� ���� ���� ��
				if (ob[i].y >= 29)
				{
					ob[i].x = rand() % 50 +24;
					ob[i].y = 3;
					evade++;  // ���� ��ֹ����� ī��Ʈ
				}
				// ��ֹ� ���
				gotoxy(ob[i].x, ob[i].y);
				printf("----------------------------");

				// �浹 üũ
				if (ob[i].x - user.x < 10 && ob[i].y == user.y)
				{
					check = 0;
					--life;
				}
				
			}
		}
		// ���� ��ֹ��� ������ 15���� ������
		/*if (evade > levelup) {
			system("cls");
			gotoxy(45,15);
			cout << "STAGE 2" << endl;
			//Sleep(500);
				scoreCompare();
				break;
		}*/
		if (life == 1) { //������ 1�̸� ���������� �ٲ�
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
	cout << "  ���� �ܰ� : 1" << endl;
	gotoxy(45, 12);
	cout << "  ���� : " << gamescore <<endl;
	gotoxy(45, 13);
	cout << "------------------" << endl;
	gotoxy(98, 33);
	cout << "2502 ��ΰ�";
	Sleep(500);
	scoreCompare();
}

void Ranking() {
	getRank();
	system("cls");
	system("mode con cols=110 lines=35");
	system("Color 0");
	gotoxy(31, 7);
	cout << "  ����������������������������������";
	gotoxy(31, 9);
	cout << "                ����                  ";
	gotoxy(31, 11);
	cout << "  ����������������������������������";
	for (int i = 0; i < 5; i++) {
		gotoxy(38, 13 + i * 2);
		printf("%4d %10s %5d\n", player[i].rank, player[i].name, player[i].score);
	}
	gotoxy(88, 29);
	cout << "2502 ��ΰ�";

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
			cout << "�� ŷ �� �� �� ��";
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
	cout << "���������� "<<gamescore << "���Դϴ�\n";
	gotoxy(30, 15);
	cout<<"�̸��� �Է����ּ��� >> ";
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

	char line[200]; // �� �پ� �о �ӽ÷� ������ ����

	ifile.open("End.txt");  // ���� ����

	if (ifile.is_open())
	{
		while (ifile.getline(line, sizeof(line))) // �� �پ� �о� ó���� �����Ѵ�.
		{
			cout << line << endl; // ���� ���
		}
		cout << endl;
	}
	ifile.close(); // ���� �ݱ�
	gotoxy(45, 21);
	cout << "����Ǿ����ϴ�~!!!" << endl;
	gotoxy(98, 33);
	cout << "2502 ��ΰ�";
}

//��ǥ����
void gotoxy(int x, int y)
{
	COORD pos = { (short)x,(short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//Ŀ�� ���ڱ���
void Cursor(int n) {
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = n;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

//Ű���� �Է�
BOOL IsKeyDown(int Key)
{
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}