// Win32SocketPrac.cpp : 定义控制台应用程序的入口点。
// project description : A IPV4 Winsock V2.1 Based TCP client demo
// Destination IP      : 192.168.0.107
// Destination Port    : 8990
// Network family      : AF_INET(IPV4)
// Socket type         : SOCK_STREAM(bytes stream)
// Protocol            : TCP

#include "stdafx.h"
#include "WinSock2.h"
#include "stdlib.h"

// link with Ws2_32.lib
#pragma comment(lib,"Ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	SOCKET Sock_0 = INVALID_SOCKET;

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	sockaddr_in SocketServiceAddr;
	int connect_err;
	SocketServiceAddr.sin_family = AF_INET;
	SocketServiceAddr.sin_addr.s_addr = inet_addr("192.168.0.107");
	SocketServiceAddr.sin_port = htons(8990);

	char str[100] = { 0 };
	char res[100] = { 0 };
	int send_err;
	int rece_err;

	wVersionRequested = MAKEWORD(2, 1);
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0)
	{
		printf("WSAStartup faild!\n");
		return 1;
	}

	Sock_0 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Sock_0 != INVALID_SOCKET)
	{
		printf("Socket creat success!\n");
	}
	else
	{
		printf("Socket creat failed because some problems\n");
		return 1;
	}

	connect_err = connect(Sock_0, (sockaddr *)&SocketServiceAddr, sizeof(SocketServiceAddr));
	if (connect_err == SOCKET_ERROR)
	{
		printf("connect error SOCKET_ERROR No.%d\n", connect_err);
		Sleep(3000);
		closesocket(Sock_0);
		WSACleanup();
		return 1;
	}
	else
	{
		printf("connect success!\n");
	}
	printf("input string to send the server\n");
	scanf_s("%s", str, 100);
	send_err = send(Sock_0, str, strlen(str), 0);
	if (send_err == SOCKET_ERROR)
	{
		printf("Socket send stream error No.%d\n", send_err);
		Sleep(1500);
		closesocket(Sock_0);
		WSACleanup();
	}
	else
	{
		printf("Send string success!\n Bytes count:%d\n", strlen(str));
		Sleep(1500);
	}
	
	printf("waiting for received some message...\n");
	rece_err = recv(Sock_0, res, 5, 0);
	printf("Received str success!\n");
	printf("Received bytes count: 5\n");
	printf("Received Str:%s\n", res);
	printf("Input anything to close the socket.\n");
	scanf_s("%d");
	closesocket(Sock_0);
	WSACleanup();

	return 0;
}

