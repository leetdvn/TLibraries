#ifndef LPUBLIC_H
#define LPUBLIC_H
#pragma once
#include <Windows.h>
#include <wininet.h>
#include <ObjBase.h>      // include the base COM header
#include <Netlistmgr.h>
#include "LeeContainer.h"
#include <QtCore/QString>
#include <iostream>
#include <QtNetwork/QNetWorkReply>
#include <QtNetwork/QNetWorkAccessManager>
#include <QtNetwork/QNetWorkRequest>
#include <QtNetwork/QNetWorkInterFace>
#include <QtCore/QVariant>
#include <QtCore/QJsonObject>
#include <QtCore/QJSonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonValue>
#include <QtCore/QEventLoop>
#include <QtCore/QDir>
#include <QtGui/QImage>
#include <QtWidgets/QMainWindow>
#include <QtDesigner/formbuilder.h>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QWidgetAction>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLabel>
#include <QtCore/QVariant>
#include <QtCore/QList>
#include <QtWidgets/QApplication>
#include <maya/MGlobal.h>
#include "LeeInfo.h"


#pragma comment(lib, "Wininet")
using namespace std;

#define MacId GetDomain();
#define ComputerId qgetenv("PCNAME")
#define UserId qgetenv("USERNAME")
#define IpAddr GetIp()

#ifdef LPUBLIC_H
#define TOOLNAME leeToolName;
#endif

#ifdef LEEINFO_H
#define COMMANDFOLDER basefolder + "/TCommand"
#endif

#define WIDGETACTION(...) TDirective(__VA__ARGS__)

//typedef QString(*TDisplayName)(QString);
//using DISPLAYNAME = QString(*)(QString);
struct pencil {
	pencil(QString str);
	QString toStr();
	QString inp;
};

void getPencil(struct pencil* arg) {
	arg = new pencil("new pencil");
	qDebug() << arg->toStr() << endl;
}

static QString basefolder =  "C:/Users/" + UserId + QString("/AppData/Local/TPicker Data");
static QString CommandPath = "C:/Users/LeePhan/Documents/GitHub/leePickerOPS/src/TCreateWorkspace.lee";
static QJsonArray MayaCmdList;

/// <summary>
/// check Internet connetion
/// </summary>
/// <returns></returns>
extern INTERNET_STATUS WINAPI IsConnectedToNet();

/// <summary>
/// Internet Is Connected..
/// </summary>
/// <returns></returns>
extern bool WINAPI isConnected();

/// <summary>
/// Convert QString to Const Char
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
extern const char* WINAPI toData(QString str);

/// <summary>
/// CHECk file exist
/// </summary>
/// <param name="filepath"></param>
/// <returns></returns>
extern bool WINAPI  FileEx(QString filepath);

/// <summary>
/// CHECK Qt Network is online
/// </summary>
/// <returns></returns>
extern bool WINAPI isQOnline();

/// <summary>
/// conver QString to LPCWSTR
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
extern LPCWSTR WINAPI toWData(QString str);

/// <summary>
/// Detach file path to end 
/// </summary>
/// <param name="inStr"></param>
/// <returns></returns>
extern QString WINAPI FileDetach(QString inStr);

/// <summary>
/// load file Qt Mainwindow /Widget .ui
/// </summary>
/// <param name="filepath"></param>
/// <returns></returns>
extern QWidget* WINAPI LoadUiFile(QString filepath);

/// <summary>
/// get Computer MAC id
/// </summary>
/// <returns></returns>
extern QString WINAPI GetDomain();

/// <summary>
/// get Computer Ip Address
/// </summary>
/// <returns></returns>
extern QString WINAPI GetIp();

/// <summary>
/// Open Windows Browser 
/// </summary>
/// <param name=" previous Folder"></param>
/// <returns></returns>
extern QString WINAPI BrowserImage(QString previous);

/// <summary>
/// QWidget Action add to tool bar
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="action"></param>
/// <param name="label"></param>
/// <param name="name"></param>
/// <returns></returns>
template<class T>
extern QWidgetAction* WINAPI TWidgetAction(void*& action, QString label = NULL, QString name = NULL);

/// <summary>
/// Convert Enum 2 const char*
/// </summary>
/// <param name="lApp"></param>
/// <returns></returns>
extern constexpr const char* WINAPI Cmd2Str(COMMANDAPP lApp);

extern QString WINAPI TDisplayName(QString Message);

#endif // !LPUBLIC_HPP