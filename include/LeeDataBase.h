#ifndef LEEDATABASE_H
#define LEEDATABASE_H
#pragma once

#include "lPublic.h"
#include <fstream>
#include <Bits.h>
#include <stdio.h>
#include <Windows.h>
#include <wininet.h>
#include "LeeFtpsvc.h"

#pragma comment(lib, "Wininet")
using namespace std;

#ifdef _LEELIB
#    define EXPORT_API  __declspec(dllexport)
#else
#    define EXPORT_API __declspec(dllimport)
#endif

class EXPORT_API LeeDataCore
{
public:
	explicit LeeDataCore(QString filepath);
	LeeDataCore(const char* filepath=nullptr);
	/// <summary>
	/// download data from url and save to file
	/// only format .json and png
	/// </summary>
	/// <param name="url"></param>
	/// <param name="fileSave"></param>
	virtual void dURL2FILE(QString url, QString fileSave) const;
	/// <summary>
	/// save data params const Char
	/// </summary>
	/// <param name="path"></param>
	/// <param name="content"></param>
	virtual void dSaveFile(const char* content, bool isJs = false);
	/// <summary>
	/// Save File type QString
	/// </summary>
	/// <param name="path"></param>
	/// <param name="content"></param>
	virtual void dSaveFile(QString content);
	/// <summary>
	/// Save file type QByte
	/// </summary>
	/// <param name="path"></param>
	/// <param name="content"></param>
	virtual void dSaveFile(QByteArray content);
	/// <summary>
	/// Save param Json
	/// </summary>
	/// <param name="path"></param>
	/// <param name="content"></param>
	virtual void dSaveFile(QJsonObject content);
	/// <summary>
	/// get data File convert to QStringList
	/// </summary>
	/// <param name="path"></param>
	/// <param name="key"></param>
	/// <returns></returns>
	virtual QStringList dFileJs2Array(const char* key = NULL);
	/// <summary>
	/// Get Data From File
	/// return type const char* 
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	virtual const char* dFile2Char(QString path = NULL);
	/// <summary>
	/// Get Data From File convert to JsObject
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	virtual QJsonObject dFileJs2JsObject(QString ifile=NULL);
#pragma region Encrypt file with passwork key number type int
	/// <summary>
	/// Encryptdata with key number type int
	/// </summary>
	virtual QString dEncryptionData(QString filepath,int key,bool isdEncrypt=NULL);
	/// <summary>
	/// deEncryption data with key number type int
	/// </summary>
	virtual QString dDeEncryptionData(QString filepath,int key) { return dEncryptionData(filepath,key,true); }
	/// <summary>
	/// deEncryption data with key number type int
	/// </summary>
	/// <param name="filepath"></param>
	/// <param name="key"></param>
	/// <returns>
	/// return data type const char*
	/// </returns>
	virtual const char* dDeEncryptionToChar(QString filepath, int key);

	virtual const char* dEncrypt(QString content);

	/// <summary>
	/// save command application
	/// </summary>
	/// <param name="ifile"></param>
	/// <param name="lApp"></param>
	/// <param name="pKey"></param>
	virtual void dSaveFileCommand(QString ifile, COMMANDAPP lApp,QString opKey, QString ipNewKey = NULL);

	QString previousFile=NULL;
	QString currentFile = NULL;
#pragma endregion 
	~LeeDataCore()
	{
	}

private:
	QString dCopy(QString filepath);
	void Initialize(const char* filepath);
	char c;

};


#endif