#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include "cursor.h"
#include "start.h"
#include "player1or2.h"

void movePlayer1(int dx, int dy, int n)   //플레이어 이동 함수
{
	if (map[player1Y + dy][player1X + dx] == SPACE) //이동할 공간에 아무것도 없는지 비교
	{
		gotoxy(player1X, player1Y);
		if (n == 1) {
			printf("  "); //원래 좌표에 공백 출력
			map[player1Y][player1X] = SPACE; //원래 좌표 공간에 SPACE 저장
			player1X += dx;
			player1Y += dy;
			gotoxy(player1X, player1Y);
			printf("▲"); //이동 좌표에 플레이어 출력
			map[player1Y][player1X] = PLAYER1; //이동 좌표 공간에 PLAYER1 저장
		}
		else
		{
			printf("○"); //원래 좌표에 물풍선 출력
			map[player1Y][player1X] = WATERB; //원래 좌표 공간에 WATERB 저장
			player1X += dx;
			player1Y += dy;
			gotoxy(player1X, player1Y);
			printf("▲"); //이동 좌표에 플레이어 출력
			map[player1Y][player1X] = PLAYER1; //이동 좌표 공간에 PLAYER1 저장
			waterb++;
		}
	}
}

void movePlayer2(int dx, int dy, int n)   //플레이어 이동 함수
{
	if (map[player2Y + dy][player2X + dx] == SPACE) //이동할 공간에 아무것도 없는지 비교
	{
		gotoxy(player2X, player2Y);
		if (n == 1) {
			printf("  "); //원래 좌표에 공백 출력
			map[player2Y][player2X] = SPACE; //원래 좌표 공간에 SPACE 저장
			player2X += dx;
			player2Y += dy;
			gotoxy(player2X, player2Y);
			printf("▽"); //이동 좌표에 플레이어 출력
			map[player2Y][player2X] = PLAYER2; //이동 좌표 공간에 PLAYER1 저장
		}
		else
		{
			printf("○"); //원래 좌표에 물풍선 출력
			map[player2Y][player2X] = WATERB; //원래 좌표 공간에 WATERB 저장
			player2X += dx;
			player2Y += dy;
			gotoxy(player2X, player2Y);
			printf("▽"); //이동 좌표에 플레이어 출력
			map[player2Y][player2X] = PLAYER2; //이동 좌표 공간에 PLAYER1 저장
			waterb++;
		}
	}
}

int printWaterb1() //물풍선 출력 함수
{
	int i;
	if (waterb < 2) //현재 생성되어있는 물풍선 개수 비교
	{
		for (i = 0; i <= 1; i++)
		{
			if (Wballon[i].x == 0) //비어있는 구조체인지 확인
			{
				Wballon[i].x = player1X; //i번 물풍선 X좌표에 플레이어 X좌표 저장
				Wballon[i].y = player1Y; //i번 물풍선 Y좌표에 플레이어 Y좌표 저장
				break;
			}
		}
		return i;
	}
}

int printWaterb2() //물풍선 출력 함수
{
	int i;
	if (waterb < 2) //현재 생성되어있는 물풍선 개수 비교
	{
		for (i = 2; i <= 3; i++)
		{
			if (Wballon[i].x == 0) //비어있는 구조체인지 확인
			{
				Wballon[i].x = player1X; //i번 물풍선 X좌표에 플레이어 X좌표 저장
				Wballon[i].y = player1Y; //i번 물풍선 Y좌표에 플레이어 Y좌표 저장
				break;
			}
		}
		return i;
	}
}