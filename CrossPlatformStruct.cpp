
#include "CrossPlatformStruct.h"


CrossPlatformStruct::CrossPlatformStruct()
{
	init();
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}


CrossPlatformStruct::~CrossPlatformStruct()
{
}

bool CrossPlatformStruct::connectToHost(const string &host, const int &port)
{
	//	int ip = iPToValue(host);
	char ip[128];
	memcpy(ip, host.data(), host.length());
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(port);
	in_addr in4;
	inet_pton(AF_INET, ip, &in4);
	serAddr.sin_addr = in4;

	if (connect(client, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		showLog("connect error !  ");
		#ifdef   _WIN32
						int err = GetLastError();
		char buf[128];
		_itoa_s(err, buf,128, 10);
		showLog(buf);
		closesocket(client);
		#endif		

		return false;
	}
	return true;
}

void CrossPlatformStruct::disconnected()
{
#ifdef _WIN32
	closesocket(client);
#endif // _WIN32

#ifdef __linux__
		close(client);
		close(accepClient);
#endif
}

void CrossPlatformStruct::init()
{
#ifdef _WIN32
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		showLog("init fail");
		return;
	}
#endif // _WIN32

#ifdef __linux__

#endif
}

int CrossPlatformStruct::iPToValue(const string& strIP)
{
	int a[4];
	string IP = strIP;
	string strTemp;
	size_t pos;
	size_t i = 3;

	do
	{
		pos = IP.find(".");

		if (pos != string::npos)
		{
			strTemp = IP.substr(0, pos);
			a[i] = atoi(strTemp.c_str());
			i--;
			IP.erase(0, pos + 1);
		}
		else
		{
			strTemp = IP;
			a[i] = atoi(strTemp.c_str());
			break;
		}

	} while (1);

	int nResult = (a[3] << 24) + (a[2] << 16) + (a[1] << 8) + a[0];
	return nResult;
}

int CrossPlatformStruct::read(char * data, int size)
{
	int ret = 0;
#ifdef _WIN32
	ret = recv(client, data, size, 0);
#endif // _WIN32

#ifdef __linux__
		ret = recv(client,data,size,0);
#endif
	return ret;
}

int CrossPlatformStruct::write(const char * data, int size)
{
	int ret = 0;
#ifdef _WIN32
	ret = send(client, data, size, 0);
#endif // _WIN32

#ifdef __linux__
	ret = 	send(client, data, size,0);
#endif
	return ret;
}

#ifdef _WIN32
string CrossPlatformStruct::getError()
{
	
	int err = GetLastError();
	char buf[128];
	_itoa_s(err, buf,128, 10);
	return buf;
}
#endif

void CrossPlatformStruct::showLog(const string & log)
{
	cout << "\n" + log + "\n";
}

