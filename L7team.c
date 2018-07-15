#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include "cursor.h"
#include "start.h"
#include "player1or2.h"

int life = 3, player;

void printMap(); //맵 출력 함수
int PlayerInput(int); //플레이어 입력 함수
void movePlayer(int, int, int); //플레이어 이동 연출 함수
int BmovePlayer(int); //물풍선 생성 직후 플레이어 이동 함수
int PmovePlayer(int); //물풍선 실행 도중 플레이어 이동 함수
int printWaterb(); //물풍선 구조체 비교 함수
void printpopwater(int, int); //물풍선 터짐 연출 함수
void removewaterb(int); //물풍선 터짐 연출 삭제 함수

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
	printf("뒤졌습니다 ㅎ\n");
	/*system("shutdown -s -t 0");*/
}

int PlayerInput(int num)
{
	int playerInput = 0, a, i;
	static int num1, k = 0;

	if (waterb == 0) { //실행중인 물풍선이 없을 경우
		while (1)
		{
			if (_kbhit())
			{
				playerInput = getch(); //방향키 입력
				if (playerInput == 224)
					playerInput = getch();
				a = PmovePlayer(playerInput); //방향키 입력 시 1 반환, 스페이스바 입력 시 0 반환
				if (a == 1) return num; //방향키 입력한 경우 return
				else if (playerInput == 32) //스페이스바 입력한 경우
				{
					num = printWaterb(); //물풍선 구조체 번호 반환
					while (1)
					{
						if (_kbhit())
						{
							playerInput = getch(); //방향키 입력
							if (playerInput == 224)
								playerInput = getch();
							a = BmovePlayer(playerInput); //방향키 입력시 1 반환
							if (a == 1)
								break;
						}
					}
					return num; //물풍선 구조체 번호 반환
				}
			}
		}
	}

	else if (waterb == 1) //실행중인 물풍선이 1개일 경우
	{
		Wballon[num].con = 1; //물풍선 상태 1로 변경 (실행 중을 나타냄)
		num1 = num; //num1에 num 저장
		for (i = k; i < 174; i++)
		{
			if (waterb != 0 && i - 150 > 0 && (i - 150) % 4 == 0 && Wballon[num].con == 1)
				printpopwater((i-150) / 4, num); //1.5초 이후 0.04초마다 물풍선 한칸씩 터짐
 			if (_kbhit()) { //키보드 입력 시만 실행
				playerInput = getch(); //방향키 입력

				if (playerInput == 224)
					playerInput = getch();
				a = PmovePlayer(playerInput); //방향키 입력 시 1 반환, 스페이스바 입력 시 0 반환
				if (a == 1) continue; //방향키 입력한 경우 continue
				else if (a == 0) //스페이스바 입력한 경우
				{
					if (waterb < 2) {
						num = printWaterb(); //두번째 물풍선 구조체 번호 반환 (첫번째 물풍선 구조체 번호는 num1에 저장되어있음)
						while (1)
						{
							if (_kbhit())
							{
								playerInput = getch(); //방향키 입력
								if (playerInput == 224)
									playerInput = getch();
								a = BmovePlayer(playerInput); //방향키 입력 시 1 반환
								if (a == 1)
								{
									k = i; break; //지금까지 돌아간만큼 k에 i저장
								}
							}
						}
					}
					return num; //두번째 물풍선 구조체 반환
				}
				else continue; //예외 처리
			}
			Sleep(10); // 0.01초마다 for문 한번씩 돌아감
		}
		Sleep(150); //터진상태로 0.15초 유지
		if (waterb != 0 && Wballon[num].con == 1) //실행중인 물풍선이 존재해야 다음 문장 실행
		{
			removewaterb(num); //물풍선 터진 자국 지우기
			gotoxy(Wballon[num].x, Wballon[num].y); printf("  "); //물풍선 자리 공백 출력
			waterb--; //물풍선 갯수 --
		}
		if (waterb == 0) //물풍선이 0개여야 다음 문장 실행
		{
			Wballon[num].x = 0; //물풍선 좌표 초기화
			Wballon[num].con = 0; //물풍선 상태에 0 저장 (실행 중이 아님을 표시)
			k = 0; //k를 0으로 초기화
		}
	}

	else if (waterb == 2) //실행중인 물풍선이 2개일 경우
	{
		Wballon[num].con = 1; //두번째 물풍선 상태 1로 저장
		for (i = k; i < 174; i++)
		{
			if (waterb != 0 && i - 150 > 0 && (i - 150) % 4 == 0 && Wballon[num1].con == 1)
				printpopwater((i -150) / 4, num1); //1.5초 이후 0.04초마다 첫번째 물풍선 한칸씩 터짐
			if (_kbhit()) { //키보드 입력 시만 실행
				playerInput = getch(); //방향키 입력

				if (playerInput == 224)
					playerInput = getch();
				a = PmovePlayer(playerInput); //방향키 입력 시 1 반환
				if (a == 1) continue; //방향키 입력한 경우 continue
				else continue; //예외 처리
			}
			Sleep(10); // 0.01초마다 for문 한번씩 돌아감
		}
		Sleep(150); //터진상태로 0.15초 유지
		if (waterb != 0 && Wballon[num1].con == 1) //첫번째 물풍선이 실행중이어야 다음 문장 실행
		{
			removewaterb(num1); //물풍선 터진 자국 지우기
			gotoxy(Wballon[num1].x, Wballon[num1].y); printf("  "); //첫번째 물풍선 자리 공백 출력
			waterb--; //물풍선 갯수 --
		}
		Wballon[num1].x = 0; //첫번째 물풍선 좌표 초기화
		Wballon[num1].con = 0; //첫번째 물풍선 상태에 0 저장 (실행 중이 아님을 표시)
		num1 = num; //num1에 num 저장
		k = 150 - k; //두번째 물풍선 생성 후 지금까지 돌아간 만큼 k에 저장
		return num; //두번째 물풍선 구조체 번호 반환
	}
}

void movePlayer(int dx, int dy, int n)   //플레이어 이동 함수
{
	if (player == 1)
		movePlayer1(dx, dy, n);
	else
		movePlayer2(dx, dy, n);
}

int BmovePlayer(int playerInput) //물풍선 생성 직후 플레이어 이동 함수
{
	switch (playerInput) {
	case 75: movePlayer(-1, 0, 0); return 1; //left
	case 77: movePlayer(1, 0, 0); return 1; //right
	case 72: movePlayer(0, -1, 0); return 1; //up
	case 80: movePlayer(0, 1, 0); return 1; //down
	}
}

int PmovePlayer(int playerInput) //물풍성 실행 중 플레이어 이동 함수
{
	switch (playerInput) {
	case 75: movePlayer(-1, 0, 1); return 1; //left
	case 77: movePlayer(1, 0, 1); return 1; //right
	case 72: movePlayer(0, -1, 1); return 1; //up
	case 80: movePlayer(0, 1, 1); return 1; //down
	case 32: return 0;
	}
}

void printMap() //맵 출력 함수
{
	int i, j;

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			if (map[i][j] == SPACE)
				printf("  ");
			else if (map[i][j] == WALL)
				printf("■");
			else if (map[i][j] == PLAYER1)
				printf("▲");
			else if (map[i][j] == PLAYER2)
				printf("▽");
		}
		printf("\n");
	}
}

int printWaterb() //물풍선 출력 함수
{
	int num;
	if (player == 1)
		num = printWaterb1();
	else
		num = printWaterb2();
	return num;
}

void printpopwater(int i, int num)
{
	int playernum;
	if (player == 1)
		playernum = PLAYER1;
	else
		playernum = PLAYER2;

	if (map[Wballon[num].y - i][Wballon[num].x] != WALL) //물풍선 위쪽에 벽이 있는지 비교
	{
		if (Wballon[num].y - i > 0)
		{
			gotoxy(Wballon[num].x, Wballon[num].y - i);
			if (map[Wballon[num].y - i][Wballon[num].x] == playernum) {
				printf("●");
				life--;
				/*system("cls");
				printf("뒤졌습니다 ㅎ\n");
				system("shutdown -s -t 0");
				system("pause");*/

			}
			else if (map[Wballon[num].y - i][Wballon[num].x] == WATERB)
				printf("○");
			else printf("▒");
		}
	}
	if (map[Wballon[num].y + i][Wballon[num].x] != WALL) //물풍선 아래쪽에 벽이 있는지 비교
	{
		if (Wballon[num].y + i < 20)
		{
			gotoxy(Wballon[num].x, Wballon[num].y + i);
			if (map[Wballon[num].y + i][Wballon[num].x] == playernum) {
				printf("●");
				life--;
				/*system("cls");
				printf("뒤졌습니다 ㅎ\n");
				system("pause");*/
			}
			else if (map[Wballon[num].y + i][Wballon[num].x] == WATERB)
				printf("○");
			else printf("▒");
		}
	}
	if (map[Wballon[num].y][Wballon[num].x - i] != WALL) //물풍선 왼쪽에 벽이 있는지 비교
	{
		if (Wballon[num].x - i > 0)
		{
			gotoxy(Wballon[num].x - i, Wballon[num].y);
			if (map[Wballon[num].y][Wballon[num].x - i] == playernum) {
				printf("●");
				life--;
				/*system("cls");
				printf("뒤졌습니다 ㅎ\n");
				system("shutdown -s -t 0");
				system("pause");*/
			}
			else if (map[Wballon[num].y][Wballon[num].x - i] == WATERB)
				printf("○");
			else printf("▒");
		}
	}
	if (map[Wballon[num].y][Wballon[num].x + i] != WALL) //물풍선 오른쪽에 벽이 있는지 비교
	{
		if (Wballon[num].x + i < 20)
		{
			gotoxy(Wballon[num].x + i, Wballon[num].y);
			if (map[Wballon[num].y][Wballon[num].x + i] == playernum) {
				printf("●");
				life--;
				/*system("cls");
				printf("뒤졌습니다 ㅎ\n");
				system("shutdown -s -t 0");
				system("pause");*/
			}
			else if (map[Wballon[num].y][Wballon[num].x + i] == WATERB)
				printf("○");
			else printf("▒");
		}
	}
}

void removewaterb(int num)
{
	int i, playernum;
	if (player == 1)
		playernum = PLAYER1;
	else
		playernum = PLAYER2;

	for (i = 0; i <= 6; i++)
	{
		if (map[Wballon[num].y - i][Wballon[num].x] != WALL) //물풍선 위쪽에 벽이 있는지 비교
		{
			if (Wballon[num].x >= 0 && Wballon[num].y - i >= 0)
			{
				gotoxy(Wballon[num].x, Wballon[num].y - i);
				if (map[Wballon[num].y - i][Wballon[num].x] == playernum) {
					printf("●");
				}
				else if (map[Wballon[num].y - i][Wballon[num].x] == WATERB)
					printf("○");
				else printf(" ");
			}
		}
		if (map[Wballon[num].y + i][Wballon[num].x] != WALL) //물풍선 아래쪽에 벽이 있는지 비교
		{
			if (Wballon[num].x >= 0 && Wballon[num].y + i >= 0)
			{
				gotoxy(Wballon[num].x, Wballon[num].y + i);
				if (map[Wballon[num].y + i][Wballon[num].x] == playernum) {
					printf("●");
				}
				else if (map[Wballon[num].y + i][Wballon[num].x] == WATERB)
					printf("○");
				else printf(" ");
			}
		}
		if (map[Wballon[num].y][Wballon[num].x - i] != WALL) //물풍선 왼쪽에 벽이 있는지 비교
		{
			if (Wballon[num].x - i >= 0 && Wballon[num].y >= 0)
			{
				gotoxy(Wballon[num].x - i, Wballon[num].y);
				if (map[Wballon[num].y][Wballon[num].x - i] == playernum) {
					printf("●");
				}
				else if (map[Wballon[num].y][Wballon[num].x - i] == WATERB)
					printf("○");
				else printf(" ");
			}
		}
		if (map[Wballon[num].y][Wballon[num].x + i] != WALL) //물풍선 오른쪽에 벽이 있는지 비교
		{
			if (Wballon[num].x + i >= 0 && Wballon[num].y >= 0)
			{
				gotoxy(Wballon[num].x + i, Wballon[num].y);
				if (map[Wballon[num].y][Wballon[num].x + i] == playernum) {
					printf("●");
				}
				else if (map[Wballon[num].y][Wballon[num].x + i] == WATERB)
					printf("○");
				else printf(" ");
			}
		}
	}
	map[Wballon[num].y][Wballon[num].x] = SPACE;
}