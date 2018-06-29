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

int player1X = 1, player1Y = 1; // 플레이어 초기 좌표
int waterb = 0; //물풍선 초기 개수
struct ballon //물풍선 좌표 구조체
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
void printMap(); //맵 출력 함수
void printpopwater(int, int); //물풍선 터짐 연출 함수
void removewaterb(int); //물풍선 터짐 연출 삭제 함수
void PlayerInput(); //플레이어 입력 함수
void movePlayer(int, int); //플레이어 이동 함수
void BmovePlayer(); //물풍선 생성 직후 플레이어 이동 함수
int PmovePlayer(int, int, int); //물풍선 터짐 함수 도중 플레이어 이동 함수
int printWaterb(); //물풍선 출력 함수
void popWaterb(int, int); //물풍선 터짐 함수

int main() {
	int pl = 0;
	while (1)
	{
		printf("인원 수를 입력해주세요 : ");
		scanf("%d", &pl);
		if (pl < 2) {
			printf("최소 2명을 입력해주세요!\n");
		}
		else if (pl > 4) {
			printf("최대 4명입니다!\n\n");
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
	printf("뒤졌습니다 ㅎ\n");
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

void movePlayer(int dx, int dy)   //플레이어 이동 함수
{
	if (map[player1Y + dy][player1X + dx] == SPACE) //이동할 공간에 아무것도 없는지 비교
	{
		gotoxy(player1X, player1Y);
		printf("  "); //원래 좌표에 공백 출력
		map[player1Y][player1X] = SPACE; //원래 좌표 공간에 SPACE 저장
		player1X += dx;
		player1Y += dy;
		gotoxy(player1X, player1Y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("▲"); //이동 좌표에 플레이어 출력
		map[player1Y][player1X] = PLAYER1; //이동 좌표 공간에 PLAYER1 저장
	}
}

void bmove(int dx, int dy)
{
	if (map[player1Y + dy][player1X + dx] == SPACE) //이동할 공간에 아무것도 없는지 비교
	{
		gotoxy(player1X, player1Y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("○"); //원래 좌표에 물풍선 출력
		map[player1Y][player1X] = WATERB; //원래 좌표 공간에 WATERB 저장
		player1X += dx;
		player1Y += dy;
		gotoxy(player1X, player1Y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("▲"); //이동 좌표에 플레이어 출력
		map[player1Y][player1X] = PLAYER1; //이동 좌표 공간에 PLAYER1 저장
		waterb++;
	}
	else BmovePlayer();
}

void BmovePlayer() //물풍선 생성 직후 플레이어 이동 함수
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

int PmovePlayer(int num1, int num, int k) //popWaterb 전용 플레이어 이동 함수
{
	int playerInput, dx, dy, i;
	if (life != 0){
		for (i = k; i < 150; i++)
		{
			if (_kbhit()) { //키보드 입력 시만 실행
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
			Sleep(10); //0.01초 동안 for문 한 번 실행 : 키보드 입력 없을 시 다음으로 넘어감
		}
		for (i = 1; i < 24; i++) {
			if (_kbhit()) { //키보드 입력 시만 실행
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

int printWaterb() //물풍선 출력 함수
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
		BmovePlayer();
		return i;
	}

}

void popWaterb(int num, int num1, int k) //물풍선 터짐 함수
{
	if (life != 0){
		if (waterb == 1) { //생성된 물풍선이 한 개일 경우
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
			k = PmovePlayer(num1, num1, k); //물풍선이 두개이기 때문에 먼저 들어온 물풍선과 나중에 들어온 물풍선을 비교하기 위해 num1 사용
			Wballon[num1].x = 0;
			Wballon[num1].con = 0;
			num1 = num;
			k = PmovePlayer(num1, num, k);
			Wballon[num1].x = 0;
			Wballon[num1].con = 0;
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
			else if (map[i][j] == PLAYER3)
				printf("△");
			else if (map[i][j] == PLAYER4)
				printf("▼");
		}
		printf("\n");
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
				life = 0;
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
				life = 0;
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
				life = 0;
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
				life = 0;
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
				if (map[Wballon[num].y - i][Wballon[num].x] == PLAYER1) {
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
				if (map[Wballon[num].y + i][Wballon[num].x] == PLAYER1) {
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
				if (map[Wballon[num].y][Wballon[num].x - i] == PLAYER1) {
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
				if (map[Wballon[num].y][Wballon[num].x + i] == PLAYER1) {
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