#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "cursor.h"

#define SPACE 0
#define WALL 1
#define PLAYER1 2
#define PLAYER2 3
#define PLAYER3 4
#define PLAYER4 5
#define WATERB 6

int player1X = 1, player1Y = 1; // �÷��̾� �ʱ� ��ǥ
int waterb = 0; //��ǳ�� �ʱ� ����
struct ballon //��ǳ�� ��ǥ ����ü
{
	int x; int y; int con;
}Wballon[8] = { 0 };
int life = 1;
int map[20][20] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};
void printMap(); //�� ��� �Լ�
void printpopwater(int, int); //��ǳ�� ���� ���� �Լ�
void removewaterb(int); //��ǳ�� ���� ���� ���� �Լ�
void PlayerInput(); //�÷��̾� �Է� �Լ�
void movePlayer(int, int); //�÷��̾� �̵� �Լ�
void BmovePlayer(); //��ǳ�� ���� ���� �÷��̾� �̵� �Լ�
int PmovePlayer(int, int, int); //��ǳ�� ���� �Լ� ���� �÷��̾� �̵� �Լ�
int printWaterb(); //��ǳ�� ��� �Լ�
void popWaterb(int, int); //��ǳ�� ���� �Լ�

int main() {
	int pl = 0;
	while (1)
	{
		printf("�ο� ���� �Է����ּ��� : ");
		scanf("%d", &pl);
		if (pl < 2) {
			printf("�ּ� 2���� �Է����ּ���!\n");
		}
		else if (pl > 4) {
			printf("�ִ� 4���Դϴ�!\n\n");
		}
		else if (pl == 2) {
			map[18][1] = 0;
			map[1][18] = 0;
			break;
		}
		else if (pl == 3) {
			map[1][18] = 0;
			break;
		}
		else {
			break;
		}
	}
	system("cls");

	removeCursor();
	printMap();

	while (life != 0)
	{
 		PlayerInput();
 	}
	system("cls");
	printf("�������ϴ� ��\n");
}

void PlayerInput()
{
	int playerInput, num;

	playerInput = getch();
	if (playerInput == -32)
		playerInput = getch();
	if (playerInput == 75) //left
		movePlayer(-1, 0);
	else if (playerInput == 77) //right
		movePlayer(1, 0);
	else if (playerInput == 72) //up
		movePlayer(0, -1);
	else if (playerInput == 80) //down
		movePlayer(0, 1);
	else if (playerInput == 32) //waterballon
	{
		num = printWaterb();
		popWaterb(num, 0, 1);
	}
	else PlayerInput();
}

void movePlayer(int dx, int dy)   //�÷��̾� �̵� �Լ�
{
	if (map[player1Y + dy][player1X + dx] == SPACE) //�̵��� ������ �ƹ��͵� ������ ��
	{
		gotoxy(player1X, player1Y);
		printf("  "); //���� ��ǥ�� ���� ���
		map[player1Y][player1X] = SPACE; //���� ��ǥ ������ SPACE ����
		player1X += dx;
		player1Y += dy;
		gotoxy(player1X, player1Y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("��"); //�̵� ��ǥ�� �÷��̾� ���
		map[player1Y][player1X] = PLAYER1; //�̵� ��ǥ ������ PLAYER1 ����
	}
}

void bmove(int dx, int dy)
{
	if (map[player1Y + dy][player1X + dx] == SPACE) //�̵��� ������ �ƹ��͵� ������ ��
	{
		gotoxy(player1X, player1Y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("��"); //���� ��ǥ�� ��ǳ�� ���
		map[player1Y][player1X] = WATERB; //���� ��ǥ ������ WATERB ����
		player1X += dx;
		player1Y += dy;
		gotoxy(player1X, player1Y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("��"); //�̵� ��ǥ�� �÷��̾� ���
		map[player1Y][player1X] = PLAYER1; //�̵� ��ǥ ������ PLAYER1 ����
		waterb++;
	}
	else BmovePlayer();
}

void BmovePlayer() //��ǳ�� ���� ���� �÷��̾� �̵� �Լ�
{
	int playerInput, dx, dy;

	playerInput = getch();

	if (playerInput == 224)
		playerInput = getch();

	if (playerInput == 75) //left
	{
		dx = -1;
		dy = 0;
		bmove(dx, dy);
	}
	else if (playerInput == 77) //right
	{
		dx = 1;
		dy = 0;
		bmove(dx, dy);
	}
	else if (playerInput == 72) //up
	{
		dx = 0;
		dy = -1;
		bmove(dx, dy);
	}
	else if (playerInput == 80) //down
	{
		dx = 0;
		dy = 1;
		bmove(dx, dy);
	}

	else BmovePlayer();
}

int PmovePlayer(int num1, int num, int k) //popWaterb ���� �÷��̾� �̵� �Լ�
{
	int playerInput, dx, dy, i;
	if (life != 0){
		for (i = k; i < 150; i++)
		{
			if (_kbhit()) { //Ű���� �Է� �ø� ����
				playerInput = getch();

				if (playerInput == 224)
					playerInput = getch();
				if (playerInput == 75) //left
					movePlayer(-1, 0);
				else if (playerInput == 77) //right
					movePlayer(1, 0);
				else if (playerInput == 72) //up
					movePlayer(0, -1);
				else if (playerInput == 80) //down
					movePlayer(0, 1);
				else if (playerInput == 32) //waterballon
				{
					if (waterb < 2){
						num = printWaterb();
						popWaterb(num, num1, i);
					}
				}
				else continue;
			}
			Sleep(10); //0.01�� ���� for�� �� �� ���� : Ű���� �Է� ���� �� �������� �Ѿ
		}
		for (i = 1; i < 24; i++) {
			if (_kbhit()) { //Ű���� �Է� �ø� ����
				playerInput = getch();

				if (playerInput == 224)
					playerInput = getch();
				if (playerInput == 75) //left
					movePlayer(-1, 0);
				else if (playerInput == 77) //right
					movePlayer(1, 0);
				else if (playerInput == 72) //up
					movePlayer(0, -1);
				else if (playerInput == 80) //down
					movePlayer(0, 1);
				else continue;
			}
			if (waterb != 0 && i % 4 == 0 && Wballon[num].con == 1)
				printpopwater(i / 4, num);
			Sleep(10);
		}
		Sleep(150);
		if (waterb != 0 && Wballon[num].con == 1)
		{
			removewaterb(num);
			gotoxy(Wballon[num].x, Wballon[num].y); printf("  ");
			waterb--;
		}
		return 150 - k;
	}
}

int printWaterb() //��ǳ�� ��� �Լ�
{
	int i;
	if (waterb < 2) //���� �����Ǿ��ִ� ��ǳ�� ���� ��
	{
		for (i = 0; i <= 1; i++)
		{
			if (Wballon[i].x == 0) //����ִ� ����ü���� Ȯ��
			{
				Wballon[i].x = player1X; //i�� ��ǳ�� X��ǥ�� �÷��̾� X��ǥ ����
				Wballon[i].y = player1Y; //i�� ��ǳ�� Y��ǥ�� �÷��̾� Y��ǥ ����
				break;
			}
		}
		BmovePlayer();
		return i;
	}

}

void popWaterb(int num, int num1, int k) //��ǳ�� ���� �Լ�
{
	if (life != 0){
		if (waterb == 1) { //������ ��ǳ���� �� ���� ���
			Wballon[num].con = 1;
			num1 = num;
			PmovePlayer(num1, num, 1);
			if (waterb == 0){
				Wballon[num].x = 0;
				Wballon[num].con = 0;
			}
		}
		else if (waterb == 2)
		{
			Wballon[num].con = 1;
			k = PmovePlayer(num1, num1, k); //��ǳ���� �ΰ��̱� ������ ���� ���� ��ǳ���� ���߿� ���� ��ǳ���� ���ϱ� ���� num1 ���
			Wballon[num1].x = 0;
			Wballon[num1].con = 0;
			num1 = num;
			k = PmovePlayer(num1, num, k);
			Wballon[num1].x = 0;
			Wballon[num1].con = 0;
		}
	}
}

void printMap() //�� ��� �Լ�
{
	int i, j;

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			if (map[i][j] == SPACE)
				printf("  ");
			else if (map[i][j] == WALL)
				printf("��");
			else if (map[i][j] == PLAYER1)
				printf("��");
			else if (map[i][j] == PLAYER2)
				printf("��");
			else if (map[i][j] == PLAYER3)
				printf("��");
			else if (map[i][j] == PLAYER4)
				printf("��");
		}
		printf("\n");
	}
}

void printpopwater(int i, int num)
{
	if (map[Wballon[num].y - i][Wballon[num].x] != WALL) //��ǳ�� ���ʿ� ���� �ִ��� ��
	{
		if (Wballon[num].y - i > 0)
		{
			gotoxy(Wballon[num].x, Wballon[num].y - i);
			if (map[Wballon[num].y - i][Wballon[num].x] == PLAYER1) {
				printf("��");
				life = 0;
			}
			else if (map[Wballon[num].y - i][Wballon[num].x] == WATERB)
				printf("��");
			else printf("��");
		}
	}
	if (map[Wballon[num].y + i][Wballon[num].x] != WALL) //��ǳ�� �Ʒ��ʿ� ���� �ִ��� ��
	{
		if (Wballon[num].y + i < 20)
		{
			gotoxy(Wballon[num].x, Wballon[num].y + i);
			if (map[Wballon[num].y + i][Wballon[num].x] == PLAYER1) {
				printf("��");
				life = 0;
			}
			else if (map[Wballon[num].y + i][Wballon[num].x] == WATERB)
				printf("��");
			else printf("��");
		}
	}
	if (map[Wballon[num].y][Wballon[num].x - i] != WALL) //��ǳ�� ���ʿ� ���� �ִ��� ��
	{
		if (Wballon[num].x - i > 0)
		{
			gotoxy(Wballon[num].x - i, Wballon[num].y);
			if (map[Wballon[num].y][Wballon[num].x - i] == PLAYER1) {
				printf("��");
				life = 0;
			}
			else if (map[Wballon[num].y][Wballon[num].x - i] == WATERB)
				printf("��");
			else printf("��");
		}
	}
	if (map[Wballon[num].y][Wballon[num].x + i] != WALL) //��ǳ�� �����ʿ� ���� �ִ��� ��
	{
		if (Wballon[num].x + i < 20)
		{
			gotoxy(Wballon[num].x + i, Wballon[num].y);
			if (map[Wballon[num].y][Wballon[num].x + i] == PLAYER1) {
				printf("��");
				life = 0;
			}
			else if (map[Wballon[num].y][Wballon[num].x + i] == WATERB)
				printf("��");
			else printf("��");
		}
	}
}

void removewaterb(int num)
{
	int i;

	for (i = 0; i <= 6; i++)
	{
		if (map[Wballon[num].y - i][Wballon[num].x] != WALL) //��ǳ�� ���ʿ� ���� �ִ��� ��
		{
			if (Wballon[num].x >= 0 && Wballon[num].y - i >= 0)
			{
				gotoxy(Wballon[num].x, Wballon[num].y - i);
				if (map[Wballon[num].y - i][Wballon[num].x] == PLAYER1) {
					printf("��");
				}
				else if (map[Wballon[num].y - i][Wballon[num].x] == WATERB)
					printf("��");
				else printf(" ");
			}
		}
		if (map[Wballon[num].y + i][Wballon[num].x] != WALL) //��ǳ�� �Ʒ��ʿ� ���� �ִ��� ��
		{
			if (Wballon[num].x >= 0 && Wballon[num].y + i >= 0)
			{
				gotoxy(Wballon[num].x, Wballon[num].y + i);
				if (map[Wballon[num].y + i][Wballon[num].x] == PLAYER1) {
					printf("��");
				}
				else if (map[Wballon[num].y + i][Wballon[num].x] == WATERB)
					printf("��");
				else printf(" ");
			}
		}
		if (map[Wballon[num].y][Wballon[num].x - i] != WALL) //��ǳ�� ���ʿ� ���� �ִ��� ��
		{
			if (Wballon[num].x - i >= 0 && Wballon[num].y >= 0)
			{
				gotoxy(Wballon[num].x - i, Wballon[num].y);
				if (map[Wballon[num].y][Wballon[num].x - i] == PLAYER1) {
					printf("��");
				}
				else if (map[Wballon[num].y][Wballon[num].x - i] == WATERB)
					printf("��");
				else printf(" ");
			}
		}
		if (map[Wballon[num].y][Wballon[num].x + i] != WALL) //��ǳ�� �����ʿ� ���� �ִ��� ��
		{
			if (Wballon[num].x + i >= 0 && Wballon[num].y >= 0)
			{
				gotoxy(Wballon[num].x + i, Wballon[num].y);
				if (map[Wballon[num].y][Wballon[num].x + i] == PLAYER1) {
					printf("��");
				}
				else if (map[Wballon[num].y][Wballon[num].x + i] == WATERB)
					printf("��");
				else printf(" ");
			}
		}
	}
	map[Wballon[num].y][Wballon[num].x] = SPACE;
}