#include "LeeDataBase.h"



LeeDataCore::LeeDataCore(QString filepath)
{
	Initialize(toData(filepath));
	qDebug() << "init 1" << filepath << endl;
}

LeeDataCore::LeeDataCore(const char* filepath)
{
	Initialize(filepath);
	qDebug() << "init : " << filepath << endl;
}
void LeeDataCore::Initialize(const char* file)
{
	if (file == nullptr) return;
	currentFile = file;
	c = '\0';
	QFile f(file);
	if (f.exists()) return;
	f.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
	if (f.isOpen()) f.close();
	
}

#pragma region database file json and url
void LeeDataCore::dURL2FILE(QString url, QString fileSave) const
{
	QEventLoop loop;
	QNetworkAccessManager manager;
	QNetworkRequest* req = new QNetworkRequest(QUrl(url));
	QNetworkReply* reply = manager.get(*req);
	QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();
	QByteArray content = reply->readAll();
	std::printf("# leeLog : %s\n", toData(fileSave));

	if (url.endsWith(".json"))
	{
		QFile file(fileSave);
		if (file.open(QIODevice::WriteOnly)) {
			file.write(content);
			file.close();
		}
	}
	else
	{
		QImage* img2 = new QImage();
		img2->loadFromData(content);
		if (!img2->isNull())\
		{
			img2->save(fileSave);
		}
	}

}

void LeeDataCore::dSaveFile(const char* content, bool isJs)
{
	if (currentFile.isEmpty() || currentFile.isNull() || currentFile=="") return;
	QFile f(currentFile);
	if (f.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
		f.write(content);
	}
}

void LeeDataCore::dSaveFile(QJsonObject content)
{
	if (currentFile.isEmpty() || currentFile.isNull() || currentFile =="") return;
	QFile f(currentFile);
	if (f.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
		f.write(QJsonDocument(content).toJson());
	}

}

QStringList LeeDataCore::dFileJs2Array(const char* key)
{
	QStringList result;
	QJsonArray arr = dFilejs2QArray(key);
	foreach(const QJsonValue & v, arr) {
		QString str = v.toString();
		result.append(str);
	}
	return result;
}

QJsonArray LeeDataCore::dFilejs2QArray(const char* arrKey)
{
	QJsonArray result;
	QFile f(currentFile);
	if (f.exists()) {
		if (f.open(QFileDevice::ReadOnly)) {
			QByteArray data = f.readAll();
			QJsonObject obj = QJsonDocument::fromJson(data).object();
			result = obj[arrKey].toArray();
			return result;
		}
	}
	return result;

}

const char* LeeDataCore::dFile2Char(QString path)
{
	const char* result = NULL;
	QFile f(path);
	if (f.exists()) {
		if (f.open(QFileDevice::ReadOnly)) {
			QByteArray data = f.readAll();
			return result = data.constData();
		}
	}
	return result;

}

QJsonObject LeeDataCore::dFileJs2JsObject(QString ifile)
{
	QString mFile = FileEx(ifile) ? ifile : currentFile;
	qDebug() << "file : " << mFile << endl;

	QFile f(mFile);
	if (f.exists()) {
		if (f.open(QFileDevice::ReadOnly)) {
			QString data = f.readAll();
			qDebug() << "data : " << data << endl;
			QJsonObject result= QJsonDocument::fromJson(data.toUtf8()).object();
			return result;
		}
	}
	return QJsonObject();
}

void LeeDataCore::dSaveFile(QString content)
{
	if (currentFile.isEmpty() || currentFile.isNull()) return;
	const char* data = toData(content);
	QFile f(currentFile);
	if (f.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
		f.write(data);
	}

}

void LeeDataCore::dSaveFile(QByteArray content)
{
	if (currentFile.isEmpty() || currentFile.isNull()) return;
	const char* data = content.constData();
	QFile f(currentFile);
	if (f.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
		f.write(data);
	}

}

#pragma endregion

#pragma region Encrypt file with passwork key number type int

//deEncrypt return QString
QString LeeDataCore::dEncryptionData(QString filepath,int key , bool isdEncrypt)
{
	QString encData = NULL;
	QString nfile = dCopy(filepath);
	fstream fin;
	ofstream fout2(toData(nfile));
	// Open input file
	// ios::binary- reading file
	// character by character
	fin.open(toData(filepath), fstream::in);
	// Reading original file till
	// end of file
	while (fin >> noskipws >> c) {
		int temp = isdEncrypt ? (c - key) : (c + key);
		encData += (char)temp;
		// Write temp as char in
		// output file
		//fin << (char)temp;
		fout2 << (char)temp;
	}

	// Closing both files
	fin.close();
	fout2.close();
	if (remove(filepath.toLocal8Bit()) == 0) {
		if (rename(nfile.toLocal8Bit(), filepath.toLocal8Bit()) == 0) {
			//remote successful
		}
	}

	return encData;
}

const char* LeeDataCore::dDeEncryptionToChar(QString filepath, int key){
	QByteArray _deEncry = dEncryptionData(filepath, key,true).toLocal8Bit();
	return _deEncry.constData();
}

const char* LeeDataCore::dEncrypt(QString toEncrypt) {
	//char key[3] = {'K', 'C', 'Q'}; //Any chars will work
	//type multi key  output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
	char key[3] = { 'K', 'C', 'Q' }; //Any char will work
	string output = toData(toEncrypt);
	string Encrypt = toData(toEncrypt);

	for (int i = 0; i < Encrypt.size(); i++) {
		//output[i] = Encrypt[i] ^ key;
		output[i] = Encrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
	}
	///type multi key  output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

	return output.c_str();

}

void LeeDataCore::dSaveFileCommand(QString ifile , APPINFO lApp, QString opKey, QString ipNewKey)
{
	QFile ipF(ifile);
	if (!ipF.exists()) qDebug() << "not exist : " << ifile << endl;

	QApplication* app = qApp;
	qDebug() << "app name : " << app->applicationDisplayName() << endl;
	if (ipF.open(QIODevice::ReadOnly)) {
		QJsonObject inCmd, total;
		QByteArray _nCmd = ipF.readAll();
		inCmd[opKey] = _nCmd.constData();

		QFile f(CommandPath);

		QString _oCmd = f.readAll();
		const char* tstr =  ipNewKey.isEmpty() ||
			ipNewKey.isNull() ||
			ipNewKey =="" ?
			App2Name(lApp) :
			toData(ipNewKey);
		//get Json from base Command
		QJsonObject obj = dFileJs2JsObject();


		//get json array from ipkey
		QJsonArray arr = obj[tstr].toArray();
		qDebug() << "info 2: " << arr << endl;
		//append new command
		arr.append(inCmd);
		//QString tstr = Cmd2Str(lApp);
		total[tstr] = arr;
		qDebug() << "info 1: " << total[tstr] << endl;

		//if (f.open(QIODevice::ReadWrite)) {
		//	//get new command
		//	// read js file
		//	
		//	//dSaveFile(total);
		//}
	}

}

QString LeeDataCore::dCopy(QString filepath)
{
	QStringList split =filepath.split('.');
	return split[0] + "_copy.lee";;
}
#pragma endregion

