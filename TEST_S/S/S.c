#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib") 

#define BUF_SIZE 100 // 채팅 내용 사이즈
#define MAX_CLNT 4 // 클라이언트 max
#define _CRT_SECURE_NO_WARNINGS

unsigned WINAPI HandleClnt(void *arg); // 값 받기
void SendMsg(char *msg, int len); //보내기
void ErrorHandling(char *msg); //error 출력

int clntCnt = 0; //클라이언트 갯수 새기
SOCKET clntSocks[MAX_CLNT];
HANDLE hMutex;
	
char player1;
char player2;
int maxpl = 2;

int main(int argc, char *argv[]) {
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSz;
	HANDLE hThread;
	printf("port를 입력해주세요 : ");
	char port[100] = { 0, };
	int strLen = 0, i;
	char msg[BUF_SIZE];
	gets(port);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() Error");
	}

	hMutex = CreateMutex(NULL, FALSE, NULL);
	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(port));

	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR) {
		ErrorHandling("bind() error");
	}
	if (listen(hServSock, 5) == SOCKET_ERROR) {
		ErrorHandling("listen() Error");
	}

	while (1) {
		clntAdrSz = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);

		WaitForSingleObject(hMutex, INFINITE);
		clntSocks[clntCnt++] = hClntSock;
		ReleaseMutex(hMutex);
		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClnt, (void*)&hClntSock, 0, NULL);
		printf("Connect client IP : %s \n", inet_ntoa(clntAdr.sin_addr));

		if (clntCnt > maxpl) {
			printf("최대 인원은 %d 명이 입니다. 사용자가 너무 많아 서버를 종료합니다.", maxpl);
			closesocket(hServSock);
			WSACleanup();
			system("pause");
			return 0;
		}
	}

	closesocket(hServSock);
	WSACleanup();
	system("pause");
	return 0;
}

unsigned WINAPI HandleClnt(void *arg) {
	SOCKET hClntSock = *((SOCKET*)arg);
	int strLen = 0, i;
	while (1) {
		char msg[BUF_SIZE] = { 0, };
		if ((strLen = recv(hClntSock, msg, sizeof(msg), 0)) != 0) {
			if (strLen == -1) {
				system("pause");
				return 0;
			}
			SendMsg(msg, strLen);
			printf("%s\n", msg);
		}
	}

	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i < clntCnt; i++) {
		if (hClntSock == clntSocks[i]) {
			while (i++ < clntCnt - 1) {
				clntSocks[i] = clntSocks[i + 1];
			}
			break;
		}
	}
	clntCnt--;
	ReleaseMutex(hMutex);
	closesocket(hClntSock);
	return 0;
}

void SendMsg(char *msg, int len) {
	int i;
	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i < clntCnt; i++) {
		send(clntSocks[i], msg, len, 0);
	}
	ReleaseMutex(hMutex);
}

void ErrorHandling(char *msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	system("pause");
	exit(1);
}