
#include "CSocket.h"


CSocket::CSocket()
{
		cout<<"start socket";
}

CSocket::~CSocket()
{
}

string CSocket::readAll()
{

	return string();
}

int CSocket::read(char * data, int size)
{
	int ret = socket.read(data, size);
	if (ret == SOCKET_ERROR)
	{
		#ifdef _WIN32
		showLog(socket.getError());    //linux展示还不知道怎么获取最近的错误
		#endif
	}
	return ret;
}

int CSocket::write(const char* data, int size)
{
	int ret = socket.write(data, size);
	if (ret == SOCKET_ERROR)
	{
		#ifdef _WIN32
		showLog(socket.getError());    //linux展示还不知道怎么获取最近的错误
		#endif
	}
	return ret;
}

bool CSocket::connectHost(const string &host, const int &port)
{
	socket.connectToHost(host, port);
	return false;
}

void CSocket::init()
{

}

void CSocket::showLog(const string &mess)
{
	cout << "\n" + mess + "\n";
}
