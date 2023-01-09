#include "LeeFtpsvc.h"

LeeFtp::LeeFtp(QString host, QString username, QString pw)
{
	//QFile* file = new QFile("test.txt");
	urlInfo = toData(host);
	userInfo = username;
	LPCWSTR whost = toWData(host); // L"20.204.10.27";
	LPCWSTR wuser = toWData(username);
	LPCWSTR passwork = toWData(pw);
	netOpen = InternetOpen(0, INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0);
	FtpNet = InternetConnect(netOpen, whost, INTERNET_DEFAULT_FTP_PORT,
		wuser, passwork, INTERNET_SERVICE_FTP, 0, 0);
	printf("connecting.. %s\n", toData(host));
	printf("username: %s\n", toData(username));
	QString _pw;
	for (auto s : pw)
		_pw += "*";
	printf("passwork: %s\n", toData(_pw));
}

LeeFtp::~LeeFtp()
{

}

void LeeFtp::FtpSentFile(QString localFile,QString remoteFolder)
{
	if (!isConnected()) {
		printf("error connection fail..\n");
		//return;
	}
	if (userInfo.isEmpty() || userInfo.isNull() || userInfo == "") {
		printf("error username ivalid..\n");
		//return;
	}
	if (!remoteFolder.isEmpty() || !remoteFolder.isNull() || remoteFolder !="") {
		if (!remoteFolder.endsWith("\\") || !remoteFolder.endsWith("/"))
			remoteFolder += "/";
	}
	else { remoteFolder = "./"; }
	
	QString n = remoteFolder + FileDetach(localFile);
	LPCWSTR wlocalFile = toWData(localFile);
	LPCWSTR wsent = toWData(n);//  L"/fileSending.txt";

	if (FtpSetCurrentDirectory(FtpNet, L"./")) {
		if (!FtpPutFile(FtpNet, wlocalFile, wsent, FTP_TRANSFER_TYPE_BINARY, 0))
		{
			qDebug() << "FAIL!" << n << endl;
			qDebug() << GetLastError() << endl;
		}
		else
		{
			qDebug() << "file sent to host ! " << localFile << endl;
			qDebug() << "file receive from client ! " << n << endl;
		}
	}

}

void LeeFtp::FtpDownloadFile(QString saveFolder,QString remoteFile)
{

	if (!isConnected()) {
		return;
	}
	if (userInfo.isEmpty() || userInfo.isNull() || userInfo == "") {
		return;
	}
	QString midle;
	if (!saveFolder.endsWith("\\") || !saveFolder.endsWith("/"))
		midle = "/./";
	LPCWSTR wsavefile = toWData(saveFolder + midle + remoteFile);
	LPCWSTR wFptFile = toWData(("./"+remoteFile));//  L"/fileSending.txt";

	if (!FtpGetFile(FtpNet, wFptFile, wsavefile, false, INTERNET_SERVICE_FTP, 0, 0))
	{
		qDebug() << "FAIL!" << endl;
		qDebug() << GetLastError() << endl;
	}
	else
	{
		qDebug() << "file downloaded ! : " << wsavefile;
	}

}

