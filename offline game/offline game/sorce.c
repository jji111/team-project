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

struct ballon //물풍선 좌표 구조체
{
	int x; int y; int con;
}Wballon[4] = { 0 };
int player1X = 1, player1Y = 1, player2X = 18, player2Y = 18; // 플레이어 초기 좌표
int waterb1 = 0, waterb2 = 0; //물풍선 초기 개수
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

void printMap(); //맵 출력 함수
int PlayerInput(int); //플레이어 입력 함수
int movePlayer(int, int, int, int); //플레이어 이동 연출 함수
int BmovePlayer(int, int); //물풍선 생성 직후 플레이어 이동 함수
int PmovePlayer(int, int); //물풍선 실행 도중 플레이어 이동 함수
int printWaterb(int); //물풍선 구조체 비교 함수
void printpopwater(int, int); //물풍선 터짐 연출 함수
void removewaterb(int); //물풍선 터짐 연출 삭제 함수

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
		printf("둘 다 거기서 거기");
	/*system("shutdown -s -t 0");*/
}

int PlayerInput(int num)
{
	int playerInput = 0, a, b, i, dnum;
	static int num1, k = 0;
	PlayerInput2();
	if (waterb1 == 0) { //실행중인 물풍선이 없을 경우
		PlayerInput2();
		if (_kbhit())
		{
			playerInput = getch(); //방향키 입력
			if (playerInput == 224)
				playerInput = getch();
			a = PmovePlayer(playerInput, 1); //방향키 입력 시 1 반환, 스페이스바 입력 시 0 반환
			if (a == 1) return num; //방향키 입력한 경우 return
			else if (playerInput == 32) //스페이스바 입력한 경우
			{
				num = printWaterb(1); //물풍선 구조체 번호 반환
				while (1)
				{
					if (_kbhit())
					{
						playerInput = getch(); //방향키 입력
						if (playerInput == 224)
							playerInput = getch();
						a = BmovePlayer(playerInput, 1); //방향키 입력시 1 반환
						if (a == 1)
							break;
					}
				}
				return num; //물풍선 구조체 번호 반환
			}
		}
	}

	else if (waterb1 == 1) //실행중인 물풍선이 1개일 경우
	{
		Wballon[num].con = 1; //물풍선 상태 1로 변경 (실행 중을 나타냄)
		num1 = num; //num1에 num 저장
		PlayerInput2();
		for (i = k; i < 168; i++)
		{
			if (waterb1 != 0 && i - 150 > 0 && (i - 150) % 3 == 0 && Wballon[num].con == 1)
				printpopwater((i - 150) / 3, num); //1.5초 이후 0.04초마다 물풍선 한칸씩 터짐
			if (_kbhit()) { //키보드 입력 시만 실행
				playerInput = getch(); //방향키 입력

				if (playerInput == 224)
					playerInput = getch();
				a = PmovePlayer(playerInput, 2); //방향키 입력 시 1 반환, 스페이스바 입력 시 0 반환
				b = PmovePlayer(playerInput, 1);
				if (a == 1 && b == 1) continue; //방향키 입력한 경우 continue
				else if (playerInput == 113) //스페이스바 입력한 경우
				{
					if (waterb2 < 2) {
						num = printWaterb(2); //두번째 물풍선 구조체 번호 반환 (첫번째 물풍선 구조체 번호는 num1에 저장되어있음)
						while (1)
						{
							if (_kbhit())
							{
								playerInput = getch(); //방향키 입력
								a = BmovePlayer(playerInput, 2); //방향키 입력 시 1 반환
								if (a == 1)
								{
									k = i; break; //지금까지 돌아간만큼 k에 i저장
								}
							}
						}
					}
					return num; //두번째 물풍선 구조체 반환
				}
				else if (playerInput == 32) //스페이스바 입력한 경우
				{
					if (waterb1 < 2) {
						num = printWaterb(1); //두번째 물풍선 구조체 번호 반환 (첫번째 물풍선 구조체 번호는 num1에 저장되어있음)
						while (1)
						{
							if (_kbhit())
							{
								playerInput = getch(); //방향키 입력
								a = BmovePlayer(playerInput, 1); //방향키 입력 시 1 반환
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
		if (waterb1 != 0 && Wballon[num].con == 1) //실행중인 물풍선이 존재해야 다음 문장 실행
		{
			removewaterb(num); //물풍선 터진 자국 지우기
			gotoxy(Wballon[num].x, Wballon[num].y); printf("  "); //물풍선 자리 공백 출력
			waterb1--; //물풍선 갯수 --
		}
		if (waterb1 == 0) //물풍선이 0개여야 다음 문장 실행
		{
			Wballon[num].x = 0; //물풍선 좌표 초기화
			Wballon[num].con = 0; //물풍선 상태에 0 저장 (실행 중이 아님을 표시)
			k = 0; //k를 0으로 초기화
		}
	}

	else if (waterb1 == 2) //실행중인 물풍선이 2개일 경우
	{
		Wballon[num].con = 1; //두번째 물풍선 상태 1로 저장
		PlayerInput2();
		for (i = k; i < 168; i++)
		{
			if (waterb1 != 0 && i - 150 > 0 && (i - 150) % 3 == 0 && Wballon[num1].con == 1)
				printpopwater((i - 150) / 3, num1); //1.5초 이후 0.04초마다 첫번째 물풍선 한칸씩 터짐
			if (_kbhit()) { //키보드 입력 시만 실행
				playerInput = getch(); //방향키 입력

				if (playerInput == 224)
					playerInput = getch();
				a = PmovePlayer(playerInput, 2); //방향키 입력 시 1 반환, 스페이스바 입력 시 0 반환
				b = PmovePlayer(playerInput, 1);
				if (a == 1 && b == 1) continue; //방향키 입력한 경우 continue
				else if (playerInput == 113) //스페이스바 입력한 경우
				{
					if (waterb2 < 2) {
						num = printWaterb(2); //두번째 물풍선 구조체 번호 반환 (첫번째 물풍선 구조체 번호는 num1에 저장되어있음)
						while (1)
						{
							if (_kbhit())
							{
								playerInput = getch(); //방향키 입력
								a = BmovePlayer(playerInput, 2); //방향키 입력 시 1 반환
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
		if (waterb1 != 0 && Wballon[num1].con == 1) //첫번째 물풍선이 실행중이어야 다음 문장 실행
		{
			removewaterb(num1); //물풍선 터진 자국 지우기
			gotoxy(Wballon[num1].x, Wballon[num1].y); printf("  "); //첫번째 물풍선 자리 공백 출력
			waterb1--; //물풍선 갯수 --
		}
		Wballon[num1].x = 0; //첫번째 물풍선 좌표 초기화
		Wballon[num1].con = 0; //첫번째 물풍선 상태에 0 저장 (실행 중이 아님을 표시)
		num1 = num; //num1에 num 저장
		k = 150 - k; //두번째 물풍선 생성 후 지금까지 돌아간 만큼 k에 저장
		return num; //두번째 물풍선 구조체 번호 반환
	}

}

int PlayerInput2() {
	int playerInput, a, b, i, dnum;
	static int num1, num, k = 0;

	if (waterb2 == 0) { //실행중인 물풍선이 없을 경우
		if (_kbhit())
		{
			playerInput = getch(); //방향키 입력
			a = PmovePlayer(playerInput, 2); //방향키 입력 시 1 반환, 스페이스바 입력 시 0 반환
			if (a == 1) return num; //방향키 입력한 경우 return
			else if (playerInput == 113) //스페이스바 입력한 경우
			{
				num = printWaterb(2); //물풍선 구조체 번호 반환
				while (1)
				{
					if (_kbhit())
					{
						playerInput = getch(); //방향키 입력
						a = BmovePlayer(playerInput, 2); //방향키 입력시 1 반환
						if (a == 1)
							break;
					}
				}
				return num; //물풍선 구조체 번호 반환
			}
		}
	}

	else if (waterb2 == 1) //실행중인 물풍선이 1개일 경우
	{
		Wballon[num].con = 1; //물풍선 상태 1로 변경 (실행 중을 나타냄)
		num1 = num; //num1에 num 저장
		for (i = k; i < 168; i++)
		{
			if (waterb2 != 0 && i - 150 > 0 && (i - 150) % 3 == 0 && Wballon[num].con == 1)
				printpopwater((i - 150) / 3, num); //1.5초 이후 0.04초마다 물풍선 한칸씩 터짐
			if (_kbhit()) { //키보드 입력 시만 실행
				playerInput = getch(); //방향키 입력

				if (playerInput == 224)
					playerInput = getch();
				a = PmovePlayer(playerInput, 2); //방향키 입력 시 1 반환, 스페이스바 입력 시 0 반환
				b = PmovePlayer(playerInput, 1);
				if (a == 1 && b == 1) continue; //방향키 입력한 경우 continue
				else if (playerInput == 113) //스페이스바 입력한 경우
				{
					if (waterb2 < 2) {
						num = printWaterb(2); //두번째 물풍선 구조체 번호 반환 (첫번째 물풍선 구조체 번호는 num1에 저장되어있음)
						while (1)
						{
							if (_kbhit())
							{
								playerInput = getch(); //방향키 입력
								a = BmovePlayer(playerInput, 2); //방향키 입력 시 1 반환
								if (a == 1)
								{
									k = i; break; //지금까지 돌아간만큼 k에 i저장
								}
							}
						}
					}
					return num; //두번째 물풍선 구조체 반환
				}
				else if (playerInput == 32) //스페이스바 입력한 경우
				{
					if (waterb1 < 2) {
						dnum = printWaterb(1); //두번째 물풍선 구조체 번호 반환 (첫번째 물풍선 구조체 번호는 num1에 저장되어있음)
						while (1)
						{
							if (_kbhit())
							{
								playerInput = getch(); //방향키 입력
								a = BmovePlayer(playerInput, 1); //방향키 입력 시 1 반환
								if (a == 1)
								{
									k = i; break; //지금까지 돌아간만큼 k에 i저장
								}
							}
						}
					}
					return dnum; //두번째 물풍선 구조체 반환
				}
				else continue; //예외 처리
			}
			Sleep(10); // 0.01초마다 for문 한번씩 돌아감
		}
		Sleep(150); //터진상태로 0.15초 유지
		if (waterb2 != 0 && Wballon[num].con == 1) //실행중인 물풍선이 존재해야 다음 문장 실행
		{
			removewaterb(num); //물풍선 터진 자국 지우기
			gotoxy(Wballon[num].x, Wballon[num].y); printf("  "); //물풍선 자리 공백 출력
			waterb2--; //물풍선 갯수 --
		}
		if (waterb2 == 0) //물풍선이 0개여야 다음 문장 실행
		{
			Wballon[num].x = 0; //물풍선 좌표 초기화
			Wballon[num].con = 0; //물풍선 상태에 0 저장 (실행 중이 아님을 표시)
			k = 0; //k를 0으로 초기화
		}
	}

	else if (waterb2 == 2) //실행중인 물풍선이 2개일 경우
	{
		Wballon[num].con = 1; //두번째 물풍선 상태 1로 저장
		for (i = k; i < 168; i++)
		{
			if (waterb2 != 0 && i - 150 > 0 && (i - 150) % 3 == 0 && Wballon[num1].con == 1)
				printpopwater((i - 150) / 3, num1); //1.5초 이후 0.04초마다 첫번째 물풍선 한칸씩 터짐
			if (_kbhit()) { //키보드 입력 시만 실행
				playerInput = getch(); //방향키 입력

				if (playerInput == 224)
					playerInput = getch();
				a = PmovePlayer(playerInput, 2); //방향키 입력 시 1 반환, 스페이스바 입력 시 0 반환
				b = PmovePlayer(playerInput, 1);
				if (a == 1 && b == 1) continue; //방향키 입력한 경우 continue
				else if (playerInput == 32) //스페이스바 입력한 경우
				{
					if (waterb1 < 2) {
						dnum = printWaterb(1); //두번째 물풍선 구조체 번호 반환 (첫번째 물풍선 구조체 번호는 num1에 저장되어있음)
						while (1)
						{
							if (_kbhit())
							{
								playerInput = getch(); //방향키 입력
								a = BmovePlayer(playerInput, 1); //방향키 입력 시 1 반환
								if (a == 1)
								{
									k = i; break; //지금까지 돌아간만큼 k에 i저장
								}
							}
						}
					}
					return dnum; //두번째 물풍선 구조체 반환
				}
				else continue; //예외 처리
			}
			Sleep(10); // 0.01초마다 for문 한번씩 돌아감
		}
		Sleep(150); //터진상태로 0.15초 유지
		if (waterb2 != 0 && Wballon[num1].con == 1) //첫번째 물풍선이 실행중이어야 다음 문장 실행
		{
			removewaterb(num1); //물풍선 터진 자국 지우기
			gotoxy(Wballon[num1].x, Wballon[num1].y); printf("  "); //첫번째 물풍선 자리 공백 출력
			waterb2--; //물풍선 갯수 --
		}
		Wballon[num1].x = 0; //첫번째 물풍선 좌표 초기화
		Wballon[num1].con = 0; //첫번째 물풍선 상태에 0 저장 (실행 중이 아님을 표시)
		num1 = num; //num1에 num 저장
		k = 150 - k; //두번째 물풍선 생성 후 지금까지 돌아간 만큼 k에 저장
		return num; //두번째 물풍선 구조체 번호 반환
	}
}

int movePlayer(int dx, int dy, int n, int player) //플레이어 이동 함수
{
	if (player == 1) {
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
				waterb1++;
			}
		}
		else return 0;
	}
	else if (player == 2) {
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
				waterb2++;
			}
		}
		else return 0;
	}
}

int BmovePlayer(int playerInput, int player) //물풍선 생성 직후 플레이어 이동 함수
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

int PmovePlayer(int playerInput, int player) //물풍성 실행 중 플레이어 이동 함수
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

int printWaterb(int player) //물풍선 출력 함수
{
	int i;
	if (player == 1) {
		if (waterb1 < 2) //현재 생성되어있는 물풍선 개수 비교
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
	else if (player == 2)
	{
		if (waterb2 < 2) //현재 생성되어있는 물풍선 개수 비교
		{
			for (i = 2; i <= 3; i++)
			{
				if (Wballon[i].x == 0) //비어있는 구조체인지 확인
				{
					Wballon[i].x = player2X; //i번 물풍선 X좌표에 플레이어 X좌표 저장
					Wballon[i].y = player2Y; //i번 물풍선 Y좌표에 플레이어 Y좌표 저장
					break;
				}
			}
			return i;
		}
	}
}

void printpopwater(int i, int num)
{
	if (map[Wballon[num].y - i][Wballon[num].x] != WALL) //물풍선 위쪽에 벽이 있는지 비교
	{
		if (Wballon[num].y - i > 0)
		{
			gotoxy(Wballon[num].x, Wballon[num].y - i);
			if (map[Wballon[num].y - i][Wballon[num].x] == PLAYER1) {
				printf("●");
				life1--;
			}
			if (map[Wballon[num].y - i][Wballon[num].x] == PLAYER2) {
				printf("●");
				life2--;
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
			if (map[Wballon[num].y + i][Wballon[num].x] == PLAYER1) {
				printf("●");
				life1--;
			}
			if (map[Wballon[num].y + i][Wballon[num].x] == PLAYER2) {
				printf("●");
				life2--;
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
			if (map[Wballon[num].y][Wballon[num].x - i] == PLAYER1) {
				printf("●");
				life1--;
			}
			if (map[Wballon[num].y][Wballon[num].x - i] == PLAYER2) {
				printf("●");
				life2--;
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
			if (map[Wballon[num].y][Wballon[num].x + i] == PLAYER1) {
				printf("●");
				life1--;
			}
			if (map[Wballon[num].y][Wballon[num].x + i] == PLAYER2) {
				printf("●");
				life2--;
			}
			else if (map[Wballon[num].y][Wballon[num].x + i] == WATERB)
				printf("○");
			else printf("▒");
		}
	}
}

void removewaterb(int num)
{
	int i;
	for (i = 0; i <= 6; i++)
	{
		if (map[Wballon[num].y - i][Wballon[num].x] != WALL) //물풍선 위쪽에 벽이 있는지 비교
		{
			if (Wballon[num].x >= 0 && Wballon[num].y - i >= 0)
			{
				gotoxy(Wballon[num].x, Wballon[num].y - i);
				if (map[Wballon[num].y - i][Wballon[num].x] == PLAYER1 || map[Wballon[num].y - i][Wballon[num].x] == PLAYER2) {
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
				if (map[Wballon[num].y + i][Wballon[num].x] == PLAYER1 || map[Wballon[num].y + i][Wballon[num].x] == PLAYER2) {
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
				if (map[Wballon[num].y][Wballon[num].x - i] == PLAYER1 || map[Wballon[num].y][Wballon[num].x - i] == PLAYER2) {
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
				if (map[Wballon[num].y][Wballon[num].x + i] == PLAYER1 || map[Wballon[num].y][Wballon[num].x + i] == PLAYER2) {
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