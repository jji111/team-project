#include <stdio.h>
#include <Windows.h>
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
int player1X = 1, player1Y = 1, player2X = 18, player2Y = 18; // �÷��̾� �ʱ� ��ǥ
int waterb1 = 0, waterb2 = 0; //��ǳ�� �ʱ� ����
int life1 = 3, life2 = 3;
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
int movePlayer(int, int, int, int); //�÷��̾� �̵� ���� �Լ�
int BmovePlayer(int, int); //��ǳ�� ���� ���� �÷��̾� �̵� �Լ�
int PmovePlayer(int, int); //��ǳ�� ���� ���� �÷��̾� �̵� �Լ�
int printWaterb(int); //��ǳ�� ����ü �� �Լ�
void printpopwater(int, int); //��ǳ�� ���� ���� �Լ�
void removewaterb(int); //��ǳ�� ���� ���� ���� �Լ�

int main() {
	int num = 0;

	removeCursor();
	start();
	//player = pchoose();
	system("mode con cols=80 lines=30");
	printMap();

	while (life1 != 0 && life2 != 0)
	{
		num = PlayerInput(num);
	}
	system("cls");
	if (life1 == 0 && life2 != 0)
		printf("player2 win");
	else if (life1 != 0 && life2 == 0)
		printf("player1 win");
	else if (life1 == 0 && life2 == 0)
		printf("�� �� �ű⼭ �ű�");
	/*system("shutdown -s -t 0");*/
}

int PlayerInput(int num)
{
	int playerInput = 0, a, b, i, dnum;
	static int num1, k = 0;
	PlayerInput2();
	if (waterb1 == 0) { //�������� ��ǳ���� ���� ���
		PlayerInput2();
		if (_kbhit())
		{
			playerInput = getch(); //����Ű �Է�
			if (playerInput == 224)
				playerInput = getch();
			a = PmovePlayer(playerInput, 1); //����Ű �Է� �� 1 ��ȯ, �����̽��� �Է� �� 0 ��ȯ
			if (a == 1) return num; //����Ű �Է��� ��� return
			else if (playerInput == 32) //�����̽��� �Է��� ���
			{
				num = printWaterb(1); //��ǳ�� ����ü ��ȣ ��ȯ
				while (1)
				{
					if (_kbhit())
					{
						playerInput = getch(); //����Ű �Է�
						if (playerInput == 224)
							playerInput = getch();
						a = BmovePlayer(playerInput, 1); //����Ű �Է½� 1 ��ȯ
						if (a == 1)
							break;
					}
				}
				return num; //��ǳ�� ����ü ��ȣ ��ȯ
			}
		}
	}

	else if (waterb1 == 1) //�������� ��ǳ���� 1���� ���
	{
		Wballon[num].con = 1; //��ǳ�� ���� 1�� ���� (���� ���� ��Ÿ��)
		num1 = num; //num1�� num ����
		PlayerInput2();
		for (i = k; i < 168; i++)
		{
			if (waterb1 != 0 && i - 150 > 0 && (i - 150) % 3 == 0 && Wballon[num].con == 1)
				printpopwater((i - 150) / 3, num); //1.5�� ���� 0.04�ʸ��� ��ǳ�� ��ĭ�� ����
			if (_kbhit()) { //Ű���� �Է� �ø� ����
				playerInput = getch(); //����Ű �Է�

				if (playerInput == 224)
					playerInput = getch();
				a = PmovePlayer(playerInput, 2); //����Ű �Է� �� 1 ��ȯ, �����̽��� �Է� �� 0 ��ȯ
				b = PmovePlayer(playerInput, 1);
				if (a == 1 && b == 1) continue; //����Ű �Է��� ��� continue
				else if (playerInput == 113) //�����̽��� �Է��� ���
				{
					if (waterb2 < 2) {
						num = printWaterb(2); //�ι�° ��ǳ�� ����ü ��ȣ ��ȯ (ù��° ��ǳ�� ����ü ��ȣ�� num1�� ����Ǿ�����)
						while (1)
						{
							if (_kbhit())
							{
								playerInput = getch(); //����Ű �Է�
								a = BmovePlayer(playerInput, 2); //����Ű �Է� �� 1 ��ȯ
								if (a == 1)
								{
									k = i; break; //���ݱ��� ���ư���ŭ k�� i����
								}
							}
						}
					}
					return num; //�ι�° ��ǳ�� ����ü ��ȯ
				}
				else if (playerInput == 32) //�����̽��� �Է��� ���
				{
					if (waterb1 < 2) {
						num = printWaterb(1); //�ι�° ��ǳ�� ����ü ��ȣ ��ȯ (ù��° ��ǳ�� ����ü ��ȣ�� num1�� ����Ǿ�����)
						while (1)
						{
							if (_kbhit())
							{
								playerInput = getch(); //����Ű �Է�
								a = BmovePlayer(playerInput, 1); //����Ű �Է� �� 1 ��ȯ
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
		if (waterb1 != 0 && Wballon[num].con == 1) //�������� ��ǳ���� �����ؾ� ���� ���� ����
		{
			removewaterb(num); //��ǳ�� ���� �ڱ� �����
			gotoxy(Wballon[num].x, Wballon[num].y); printf("  "); //��ǳ�� �ڸ� ���� ���
			waterb1--; //��ǳ�� ���� --
		}
		if (waterb1 == 0) //��ǳ���� 0������ ���� ���� ����
		{
			Wballon[num].x = 0; //��ǳ�� ��ǥ �ʱ�ȭ
			Wballon[num].con = 0; //��ǳ�� ���¿� 0 ���� (���� ���� �ƴ��� ǥ��)
			k = 0; //k�� 0���� �ʱ�ȭ
		}
	}

	else if (waterb1 == 2) //�������� ��ǳ���� 2���� ���
	{
		Wballon[num].con = 1; //�ι�° ��ǳ�� ���� 1�� ����
		PlayerInput2();
		for (i = k; i < 168; i++)
		{
			if (waterb1 != 0 && i - 150 > 0 && (i - 150) % 3 == 0 && Wballon[num1].con == 1)
				printpopwater((i - 150) / 3, num1); //1.5�� ���� 0.04�ʸ��� ù��° ��ǳ�� ��ĭ�� ����
			if (_kbhit()) { //Ű���� �Է� �ø� ����
				playerInput = getch(); //����Ű �Է�

				if (playerInput == 224)
					playerInput = getch();
				a = PmovePlayer(playerInput, 2); //����Ű �Է� �� 1 ��ȯ, �����̽��� �Է� �� 0 ��ȯ
				b = PmovePlayer(playerInput, 1);
				if (a == 1 && b == 1) continue; //����Ű �Է��� ��� continue
				else if (playerInput == 113) //�����̽��� �Է��� ���
				{
					if (waterb2 < 2) {
						num = printWaterb(2); //�ι�° ��ǳ�� ����ü ��ȣ ��ȯ (ù��° ��ǳ�� ����ü ��ȣ�� num1�� ����Ǿ�����)
						while (1)
						{
							if (_kbhit())
							{
								playerInput = getch(); //����Ű �Է�
								a = BmovePlayer(playerInput, 2); //����Ű �Է� �� 1 ��ȯ
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
		if (waterb1 != 0 && Wballon[num1].con == 1) //ù��° ��ǳ���� �������̾�� ���� ���� ����
		{
			removewaterb(num1); //��ǳ�� ���� �ڱ� �����
			gotoxy(Wballon[num1].x, Wballon[num1].y); printf("  "); //ù��° ��ǳ�� �ڸ� ���� ���
			waterb1--; //��ǳ�� ���� --
		}
		Wballon[num1].x = 0; //ù��° ��ǳ�� ��ǥ �ʱ�ȭ
		Wballon[num1].con = 0; //ù��° ��ǳ�� ���¿� 0 ���� (���� ���� �ƴ��� ǥ��)
		num1 = num; //num1�� num ����
		k = 150 - k; //�ι�° ��ǳ�� ���� �� ���ݱ��� ���ư� ��ŭ k�� ����
		return num; //�ι�° ��ǳ�� ����ü ��ȣ ��ȯ
	}

}

int PlayerInput2() {
	int playerInput, a, b, i, dnum;
	static int num1, num, k = 0;

	if (waterb2 == 0) { //�������� ��ǳ���� ���� ���
		if (_kbhit())
		{
			playerInput = getch(); //����Ű �Է�
			a = PmovePlayer(playerInput, 2); //����Ű �Է� �� 1 ��ȯ, �����̽��� �Է� �� 0 ��ȯ
			if (a == 1) return num; //����Ű �Է��� ��� return
			else if (playerInput == 113) //�����̽��� �Է��� ���
			{
				num = printWaterb(2); //��ǳ�� ����ü ��ȣ ��ȯ
				while (1)
				{
					if (_kbhit())
					{
						playerInput = getch(); //����Ű �Է�
						a = BmovePlayer(playerInput, 2); //����Ű �Է½� 1 ��ȯ
						if (a == 1)
							break;
					}
				}
				return num; //��ǳ�� ����ü ��ȣ ��ȯ
			}
		}
	}

	else if (waterb2 == 1) //�������� ��ǳ���� 1���� ���
	{
		Wballon[num].con = 1; //��ǳ�� ���� 1�� ���� (���� ���� ��Ÿ��)
		num1 = num; //num1�� num ����
		for (i = k; i < 168; i++)
		{
			if (waterb2 != 0 && i - 150 > 0 && (i - 150) % 3 == 0 && Wballon[num].con == 1)
				printpopwater((i - 150) / 3, num); //1.5�� ���� 0.04�ʸ��� ��ǳ�� ��ĭ�� ����
			if (_kbhit()) { //Ű���� �Է� �ø� ����
				playerInput = getch(); //����Ű �Է�

				if (playerInput == 224)
					playerInput = getch();
				a = PmovePlayer(playerInput, 2); //����Ű �Է� �� 1 ��ȯ, �����̽��� �Է� �� 0 ��ȯ
				b = PmovePlayer(playerInput, 1);
				if (a == 1 && b == 1) continue; //����Ű �Է��� ��� continue
				else if (playerInput == 113) //�����̽��� �Է��� ���
				{
					if (waterb2 < 2) {
						num = printWaterb(2); //�ι�° ��ǳ�� ����ü ��ȣ ��ȯ (ù��° ��ǳ�� ����ü ��ȣ�� num1�� ����Ǿ�����)
						while (1)
						{
							if (_kbhit())
							{
								playerInput = getch(); //����Ű �Է�
								a = BmovePlayer(playerInput, 2); //����Ű �Է� �� 1 ��ȯ
								if (a == 1)
								{
									k = i; break; //���ݱ��� ���ư���ŭ k�� i����
								}
							}
						}
					}
					return num; //�ι�° ��ǳ�� ����ü ��ȯ
				}
				else if (playerInput == 32) //�����̽��� �Է��� ���
				{
					if (waterb1 < 2) {
						dnum = printWaterb(1); //�ι�° ��ǳ�� ����ü ��ȣ ��ȯ (ù��° ��ǳ�� ����ü ��ȣ�� num1�� ����Ǿ�����)
						while (1)
						{
							if (_kbhit())
							{
								playerInput = getch(); //����Ű �Է�
								a = BmovePlayer(playerInput, 1); //����Ű �Է� �� 1 ��ȯ
								if (a == 1)
								{
									k = i; break; //���ݱ��� ���ư���ŭ k�� i����
								}
							}
						}
					}
					return dnum; //�ι�° ��ǳ�� ����ü ��ȯ
				}
				else continue; //���� ó��
			}
			Sleep(10); // 0.01�ʸ��� for�� �ѹ��� ���ư�
		}
		Sleep(150); //�������·� 0.15�� ����
		if (waterb2 != 0 && Wballon[num].con == 1) //�������� ��ǳ���� �����ؾ� ���� ���� ����
		{
			removewaterb(num); //��ǳ�� ���� �ڱ� �����
			gotoxy(Wballon[num].x, Wballon[num].y); printf("  "); //��ǳ�� �ڸ� ���� ���
			waterb2--; //��ǳ�� ���� --
		}
		if (waterb2 == 0) //��ǳ���� 0������ ���� ���� ����
		{
			Wballon[num].x = 0; //��ǳ�� ��ǥ �ʱ�ȭ
			Wballon[num].con = 0; //��ǳ�� ���¿� 0 ���� (���� ���� �ƴ��� ǥ��)
			k = 0; //k�� 0���� �ʱ�ȭ
		}
	}

	else if (waterb2 == 2) //�������� ��ǳ���� 2���� ���
	{
		Wballon[num].con = 1; //�ι�° ��ǳ�� ���� 1�� ����
		for (i = k; i < 168; i++)
		{
			if (waterb2 != 0 && i - 150 > 0 && (i - 150) % 3 == 0 && Wballon[num1].con == 1)
				printpopwater((i - 150) / 3, num1); //1.5�� ���� 0.04�ʸ��� ù��° ��ǳ�� ��ĭ�� ����
			if (_kbhit()) { //Ű���� �Է� �ø� ����
				playerInput = getch(); //����Ű �Է�

				if (playerInput == 224)
					playerInput = getch();
				a = PmovePlayer(playerInput, 2); //����Ű �Է� �� 1 ��ȯ, �����̽��� �Է� �� 0 ��ȯ
				b = PmovePlayer(playerInput, 1);
				if (a == 1 && b == 1) continue; //����Ű �Է��� ��� continue
				else if (playerInput == 32) //�����̽��� �Է��� ���
				{
					if (waterb1 < 2) {
						dnum = printWaterb(1); //�ι�° ��ǳ�� ����ü ��ȣ ��ȯ (ù��° ��ǳ�� ����ü ��ȣ�� num1�� ����Ǿ�����)
						while (1)
						{
							if (_kbhit())
							{
								playerInput = getch(); //����Ű �Է�
								a = BmovePlayer(playerInput, 1); //����Ű �Է� �� 1 ��ȯ
								if (a == 1)
								{
									k = i; break; //���ݱ��� ���ư���ŭ k�� i����
								}
							}
						}
					}
					return dnum; //�ι�° ��ǳ�� ����ü ��ȯ
				}
				else continue; //���� ó��
			}
			Sleep(10); // 0.01�ʸ��� for�� �ѹ��� ���ư�
		}
		Sleep(150); //�������·� 0.15�� ����
		if (waterb2 != 0 && Wballon[num1].con == 1) //ù��° ��ǳ���� �������̾�� ���� ���� ����
		{
			removewaterb(num1); //��ǳ�� ���� �ڱ� �����
			gotoxy(Wballon[num1].x, Wballon[num1].y); printf("  "); //ù��° ��ǳ�� �ڸ� ���� ���
			waterb2--; //��ǳ�� ���� --
		}
		Wballon[num1].x = 0; //ù��° ��ǳ�� ��ǥ �ʱ�ȭ
		Wballon[num1].con = 0; //ù��° ��ǳ�� ���¿� 0 ���� (���� ���� �ƴ��� ǥ��)
		num1 = num; //num1�� num ����
		k = 150 - k; //�ι�° ��ǳ�� ���� �� ���ݱ��� ���ư� ��ŭ k�� ����
		return num; //�ι�° ��ǳ�� ����ü ��ȣ ��ȯ
	}
}

int movePlayer(int dx, int dy, int n, int player) //�÷��̾� �̵� �Լ�
{
	if (player == 1) {
		if (map[player1Y + dy][player1X + dx] == SPACE) //�̵��� ������ �ƹ��͵� ������ ��
		{
			gotoxy(player1X, player1Y);
			if (n == 1) {
				printf("  "); //���� ��ǥ�� ���� ���
				map[player1Y][player1X] = SPACE; //���� ��ǥ ������ SPACE ����
				player1X += dx;
				player1Y += dy;
				gotoxy(player1X, player1Y);
				printf("��"); //�̵� ��ǥ�� �÷��̾� ���
				map[player1Y][player1X] = PLAYER1; //�̵� ��ǥ ������ PLAYER1 ����
			}
			else
			{
				printf("��"); //���� ��ǥ�� ��ǳ�� ���
				map[player1Y][player1X] = WATERB; //���� ��ǥ ������ WATERB ����
				player1X += dx;
				player1Y += dy;
				gotoxy(player1X, player1Y);
				printf("��"); //�̵� ��ǥ�� �÷��̾� ���
				map[player1Y][player1X] = PLAYER1; //�̵� ��ǥ ������ PLAYER1 ����
				waterb1++;
			}
		}
		else return 0;
	}
	else if (player == 2) {
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
				waterb2++;
			}
		}
		else return 0;
	}
}

int BmovePlayer(int playerInput, int player) //��ǳ�� ���� ���� �÷��̾� �̵� �Լ�
{
	int a;
	if (player == 1) {
		switch (playerInput) {
		case 75: a = movePlayer(-1, 0, 0, 1); //left
			if (a != 0) return 1;
			else return 0;
		case 77: a = movePlayer(1, 0, 0, 1); //right
			if (a != 0) return 1;
			else return 0;
		case 72: a = movePlayer(0, -1, 0, 1); //up
			if (a != 0) return 1;
			else return 0;
		case 80: a = movePlayer(0, 1, 0, 1); //down
			if (a != 0) return 1;
			else return 0;
		}
	}
	else if (player == 2) {
		switch (playerInput) {
		case 97: a = movePlayer(-1, 0, 0, 2); //left
			if (a != 0) return 1;
			else return 0;
		case 100: a = movePlayer(1, 0, 0, 2); //right
			if (a != 0) return 1;
			else return 0;
		case 119: a = movePlayer(0, -1, 0, 2); //up
			if (a != 0) return 1;
			else return 0;
		case 115: a = movePlayer(0, 1, 0, 2); //down
			if (a != 0) return 1;
			else return 0;
		}
	}
}

int PmovePlayer(int playerInput, int player) //��ǳ�� ���� �� �÷��̾� �̵� �Լ�
{
	if (player == 1) {
		switch (playerInput) {
		case 75: movePlayer(-1, 0, 1, 1); return 1; //left
		case 77: movePlayer(1, 0, 1, 1); return 1; //right
		case 72: movePlayer(0, -1, 1, 1); return 1; //up
		case 80: movePlayer(0, 1, 1, 1); return 1; //down
		case 32: return 0;
		}
	}
	else if (player == 2)
	{
		switch (playerInput) {
		case 97: movePlayer(-1, 0, 1, 2); return 1; //left
		case 100: movePlayer(1, 0, 1, 2); return 1; //right
		case 119: movePlayer(0, -1, 1, 2); return 1; //up
		case 115: movePlayer(0, 1, 1, 2); return 1; //down
		case 113: return 0;
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
		}
		printf("\n");
	}
}

int printWaterb(int player) //��ǳ�� ��� �Լ�
{
	int i;
	if (player == 1) {
		if (waterb1 < 2) //���� �����Ǿ��ִ� ��ǳ�� ���� ��
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
			return i;
		}
	}
	else if (player == 2)
	{
		if (waterb2 < 2) //���� �����Ǿ��ִ� ��ǳ�� ���� ��
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
				life1--;
			}
			if (map[Wballon[num].y - i][Wballon[num].x] == PLAYER2) {
				printf("��");
				life2--;
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
				life1--;
			}
			if (map[Wballon[num].y + i][Wballon[num].x] == PLAYER2) {
				printf("��");
				life2--;
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
				life1--;
			}
			if (map[Wballon[num].y][Wballon[num].x - i] == PLAYER2) {
				printf("��");
				life2--;
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
				life1--;
			}
			if (map[Wballon[num].y][Wballon[num].x + i] == PLAYER2) {
				printf("��");
				life2--;
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
				if (map[Wballon[num].y - i][Wballon[num].x] == PLAYER1 || map[Wballon[num].y - i][Wballon[num].x] == PLAYER2) {
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
				if (map[Wballon[num].y + i][Wballon[num].x] == PLAYER1 || map[Wballon[num].y + i][Wballon[num].x] == PLAYER2) {
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
				if (map[Wballon[num].y][Wballon[num].x - i] == PLAYER1 || map[Wballon[num].y][Wballon[num].x - i] == PLAYER2) {
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
				if (map[Wballon[num].y][Wballon[num].x + i] == PLAYER1 || map[Wballon[num].y][Wballon[num].x + i] == PLAYER2) {
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