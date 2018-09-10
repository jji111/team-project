/*
 * 소켓 프로그램의 흐름
 * 윈속 초기화 -> 소켓생성 -> bind -> listen -> accept -> 소켓해제 -> 윈속 종료
 *							      데이터 통신 
 */
#include <stdio.h>		// C언어 헤더파일
#include <Windows.h>	// 원도우 소켓과인터넷 주소 생성 / 원속 초기화 

#pragma comment(lib, "ws2_32.lib")	// ws2_32.lib 링커 : 시스템과 이 서버를 연결한다.(? 라고 이해하면 된다)
// lib: 동적 링크 라이브러리

int main(int argc, char *argv[])
{
	// 원속 초기화
	WSADATA wsaData;	// 소켓프로그램 초기화 선언 구조체

	SOCKET sock;	// 서버 구조체
	struct sockaddr_in sockinfo;	// 서버소켓 주소 구조체 선언

	// 클라이언트 소켓 함수
	SOCKET clientsock;
	struct sockaddr_in clientinfo;
	int clientsize;
	char message[] = "success";

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)	// 초기화 확인
	{
		printf("소켓 초기화 에러!\n");
		return -2;	// 에러 발생했으나 구체적으로 무엇이다를 나타냄
	}

	// 소켓 생성
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// 소켓 선언
	if (sock == INVALID_SOCKET)	// INVALID_SOCKET은 에러코드 값을 의미한다.
	{
		printf("소켓 생성 실패!\n");
		return -2;
	}

	sockinfo.sin_family = AF_INET;	// 주소 체계 정보 넣기
	sockinfo.sin_port = htons(1234);	// 초트 번호를 저정
	sockinfo.sin_addr.s_addr = htonl(INADDR_ANY);	//	 IP 주소를 지정하는 부분이다 서버 입장에서는 모든 인터넷 주소로 클라이언트를 대기 해야 한다. 
	// INADDR_ANY 라는 0.0.0.0 주소를 사용하는 것

	// bind원형: bind(Int bind ( 소켓 값 , (SOCKADDR*)&소켓주소구조체 저장값 , sizeof(소켓주소구조체이름) )
	if (bind(sock, (SOCKADDR*)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR)	// 소켓 서버 프로그램	SOCKET_ERROR
	{
		printf("bind 실패!\n");
		return -2;
	}

	// 데이터 통신 함수: listen, listener_d: 소켓 핸들 값
	if (listen(sock, 5) == SOCKET_ERROR)
	{
		printf("대기열 실패!\n");
		return -2;
	}

	clientsize = sizeof(clientinfo);	// 사이즈 값 저장
	// 원형: SOCKET accept ( 서버 소켓 , (SOCKADDR*)&클라이언트주소값, &클라이언트 주소값 사이즈 );
	printf("클라이언트로부터 접속을 기다리고 있습니다...\n");
	clientsock = accept(sock, (SOCKADDR*)&clientinfo, &clientsize);	// accept함수: 서버 프로그램 안에 클라이언트 연결 소켓

	if (clientsock == INVALID_SOCKET)	// 확인
	{
		printf("클라이언트 소켓 연결 실패!\n");
		return -2;
	}

	send(clientsock, message, sizeof(message), 0);
	// 문자 하나를 전송 하고 프로그램을 종료하는 것 까지 진행하는 함수

	if (connect(&clientinfo, (SOCKADDR*)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR)	// 클라이언트와 연결
		puts("소켓프로그램과 연결 실패!");

	int strlen;
	strlen = recv(clientsock, message, sizeof(message - 1), 0);		// 메세지 수신하여 저장하는 함수

	if (strlen == -1)	// 확인
		puts("메세지 수신 실패!");

	printf("Server: %d\n", message);	// 출력

	closesocket(sock);	// 소켓함수 해제
	closesocket(clientsock);	// 클라이언트 소켓 해제
	WSACleanup();	// 원속 종료
	return 0;
}
