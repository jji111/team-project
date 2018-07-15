#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include "cursor.h"
#include "start.h"

#pragma comment(lib, "ws2_32.lib")	

#define BUF_SIZE 100
#define NAME_SIZE 20

char recX;
char recY;
char name01[BUF_SIZE];
int count = 0;
int recspac = 1;
int number = 5;
int bx = 0;
int by = 0;
int x = 0, y = 0;

unsigned WINAPI SendMsg(void *arg);
unsigned WINAPI RecvMsg(void *arg);
unsigned WINAPI input(void *arg);
void ErrorHandling(char *arg); //ok?


char name[NAME_SIZE] = { 0, };
char msg[BUF_SIZE] = { 0, };

int plx = 0;
int ply = 0;
int space = 1;
int waterb1 = 0;
int waterb2 = 0;
int pum = 0;

int main() {
	int num = 0;

	removeCursor();


	WSADATA wsaData;
	SOCKET hSock;
	SOCKADDR_IN servAdr;
	HANDLE hSndThread, hRcvThread, inputThread;
	char port[100] = { 0, };
	char ip[100] = { 0, };
	printf("ip를 입력해주세요 : ");
	//gets(ip);
	strcpy(ip, "127.0.0.1");
	printf("port를 입력해주세요 : ");
	strcpy(port, "1234");
	//gets(port);
	printf("이름을 입력해주세요 : ");
	gets(name);

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

	start();
	player = pchoose();
	system("mode con cols=80 lines=30");
	printMap();
	hSndThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&hSock, 0, NULL);
	hRcvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&hSock, 0, NULL); // 멍미....?

	while (life != 0) {
		num = PlayerInput(num);
	}
	WaitForSingleObject(hSndThread, INFINITE);
	WaitForSingleObject(hRcvThread, INFINITE);

	closesocket(hSock);
	WSACleanup();
	system("cls");
	printf("뒤졌습니다 ㅎ\n");
	return 0;
}

void moveplayer(int dx, int dy, int n)   //플레이어 이동 함수
{
	if (player == 1) {
		if (map[dy][dx] == SPACE) //이동할 공간에 아무것도 없는지 비교
		{
			gotoxy(dx, dy);
			if (n == 1) {
				player2X = dx;
				player2Y = dy;
				gotoxy(player2X, player2Y);
				printf("▽"); //이동 좌표에 플레이어 출력
				map[player2Y][player2X] = PLAYER2; //이동 좌표 공간에 PLAYER1 저장
			}
			else
			{
				player2X = dx;
				player2Y = dy;
				gotoxy(player2X, player2Y);
				printf("▽"); //이동 좌표에 플레이어 출력
				map[player2Y][player2X] = PLAYER2; //이동 좌표 공간에 PLAYER1 저장
			}
		}
	}
	else {
		if (map[dy][dx] == SPACE) //이동할 공간에 아무것도 없는지 비교
		{
			gotoxy(dx, dy);
			if (n == 1) {
				player1X = dx;
				player1Y = dy;
				gotoxy(player1X, player1Y);
				printf("▲"); //이동 좌표에 플레이어 출력
				map[player1Y][player1X] = PLAYER1; //이동 좌표 공간에 PLAYER1 저장
			}
			else
			{
				player1X = dx;
				player1Y = dy;
				gotoxy(player1X, player1Y);
				printf("▲"); //이동 좌표에 플레이어 출력
				map[player1Y][player1X] = PLAYER1; //이동 좌표 공간에 PLAYER1 저장
			}
		}
	}
}

unsigned WINAPI SendMsg(void *arg) {
	SOCKET hSock = *((SOCKET*)arg);
	while (1) {
		if (count == 1)
		{
			char nameMsg[BUF_SIZE] = { 0, };
			if (player == 1) {
				sprintf(nameMsg, "%s.%d/%d/%d", name, player1Y, player1X, space);
			}
			else {
				sprintf(nameMsg, "%s.%d/%d/%d", name, player2Y, player2X, space);
			}
			send(hSock, nameMsg, strlen(nameMsg), 0);
			space = 1;
			count = 0;
			pum = 0;
			Sleep(10);
		}
	}
}

unsigned WINAPI RecvMsg(void *arg) {
	int hSock = *((SOCKET*)arg);
	int strLen;
	while (1) {
		char *ptr = NULL;
		char nameMsg[BUF_SIZE] = { 0, };
		char recvX[BUF_SIZE] = { 0, };
		char recvY[BUF_SIZE] = { 0, };
		char spacebar[BUF_SIZE] = { 0, };
		char pumb[BUF_SIZE] = { 0, };
		char numb[BUF_SIZE] = { 0, };
		strLen = recv(hSock, nameMsg, BUF_SIZE - 1, 0);
		ptr = strtok(nameMsg, ".");
		strcpy(name01, ptr);
		ptr = strtok(NULL, "/");
		strcpy(recvY, ptr);
		ptr = strtok(NULL, "/");
		strcpy(recvX, ptr);
		ptr = strtok(NULL, "/");
		strcpy(spacebar, ptr);
		recspac = atoi(spacebar);
		if (strcmp(name, name01)) {
			if (player == 1) {
				if (recspac == 1) {
					gotoxy(player2X, player2Y);
					printf("  "); //원래 좌표에 공백 출력
					map[player2Y][player2X] = SPACE; //원래 좌표 공간에 SPACE 저장
				}
				else if (recspac == 0) {
					gotoxy(player2X, player2Y);
					printf("○"); //원래 좌표에 물풍선 출력
					map[player2Y][player2X] = WATERB; //원래 좌표 공간에 WATERB 저장
				}
			}
			else if (player == 2) {
				if (recspac == 1) {
					gotoxy(player1X, player1Y);
					printf("  "); //원래 좌표에 공백 출력
					map[player1Y][player1X] = SPACE; //원래 좌표 공간에 SPACE 저장
				}
				else if (recspac == 0) {
					gotoxy(player1X, player1Y);
					printf("○"); //원래 좌표에 물풍선 출력
					map[player1Y][player1X] = WATERB; //원래 좌표 공간에 WATERB 저장
				}
			}
			/*else if (atoi(pumb) == 1) {
			recievepopwater(bX, bY);
			}*/
		}
		moveplayer(atoi(recvX), atoi(recvY), recspac);
	}
}

void ErrorHandling(char *msg) {
	puts(msg);
	putc('\n', stderr);
	system("pause");
	exit(1);
}
