#ifndef LEEFTPSVC_H
#define LEEFTPSVC_H

#pragma once
#include <Windows.h>
#include <iostream>
#include <Qt/QtCore/QFile>
//#include "LeeUtilities.h"
#include <ObjBase.h>      // include the base COM header
#include <Netlistmgr.h>
#include "lPublic.h"
// Instruct linker to link to the required COM libraries
#pragma comment(lib, "ole32.lib")

using namespace std;

class LeeFtp
{
public:
	explicit LeeFtp(const QString host,QString username,QString pw);
	~LeeFtp();
	virtual void __cdecl FtpSentFile(QString localFile, QString remoteFolder=NULL);
	virtual void __cdecl FtpDownloadFile(QString saveFolder, QString remoteFile);
	const char* urlInfo;
	QString userInfo;

private:
	HINTERNET FtpNet;
	HINTERNET netOpen;
};

#endif // !LEEFTPSVC_H
