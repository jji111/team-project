#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include "cursor.h"
#include "start.h"
#include "player1or2.h"

void movePlayer1(int dx, int dy, int n)   //�÷��̾� �̵� �Լ�
{
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
			waterb++;
		}
	}
}

void movePlayer2(int dx, int dy, int n)   //�÷��̾� �̵� �Լ�
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

int printWaterb1() //��ǳ�� ��� �Լ�
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
		return i;
	}
}

int printWaterb2() //��ǳ�� ��� �Լ�
{
	int i;
	if (waterb < 2) //���� �����Ǿ��ִ� ��ǳ�� ���� ��
	{
		for (i = 2; i <= 3; i++)
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