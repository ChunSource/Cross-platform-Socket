#pragma once

#include <iostream>
#include <string>
#include <string.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")  
#endif // _WIN32

#ifdef __linux__

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h> //sockaddr_in
#include<arpa/inet.h> //ip address turn
#include <unistd.h>    //close socket
#endif // __linux__

#define SOCKET_ERROR -1

using namespace std;

class CrossPlatformStruct
{
public:
	CrossPlatformStruct();
	~CrossPlatformStruct();
	bool connectToHost(const string &host, const int &port);
	void disconnected();
	void init();

	int read(char*data, int size);	   //接收数据
	int write(const char* data, int size);   //发送数据

	#ifdef _WIN32
	string getError();
	#endif
	
private:
	//member:

#ifdef _WIN32
	SOCKET client;  //socket对象
	sockaddr_in serAddr;  //ip地址
#endif // _WIN32

#ifdef __linux__
		int client = 0;
		int accepClient = 0;
		struct sockaddr_in serAddr; 
#endif
	//function:
	int iPToValue(const string &host); //没用的函数
	void showLog(const string &log);   //打印信息罢了
};

