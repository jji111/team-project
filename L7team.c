#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include "cursor.h"
#include "start.h"

#define SPACE 0
#define WALL 1
#define PLAYER1 2
#define PLAYER2 3
#define WATERB 4

struct ballon //��ǳ�� ��ǥ ����ü
{
	int x; int y; int con;
}Wballon[4] = { 0 };
int player2X = 18, player2Y = 18; // �÷��̾� �ʱ� ��ǥ
int waterb = 0; //��ǳ�� �ʱ� ����
int life = 3;
int map[20][20] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
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
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

void printMap(); //�� ��� �Լ�
int PlayerInput(int); //�÷��̾� �Է� �Լ�
void movePlayer(int, int, int); //�÷��̾� �̵� ���� �Լ�
int BmovePlayer(int); //��ǳ�� ���� ���� �÷��̾� �̵� �Լ�
int PmovePlayer(int); //��ǳ�� ���� ���� �÷��̾� �̵� �Լ�
int printWaterb(); //��ǳ�� ����ü �� �Լ�
void printpopwater(int, int); //��ǳ�� ���� ���� �Լ�
void removewaterb(int); //��ǳ�� ���� ���� ���� �Լ�

int main() {
	int num = 0, player;

	removeCursor();
	start();
	player = pchoose();
	system("mode con cols=80 lines=30");
	printMap();

	while (life != 0)
	{
		num = PlayerInput(num);
	}
	system("cls");
	printf("�������ϴ� ��\n");
	/*system("shutdown -s -t 0");*/
}

void sleep()
{
	Sleep(10);
}

int PlayerInput(int num)
{
	int playerInput, a, i;
	static int num1, k = 0;

	if (waterb == 0) { //�������� ��ǳ���� ���� ���
		while (1)
		{
			if (_kbhit())
			{
				playerInput = getch(); //����Ű �Է�
				if (playerInput == 224)
					playerInput = getch();
				a = PmovePlayer(playerInput); //����Ű �Է� �� 1 ��ȯ, �����̽��� �Է� �� 0 ��ȯ
				if (a == 1) return num; //����Ű �Է��� ��� return
				else if (a == 0) //�����̽��� �Է��� ���
				{
					num = printWaterb(); //��ǳ�� ����ü ��ȣ ��ȯ
					while (1)
					{
						if (_kbhit())
						{
							playerInput = getch(); //����Ű �Է�
							if (playerInput == 224)
								playerInput = getch();
							a = BmovePlayer(playerInput); //����Ű �Է½� 1 ��ȯ
							if (a == 1)
								break;
						}
					}
					return num; //��ǳ�� ����ü ��ȣ ��ȯ
				}
			}
		}
	}

	else if (waterb == 1) //�������� ��ǳ���� 1���� ���
	{
		Wballon[num].con = 1; //��ǳ�� ���� 1�� ���� (���� ���� ��Ÿ��)
		num1 = num; //num1�� num ����
		for (i = k; i < 174; i++)
		{
			if (waterb != 0 && i - 150 > 0 && (i - 150) % 4 == 0 && Wballon[num].con == 1)
				printpopwater((i-150) / 4, num); //1.5�� ���� 0.04�ʸ��� ��ǳ�� ��ĭ�� ����
 			if (_kbhit()) { //Ű���� �Է� �ø� ����
				playerInput = getch(); //����Ű �Է�

				if (playerInput == 224)
					playerInput = getch();
				a = PmovePlayer(playerInput); //����Ű �Է� �� 1 ��ȯ, �����̽��� �Է� �� 0 ��ȯ
				if (a == 1) continue; //����Ű �Է��� ��� continue
				else if (a == 0) //�����̽��� �Է��� ���
				{
					if (waterb < 2) {
						num = printWaterb(); //�ι�° ��ǳ�� ����ü ��ȣ ��ȯ (ù��° ��ǳ�� ����ü ��ȣ�� num1�� ����Ǿ�����)
						while (1)
						{
							if (_kbhit())
							{
								playerInput = getch(); //����Ű �Է�
								if (playerInput == 224)
									playerInput = getch();
								a = BmovePlayer(playerInput); //����Ű �Է� �� 1 ��ȯ
								if (a == 1)
								{
									k = i; break; //���ݱ��� ���ư���ŭ k�� i����
								}
							}
						}
					}
					return num; //�ι�° ��ǳ�� ����ü ��ȯ
				}
				else continue; //���� ó��
			}
			Sleep(10); // 0.01�ʸ��� for�� �ѹ��� ���ư�
		}
		Sleep(150); //�������·� 0.15�� ����
		if (waterb != 0 && Wballon[num].con == 1) //�������� ��ǳ���� �����ؾ� ���� ���� ����
		{
			removewaterb(num); //��ǳ�� ���� �ڱ� �����
			gotoxy(Wballon[num].x, Wballon[num].y); printf("  "); //��ǳ�� �ڸ� ���� ���
			waterb--; //��ǳ�� ���� --
		}
		if (waterb == 0) //��ǳ���� 0������ ���� ���� ����
		{
			Wballon[num].x = 0; //��ǳ�� ��ǥ �ʱ�ȭ
			Wballon[num].con = 0; //��ǳ�� ���¿� 0 ���� (���� ���� �ƴ��� ǥ��)
			k = 0; //k�� 0���� �ʱ�ȭ
		}
	}

	else if (waterb == 2) //�������� ��ǳ���� 2���� ���
	{
		Wballon[num].con = 1; //�ι�° ��ǳ�� ���� 1�� ����
		for (i = k; i < 174; i++)
		{
			if (waterb != 0 && i - 150 > 0 && (i - 150) % 4 == 0 && Wballon[num1].con == 1)
				printpopwater((i -150) / 4, num1); //1.5�� ���� 0.04�ʸ��� ù��° ��ǳ�� ��ĭ�� ����
			if (_kbhit()) { //Ű���� �Է� �ø� ����
				playerInput = getch(); //����Ű �Է�

				if (playerInput == 224)
					playerInput = getch();
				a = PmovePlayer(playerInput); //����Ű �Է� �� 1 ��ȯ
				if (a == 1) continue; //����Ű �Է��� ��� continue
				else continue; //���� ó��
			}
			Sleep(10); // 0.01�ʸ��� for�� �ѹ��� ���ư�
		}
		Sleep(150); //�������·� 0.15�� ����
		if (waterb != 0 && Wballon[num1].con == 1) //ù��° ��ǳ���� �������̾�� ���� ���� ����
		{
			removewaterb(num1); //��ǳ�� ���� �ڱ� �����
			gotoxy(Wballon[num1].x, Wballon[num1].y); printf("  "); //ù��° ��ǳ�� �ڸ� ���� ���
			waterb--; //��ǳ�� ���� --
		}
		Wballon[num1].x = 0; //ù��° ��ǳ�� ��ǥ �ʱ�ȭ
		Wballon[num1].con = 0; //ù��° ��ǳ�� ���¿� 0 ���� (���� ���� �ƴ��� ǥ��)
		num1 = num; //num1�� num ����
		k = 150 - k; //�ι�° ��ǳ�� ���� �� ���ݱ��� ���ư� ��ŭ k�� ����
		return num; //�ι�° ��ǳ�� ����ü ��ȣ ��ȯ
	}
}

void movePlayer(int dx, int dy, int n)   //�÷��̾� �̵� �Լ�
{
	if (map[player2Y + dy][player2X + dx] == SPACE) //�̵��� ������ �ƹ��͵� ������ ��
	{
		gotoxy(player2X, player2Y);
		if (n == 1) {
			printf("  "); //���� ��ǥ�� ���� ���
			map[player2Y][player2X] = SPACE; //���� ��ǥ ������ SPACE ����
			player2X += dx;
			player2Y += dy;
			gotoxy(player2X, player2Y);
			printf("��"); //�̵� ��ǥ�� �÷��̾� ���
			map[player2Y][player2X] = PLAYER2; //�̵� ��ǥ ������ PLAYER1 ����
		}
		else
		{
			printf("��"); //���� ��ǥ�� ��ǳ�� ���
			map[player2Y][player2X] = WATERB; //���� ��ǥ ������ WATERB ����
			player2X += dx;
			player2Y += dy;
			gotoxy(player2X, player2Y);
			printf("��"); //�̵� ��ǥ�� �÷��̾� ���
			map[player2Y][player2X] = PLAYER2; //�̵� ��ǥ ������ PLAYER1 ����
			waterb++;
		}
	}
}

int BmovePlayer(int playerInput) //��ǳ�� ���� ���� �÷��̾� �̵� �Լ�
{
	switch (playerInput) {
	case 75: movePlayer(-1, 0, 0); return 1; //left
	case 77: movePlayer(1, 0, 0); return 1; //right
	case 72: movePlayer(0, -1, 0); return 1; //up
	case 80: movePlayer(0, 1, 0); return 1; //down
	}
}

int PmovePlayer(int playerInput) //��ǳ�� ���� �� �÷��̾� �̵� �Լ�
{
	switch (playerInput) {
	case 75: movePlayer(-1, 0, 1); return 1; //left
	case 77: movePlayer(1, 0, 1); return 1; //right
	case 72: movePlayer(0, -1, 1); return 1; //up
	case 80: movePlayer(0, 1, 1); return 1; //down
	case 32: return 0;
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
		}
		printf("\n");
	}
}

int printWaterb() //��ǳ�� ��� �Լ�
{
	int i;
	if (waterb < 2) //���� �����Ǿ��ִ� ��ǳ�� ���� ��
	{
		for (i = 2; i <= 3; i++)
		{
			if (Wballon[i].x == 0) //����ִ� ����ü���� Ȯ��
			{
				Wballon[i].x = player2X; //i�� ��ǳ�� X��ǥ�� �÷��̾� X��ǥ ����
				Wballon[i].y = player2Y; //i�� ��ǳ�� Y��ǥ�� �÷��̾� Y��ǥ ����
				break;
			}
		}
		return i;
	}
}

void printpopwater(int i, int num)
{
	if (map[Wballon[num].y - i][Wballon[num].x] != WALL) //��ǳ�� ���ʿ� ���� �ִ��� ��
	{
		if (Wballon[num].y - i > 0)
		{
			gotoxy(Wballon[num].x, Wballon[num].y - i);
			if (map[Wballon[num].y - i][Wballon[num].x] == PLAYER2) {
				printf("��");
				life--;
				/*system("cls");
				printf("�������ϴ� ��\n");
				system("shutdown -s -t 0");
				system("pause");*/

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
			if (map[Wballon[num].y + i][Wballon[num].x] == PLAYER2) {
				printf("��");
				life--;
				/*system("cls");
				printf("�������ϴ� ��\n");
				system("pause");*/
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
			if (map[Wballon[num].y][Wballon[num].x - i] == PLAYER2) {
				printf("��");
				life--;
				/*system("cls");
				printf("�������ϴ� ��\n");
				system("shutdown -s -t 0");
				system("pause");*/
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
			if (map[Wballon[num].y][Wballon[num].x + i] == PLAYER2) {
				printf("��");
				life--;
				/*system("cls");
				printf("�������ϴ� ��\n");
				system("shutdown -s -t 0");
				system("pause");*/
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
				if (map[Wballon[num].y - i][Wballon[num].x] == PLAYER2) {
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
				if (map[Wballon[num].y + i][Wballon[num].x] == PLAYER2) {
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
				if (map[Wballon[num].y][Wballon[num].x - i] == PLAYER2) {
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
				if (map[Wballon[num].y][Wballon[num].x + i] == PLAYER2) {
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