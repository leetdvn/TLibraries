#include "LeeInfo.h"

const char* LeeInfo::Host;
const char* LeeInfo::MACID;
const char* LeeInfo::User;
const char* LeeInfo::IpAddress;

LeeInfo::LeeInfo()
{
	//MACID = GetDomain();
	Host = qgetenv("PCNAME");// GetComputerId(); //QHostInfo::localHostName().toLocal8Bit();
	User = qgetenv("USERNAME");
	QString ip = GetIp();
	IpAddress = ip.toLocal8Bit();
	clientInfo =  basefolder+ "/ClientInfo.lee";

	qDebug() << "PC: " + QHostInfo::localHostName();
	qDebug() << "USER: " + qgetenv("USERNAME");
	qDebug() << "MAC: " + GetDomain();
	qDebug() << "IP: " + GetIp();
	saveInfo();
	InitializeLocation();
	
}

void LeeInfo::InitializeLocation()
{
	LeeDataCore* data = new LeeDataCore("C:/Users/LeePhan/Documents/GitHub/leePickerOPS/src/TCreateWorkspace.lee");
	if (MayaCmdList.count() <= 0) {
		/*QJsonObject obj = data->dFileJs2JsObject(data->currentFile);
		QJsonArray arr = obj["Maya"].toArray();
		for(auto str : arr) {
			QJsonObject cmd = str.toObject();
			qDebug() << cmd["CreateWorkspace"].toString() << endl;

		}*/
		
	}
	data->dSaveFileCommand("C:/Users/LeePhan/Documents/leePhan/leePhan/Scripts/MEL/newCmd.lee",APPINFO::LMAYA,"Create");
	//qDebug() << str << data->dFileJs2JsObject(data->currentFile) <<  endl;


	if (!QDir(basefolder).exists()) QDir().mkdir(basefolder);
	if (!QDir(COMMANDFOLDER).exists()) QDir().mkdir(COMMANDFOLDER);


}

const char* LeeInfo::GetUser()
{
	TCHAR  infoBuf[UNLEN + 1];
	DWORD  bufCharCount = UNLEN + 1;
	GetUserName(infoBuf, &bufCharCount);
	wstring wstr = &infoBuf[0];
	string str(wstr.begin(), wstr.end());
	const char* resutl= str.c_str();
	return resutl;
}

const char* LeeInfo::GetComputerId()
{
	
	return toData(QHostInfo::localHostName());
}

void LeeInfo::saveInfo()
{
	QString content;
	QJsonObject obj;
	QJsonArray arr;
	obj["MAC"] = GetDomain();
	obj["PC"] = QHostInfo::localHostName();
	obj["USER"] = qgetenv("USERNAME").data();
	obj["IP"] = GetIp();
	QString domain = QHostInfo::localDomainName();
	if (!domain.isEmpty() || !domain.isNull()|| domain !="")
		obj["Domain"] = QHostInfo::localDomainName();
	arr.append(obj);
	QJsonObject result;
	result["Client"] = arr;


	//QFile f(clientInfo);
	//if (f.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
	//{
	//	f.write(QJsonDocument(result).toJson());
	//}
	LeeDataCore* data = new LeeDataCore(clientInfo);
	data->dSaveFile(result);
}
