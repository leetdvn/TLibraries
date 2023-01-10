#include "TConfiguration.h"

TConfiguration::TConfiguration(QString path,bool newconfig)
{
	lCreator(toData(path), newconfig);
	qDebug() << "Q char param .\n";

}

TConfiguration::TConfiguration(const char* path,bool newconfig) { 
	
	Initial(path,newconfig);
}

TConfiguration::~TConfiguration()
{
	//VirtualFree(this,malloc(sizeof(ins)),(DWORD)"Free");
	
}

void TConfiguration::lCreator(const char* path, bool newconfig)
{

	_keyconfig = "TConfig";

	//new file config
	if (newconfig) {
		_data = new LeeDataCore(path);
		jsObject[_keyconfig] = folderlist;
	}
	QFile f(path);
	if (!f.exists()) { qDebug() << "no file wrong path file :" << path << endl; return;}

	_configfile = &f;
	_TConfigPath = path;

	// file config exists
	if(!newconfig) _data = new LeeDataCore(path);

	jsObject = _data->dFileJs2JsObject();
	folderlist = _data->dFilejs2QArray(_keyconfig);
	_content = _data->dFile2Char(path);


	//init data

}

QJsonObject TConfiguration::GetJSObject()
{
	return QJsonObject();
}

const char* TConfiguration::TGetConfigName(const char* configKey) const
{
	QFile f(_TConfigPath);
	if (!f.exists()) {
		qDebug() << "file does't exists" << endl;
		return nullptr;
	}

	for (auto v : folderlist)
	{
		QJsonObject obj = v.toObject();
		QString str = obj[configKey].toString();
		return toData(str);
	}


	return nullptr;
}

const char* TConfiguration::TGetConfigName(QString config) const
{
	const char* cStr = toData(config);
	return TGetConfigName(cStr);
}

void TConfiguration::TSetConfigName(const char* key, QString contents)
{
	QJsonArray arr;
	for (auto v : folderlist) {
		QJsonObject obj = v.toObject();
		obj[key] = contents;
		QJsonValue _value = obj;
		arr.append(obj);
	}
	jsObject[_keyconfig] = arr;
	_data->dSaveFile(jsObject);
	qDebug() << "count" << jsObject[_keyconfig] << endl;
}

void TConfiguration::TSetConfigName(const char* key, const char* contents)
{
	QString qstr = contents;
	TSetConfigName(key, contents);
}

void TConfiguration::TAddConfigName(QString& key) const
{
}

void TConfiguration::TAddConfigName(const char* key) const
{
}

const char* TConfiguration::toCData()
{
	return toData(_content);
}

QString TConfiguration::toQData()
{
	return _content;
}

