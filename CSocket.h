#pragma once
#include "CrossPlatformStruct.h"
#include <iostream>

using namespace std;
class CSocket
{
public:
	CSocket();
	virtual ~CSocket();
	virtual string readAll();
	virtual int read(char* data, int size);
	virtual int write(const char* data, int size);
	bool connectHost(const string &host, const int &port);
	void init();
private:
	//member:
	CrossPlatformStruct socket;

	//function: 
	virtual void showLog(const string &mess);
};

