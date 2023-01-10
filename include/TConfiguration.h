#pragma once
#ifndef TCONFIGURATION_H
#define TCONFIGURATION_H

#include <QtCore/QFile>
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <lPublic.h>
#include <LeeDataBase.h>

//const const char* configtempPath = "C:\\Users\\LeePhan\\Documents\\leePhan\\leePhan\\Scripts\\MEL\\TConfigurations.json";

class TConfiguration
{
public:
	explicit TConfiguration(QString path,bool newconfig =0);
	explicit TConfiguration(const char* path, bool newconfig =0);
	~TConfiguration();

	/// <summary>
	/// get Config name
	/// </summary>
	/// <param name="input key"></param>
	/// <returns></returns>
	const char* TGetConfigName(const char* configkey) const;
	const char* TGetConfigName(QString configkey) const;

	/// <summary>
	/// set config
	/// </summary>
	/// <param name="key"></param>
	void TSetConfigName(const char* key, QString contents) ;

	void TSetConfigName(const char* key, const char* contents);

	/// <summary>
	/// add new config
	/// </summary>
	/// <param name="input key"></param>
	void TAddConfigName(QString &key) const;
	void TAddConfigName(const char* key) const;
	//----------------------------------------
	//void operator=(const TConfiguration&);
	const char* toCData();
	QString toQData();
	QJsonArray folderlist;
	QJsonObject jsObject;

private:
	const char* _TConfigPath;
	QFile *_configfile;
	QString _content;
	const char* _keyconfig;
	/// <summary>
	/// init file
	/// </summary>
	/// <param name="path"></param>
	/// <param name="newconfig"></param>
	void lCreator(const char* path, bool newconfig);

	QJsonObject GetJSObject();
	LeeDataCore* _data;


};

#endif // !TCONFIGURATION_H
