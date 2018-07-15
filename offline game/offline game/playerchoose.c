#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "cursor.h"
#include "start.h"

int pchoose()
{
	char player;

	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if (i == 0 || i == 49 || j == 0 || j == 49)
				printf("■");
			else
				printf("  ");
		}
		printf("\n");
	}
	sa();

	tc(15);
	gotoxy(17, 33);
	printf("플레이어를 선택해주세요");
	gotoxy(17, 35);
	printf("1. player1");
	gotoxy(17, 36);
	printf("2. player2");

	while (1)
	{
		if (_kbhit())
		{
			player = getch(); //방향키 입력
			if (player == '1')
			{
				system("cls"); return 1;
			}
			else if (player == '2')
			{
				system("cls"); return 2;
			}
		}
	}
}