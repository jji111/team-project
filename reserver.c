#include <stdio.h>		// 표준 C라이브러리
#include <stdlib.h>	
#include <string.h>		// strcpy, atoi, memset
#include <Windows.h>	// 소켓, pause
#include <process.h>

#pragma comment(lib, "ws2_32.lib")	// 자동 라이브러리 넣기

#define BUF_SIZE 100
#define MAX_CLNT 4		// 최대 사용자(클라이언트)

unsigned WINAPI HandleClnt(void *arg);
void SendMsg(char *msg, int len);	// 클라이언트에서 
void ErrorHandling(char *msg);

// 매개 변수
int clntCnt = 0;
SOCKET clntSocks[MAX_CLNT];
HANDLE hMutex;

int main(int argc, char *argv[]) {
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSz;
	HANDLE hThread;
	printf("port를 입력해주세요 : ");
	char port[100] = { 0 };
	fgets(port, 100, stdin);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling((char*)"WSAStartup() Error");
	}

	hMutex = CreateMutex(NULL, FALSE, NULL);
	// CreateMutex: 원도우 중복 방지실행
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAdr, 0, sizeof(servAdr));	// servAdr의 NULL값으로 초기화
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(port));
	// htons: 네트워크 바이트 정렬 방식의 4바이트 데이터를 호스트 바이트 정렬 방식으로 변환

	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR) {
		ErrorHandling((char*)"bind() error");
	}
	if (listen(hServSock, 5) == SOCKET_ERROR) {
		ErrorHandling((char*)"listen() Error");
	}

	// 소켓 신호 받기
	while (1) {
		clntAdrSz = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);
		puts("클라이언트에서 메세지 받는 중: ");
		if (-1 == hClntSock)
			ErrorHandling((char*)"클라이언트 연결 수락 실패!");
		WaitForSingleObject(hMutex, INFINITE);
		clntSocks[clntCnt++] = hClntSock;
		ReleaseMutex(hMutex);	// 윈도우 중복방지 제거
		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClnt, (void*)&hClntSock, 0, NULL);
		printf("Connect client IP : %s\n", inet_ntoa(clntAdr.sin_addr));	// inet_ntoa: 네트워크 주소 반환
	}

	closesocket(hServSock);
	WSACleanup();
	system("pause");
	return 0;
}

unsigned WINAPI HandleClnt(void *arg) {
	SOCKET hClntSock = *((SOCKET*)arg);
	int strLen = 0, i;
	char msg[BUF_SIZE];

	while ((strLen = recv(hClntSock, msg, sizeof(msg), 0)) != 0) {
		SendMsg(msg, strLen);
		fputs(msg, stdout);
	}

	WaitForSingleObject(hMutex, INFINITE);

	for (i = 0; i < clntCnt; i++) {
		if (hClntSock == clntSocks[i]) {
			while (i++ < clntCnt - 1)
				clntSocks[i] = clntSocks[i + 1];
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

// 에러
void ErrorHandling(char *msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	system("pause");
	exit(1);
}
