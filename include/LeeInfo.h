#ifndef LEEINFO_H
#define LEEINFO_H
#pragma once

#include "lPublic.h"
#include <iostream>
#include <Windows.h>
#include <lmcons.h>
#include <stdlib.h>

// QT incluce
#include <QtNetwork/QHostInfo>
#include <QtCore/QDir>
#include <QtNetwork/QNetWorkInterFace>
#include "LeeDataBase.h"
// #include <windows.data.json.h>

using namespace std;

#ifdef _LEELIB
#    define EXPORT_API  __declspec(dllexport)
#else
#    define EXPORT_API __declspec(dllimport)
#endif

class EXPORT_API LeeInfo
{
public:
	LeeInfo();
	~LeeInfo(){}
	static const char* MACID;
	static const char* User;
	static const char* Host;
	static const char* IpAddress;
	QString clientInfo;
	void InitializeLocation();

private:
	const char* GetUser();
	const char* GetComputerId();
	void saveInfo();
};


#endif // !LEEINFO_H
