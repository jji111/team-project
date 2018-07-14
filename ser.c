#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include "cursor.h"

#pragma comment(lib, "ws2_32.lib") 

#define BUF_SIZE 100
#define NAME_SIZE 20
#define SPACE 0
#define WALL 1
#define PLAYER1 2
#define PLAYER2 3
#define PLAYER3 4
#define PLAYER4 5
#define WATERB 6

struct ballon //물풍선 좌표 구조체
{
	int x; int y; int con;
}Wballon[8] = { 0 };
int player1X = 1, player1Y = 1; // 플레이어 초기 좌표
int waterb = 0; //물풍선 초기 개수
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
void PlayerInput(); //플레이어 입력 함수
void movePlayer(int, int); //플레이어 이동 함수
void BmovePlayer(); //물풍선 생성 직후 플레이어 이동 함수
int PmovePlayer(int, int, int); //물풍선 터짐 함수 도중 플레이어 이동 함수
int printWaterb(); //물풍선 출력 함수
void popWaterb(int, int); //물풍선 터짐 함수
void printpopwater(int, int); //물풍선 터짐 연출 함수
void removewaterb(int); //물풍선 터짐 연출 삭제 함수
void sa();
void tc(int a);
void end();


char name[NAME_SIZE] = { 0, };
char msg[BUF_SIZE] = { 0, };

unsigned WINAPI SendMsg(void *arg);
unsigned WINAPI RecvMsg(void *arg);
void ErrorHandling(char *arg); //ok?

/*HANDLE Thread( // 쓰레드 생성
LPSECURITY_ATTRIBUTES lpThreadAttributes, // 쓰레드의 보안관련 정보 전달
SIZE_T dwStackSize, // 쓰레드에게 할당한 스택의 크기를 전달
LPTHREAD_START_ROUTINE IpStartAddress, // 쓰레드의 main 함수 정보 전달
LPVOID IpParamter, // 쓰레드의 main 함수 호출시 전달할 인자 정보 전달
DWORD dwCreationFlags, // 쓰레드 생성 이후의 행동을 결정 (0을 정달하면 생성과 동시에 실행가능)
LPDWORD IpThreadID // 쓰레드의 ID 저장을 위한 변수의 주소값 전달
);*/

int main() {
	WSADATA wsaData;
	SOCKET hSock;
	SOCKADDR_IN servAdr;
	HANDLE hSndThread, hRcvThread;
	char port[100] = { 0, };
	char ip[100] = { 0, };
	printf("ip를 입력해주세요 : ");
	//gets(ip);
	strcpy(ip, "127.0.0.1");
	printf("port를 입력해주세요 : ");
	strcpy(port, "1234");
	//gets(port);
	printf("이름을 입력해주세요 : ");
	//gets(name);
	strcpy(name, " qq");

	system("mode con cols=100 lines=51");
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
	gotoxy(21, 38);
	printf("1.게임시작");
	gotoxy(21, 40);
	printf("2.게임설명");
	while (1) {
		if (_kbhit())
		{
			int playerInput;

			playerInput = getch();
			if (playerInput == 49) {
				break;
			}
		}
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error");
	}

	hSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr(ip);
	servAdr.sin_port = htons(atoi(port));

	if (connect(hSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR) {
		ErrorHandling("Connect() Error");
	}

	system("cls");

	removeCursor();
	printMap();
	
	while (1) {
		hSndThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&hSock, 0, NULL);
		hRcvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&hSock, 0, NULL); // 멍미....?
	}
	WaitForSingleObject(hSndThread, INFINITE);
	WaitForSingleObject(hRcvThread, INFINITE);

	closesocket(hSock);
	WSACleanup();
	return 0;
}

unsigned WINAPI SendMsg(void *arg) {
	SOCKET hSock = *((SOCKET*)arg);
	while (1) {
		if (_kbhit())
		{
			char nameMsg[BUF_SIZE] = { 0, };
			int playerInput, num;
			playerInput = getch();
			if (playerInput == 224)
				playerInput = getch();
			switch (playerInput) {
			case 75: movePlayer(-1, 0, 1); sprintf(nameMsg, "%s left", name); send(hSock, nameMsg, strlen(nameMsg), 0); return; //left
			case 77: movePlayer(1, 0, 1); sprintf(nameMsg, "%s right", name); send(hSock, nameMsg, strlen(nameMsg), 0); return; //right
			case 72: movePlayer(0, -1, 1); sprintf(nameMsg, "%s up", name); send(hSock, nameMsg, strlen(nameMsg), 0); return; //up
			case 80: movePlayer(0, 1, 1); sprintf(nameMsg, "%s down", name); send(hSock, nameMsg, strlen(nameMsg), 0); return; //down
			case 32: 
				sprintf(nameMsg, "%s ball", name); 
				send(hSock, nameMsg, strlen(nameMsg), 0); 
				num = printWaterb();
				popWaterb(num, 0, 1);
				return;//waterballon
			}
		}
		Sleep(10);
	}
}

unsigned WINAPI RecvMsg(void *arg) {
	int hSock = *((SOCKET*)arg);
	char nameMsg[BUF_SIZE];
	int strLen;
	while (1) {
		strLen = recv(hSock, nameMsg, BUF_SIZE - 1, 0);
		if (strLen == -1) {
			return -1;
		}
		nameMsg[strLen] = 0;
	}
}

void ErrorHandling(char *msg) {
	puts(msg);
	putc('\n', stderr);
	system("pause");
	exit(1);
}

/*
void PlayerInput()
{
	while (1)
	{
		if (_kbhit())
		{
			int playerInput, num;

			playerInput = getch();
			if (playerInput == 224)
				playerInput = getch();
			switch (playerInput) {
			case 75: movePlayer(-1, 0, 1); return; //left
			case 77: movePlayer(1, 0, 1); return; //right
			case 72: movePlayer(0, -1, 1); return; //up
			case 80: movePlayer(0, 1, 1); return; //down
			case 32: num = printWaterb();
				popWaterb(num, 0, 1); return;//waterballon
			}
		}
	}
}
*/

void movePlayer(int dx, int dy, int n)   //플레이어 이동 함수
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

void BmovePlayer() //물풍선 생성 직후 플레이어 이동 함수
{
	while (1)
	{
		if (_kbhit())
		{
			int playerInput;

			playerInput = getch();
			if (playerInput == 224)
				playerInput = getch();
			switch (playerInput) {
			case 75: movePlayer(-1, 0, 0); return; //left
			case 77: movePlayer(1, 0, 0); return; //right
			case 72: movePlayer(0, -1, 0); return; //up
			case 80: movePlayer(0, 1, 0); return; //down
			}
		}
	}
}
int PmovePlayer(int num1, int num, int k) //popWaterb 전용 플레이어 이동 함수
{
	int playerInput, dx, dy, i;
	for (i = k; i < 150; i++)
	{
		if (_kbhit()) { //키보드 입력 시만 실행
			playerInput = getch();

			if (playerInput == 224)
				playerInput = getch();
			if (playerInput == 75) //left
				movePlayer(-1, 0, 1);
			else if (playerInput == 77) //right
				movePlayer(1, 0, 1);
			else if (playerInput == 72) //up
				movePlayer(0, -1, 1);
			else if (playerInput == 80) //down
				movePlayer(0, 1, 1);
			else if (playerInput == 32) //waterballon
			{
				if (waterb < 2) {
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
				movePlayer(-1, 0, 1);
			else if (playerInput == 77) //right
				movePlayer(1, 0, 1);
			else if (playerInput == 72) //up
				movePlayer(0, -1, 1);
			else if (playerInput == 80) //down
				movePlayer(0, 1, 1);
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
	if (waterb == 1) { //생성된 물풍선이 한 개일 경우
		Wballon[num].con = 1;
		num1 = num;
		PmovePlayer(num1, num, 1);
		if (waterb == 0) {
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

void printpopwater(int i, int num)
{
	if (map[Wballon[num].y - i][Wballon[num].x] != WALL) //물풍선 위쪽에 벽이 있는지 비교
	{
		if (Wballon[num].y - i > 0)
		{
			gotoxy(Wballon[num].x, Wballon[num].y - i);
			if (map[Wballon[num].y - i][Wballon[num].x] == PLAYER1) {
				printf("●");
				system("cls");
				end();

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
				system("cls");
				end();
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
				system("cls");
				end();
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
				system("cls");
				end();
			}
			else if (map[Wballon[num].y][Wballon[num].x + i] == WATERB)
				printf("○");
			else printf("▒");
		}
	}

}

void removewaterb(int num) {
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
					system("cls");
					end();
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
					system("cls");
					end();
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
					system("cls");
					end();
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
					system("cls");
					end();
				}
				else if (map[Wballon[num].y][Wballon[num].x + i] == WATERB)
					printf("○");
				else printf(" ");
			}
		}
	}
	map[Wballon[num].y][Wballon[num].x] = SPACE;
}

void tc(int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

void sa() {
	tc(3);
	gotoxy(18, 6);
	printf("■■■■■■■■■■■■■■■");
	gotoxy(18, 7);
	printf("■■■■■■■■■■■■■■■");
	tc(6);
	gotoxy(24, 8);
	printf("■■■");
	tc(3);
	gotoxy(23, 9);
	printf("■■■■■");
	gotoxy(20, 10);
	printf("■■■■■■■■■■■");
	gotoxy(18, 11);
	printf("■■■■■■■■■■■■■■■");
	gotoxy(17, 12);
	printf("■■■■■■■■■■■■■■■■■");
	gotoxy(16, 13);
	printf("■■■■■■■■■■■■■■■■■■■");
	tc(15);
	gotoxy(30, 13);
	printf("■■");
	tc(3);
	gotoxy(15, 14);
	printf("■■■■■■■■■■■■■■■■■■■■■");
	tc(15);
	gotoxy(31, 14);
	printf("■■");
	tc(3);
	gotoxy(14, 15);
	printf("■■■■■■■■■■■■■■■■■■■■■■■");
	tc(15);
	gotoxy(32, 15);
	printf("■■");
	tc(3);
	gotoxy(14, 16);
	printf("■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(13, 17);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(13, 18);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(13, 19);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(13, 20);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(13, 21);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(14, 22);
	printf("■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(14, 23);
	printf("■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(15, 24);
	printf("■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(16, 25);
	printf("■■■■■■■■■■■■■■■■■■■");
	gotoxy(17, 26);
	printf("■■■■■■■■■■■■■■■■■");
	gotoxy(18, 27);
	printf("■■■■■■■■■■■■■■■");
	gotoxy(20, 28);
	printf("■■■■■■■■■■■");
}

void end(){
	int i = 18;
	system("mode con cols=100 lines=51");
	gotoxy(16, i - 1);
	printf("■■■■■■■■■■■                     ■■■■■■■■■■■");
	gotoxy(12, i);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	printf("■                                               ■");
	gotoxy(11, i + 1);
	printf("■■                                               ■■");
	gotoxy(10, i + 2);
	printf("■■■                                               ■■■");
	gotoxy(9, i + 3);
	printf("■■■■                                               ■■■■");
	gotoxy(8, i + 4);
	printf("■■■■■                                               ■■■■■");
	gotoxy(7, i + 5);
	printf("■■■■■■                                               ■■■■■■");
	gotoxy(7, i + 6);
	printf(" ■■■■■                                                 ■■■■■");
	gotoxy(7, i + 7);
	printf("  ■■■■                                                   ■■■■");
	system("pause");
}