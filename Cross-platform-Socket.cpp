// Cross-platform-Socket.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <string>

#include "CSocket.h"

using namespace std;

void readMess(CSocket *socket)
{
//	cout << "\n read:" + socket.read(;

	char* buff = new char[1024];
	while (1)
	{
		memset(buff, 0, 1024);
		
		int ret = socket->read(buff,1024);
		if (ret <=0)
		{
			cout<<"ret <  0 ";
			break;
		}
		string out = "\n read: " + string(buff, ret)+"  long: "+std::to_string(ret);
		fputs(out.data(), stdout);
	//	cout << "\n read: " + string(buff, ret)+"  long: "+std::to_string(ret);
	}
	return;
}

int main()
{
    std::cout << "Hello World!\n"; 

   
	CSocket *s = new CSocket();
	s->connectHost("192.168.1.104", 1611);
	
	std::thread thread(readMess, s);

	string mess;
	while (1)
	{
		cout << "\n please enter mess ";
		cin >> mess;
		
		s->write(mess.data(), mess.length());

		string tmp = "\n send:" + mess;
		cout << tmp;
	}
	
}
