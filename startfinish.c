#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "cursor.h"
#include "start.h"

void start() {
	char start;
	system("mode con cols=100 lines=51");
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if (i == 0 || i == 49 || j == 0 || j == 49)
				printf("��");
			else
				printf("  ");
		}
		printf("\n");
	}
	sa();
	tc(15);
	gotoxy(21, 38);
	printf("1.���ӽ���");
	gotoxy(21, 40);
	printf("2.���Ӽ���");

	while (1)
	{
		if (_kbhit())
		{
			start = getch(); //����Ű �Է�
			if (start == '1')
			{
				system("cls"); return;
			}
			else if (start == '2')
			{
				system("cls");
				start = ex();
				if (start == 0)
					return;
			}
		}
	}
}

void tc(int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

void sa() {
	tc(3);
	gotoxy(18, 6);
	printf("����������������");
	gotoxy(18, 7);
	printf("����������������");
	tc(6);
	gotoxy(24, 8);
	printf("����");
	tc(3);
	gotoxy(23, 9);
	printf("������");
	gotoxy(20, 10);
	printf("������������");
	gotoxy(18, 11);
	printf("����������������");
	gotoxy(17, 12);
	printf("������������������");
	gotoxy(16, 13);
	printf("���������������������");
	gotoxy(15, 14);
	printf("����������������������");
	gotoxy(14, 15);
	printf("������������������������");
	gotoxy(14, 16);
	printf("������������������������");
	gotoxy(13, 17);
	printf("��������������������������");
	gotoxy(13, 18);
	printf("��������������������������");
	gotoxy(13, 19);
	printf("��������������������������");
	gotoxy(13, 20);
	printf("��������������������������");
	gotoxy(13, 21);
	printf("��������������������������");
	gotoxy(13, 22);
	printf("��������������������������");
	gotoxy(14, 23);
	printf("������������������������");
	gotoxy(15, 24);
	printf("����������������������");
	tc(15);
	gotoxy(17, 24);
	printf("���");
	tc(3);
	gotoxy(16, 25);
	printf("��������������������");
	tc(15);
	gotoxy(18, 25);
	printf("���");
	tc(3);
	gotoxy(17, 26);
	printf("������������������");
	tc(15);
	gotoxy(19, 26);
	printf("���");
	tc(3);
	gotoxy(18, 27);
	printf("����������������");
	gotoxy(20, 28);
	printf("������������");
}

int ex()
{
	char start;

	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if (i == 0 || i == 49 || j == 0 || j == 49)
				printf("��");
			else
				printf("  ");
		}
		printf("\n");
	}
	sa();

	tc(15);
	gotoxy(17, 33);
	printf("�� �÷��̾�1 :����Ű �Է� �� �÷��̾� �̵�");
	gotoxy(17, 34);
	printf("�� �����̽� �� �Է� �� ��ǳ�� ����");
	gotoxy(17, 35);
	printf("�� �÷��̾�2 :AWSD �Է� �� �÷��̾� �̵�");
	gotoxy(17, 36);
	printf("�� Q �Է� �� ��ǳ�� ����");
	gotoxy(17, 37);
	printf("�� ��ǳ���� 2������ ���� ����");
	gotoxy(17, 38);
	printf("�� ����� 3�� ��ǳ���� ���������� ��� -1");
	gotoxy(21, 42);
	printf("1. ���ӽ���");

	while (1)
	{
		if (_kbhit())
		{
			start = getch(); //����Ű �Է�
			if (start == '1')
			{
				system("cls"); return 0;
			}
			else return 1;
		}
	}
}