 #include "LeeInfo.h"
 #include "LeeDataBase.h"
 #include <winnt.h>
 #include <omp.h>
 #include "AssetsManage.h"
 #include <QtWidgets/QMainWindow>
 #include "LeeFtpsvc.h"
 #include "LeeMacro.h"
 #include <iostream>
 #include <stdio.h>

#include <TConfiguration.h>

// #define X3(...) CHECK2(__VA_ARGS__)

// QCoreApplication* createApplication(int& argc, char* argv[])
// {
// 	for (int i = 1; i < argc; ++i)
// 		if (!qstrcmp(argv[i], "-no-gui"))
// 			return new QCoreApplication(argc, argv);
// 	return new QApplication(argc, argv);
// }

// int main(int argc, char* argv[]) {

// 	//printf("sum : %d",X3(10, 20, 30));
// 	AssetsManage* assets = new AssetsManage();
// 	QString _p1 = "C:/Users/LeePhan/Documents/GitHub/leePickerOPS/src/leecorel.lee";
// 	QString _p2 = "C:/Users/LeePhan/Documents/GitHub/leePickerOPS/src/testing.lee";
// 	const char* _p3 = "C:/Users/LeePhan/Documents/GitHub/leePickerOPS/src/testing1.lee";

// 	LeeDataCore* data = new LeeDataCore(_p2);

// 	const char* content = data->dFile2Char(_p1);
// 	QStringList strl= data->dFileJs2Array( "ImgSrc");

// #pragma omp parallel for 
// 	for(auto &str : strl)
// 		printf("info : %s\n", toData(str));
// 	QByteArray hexContent = content;
// 	//LeeDataCore* dataC = new LeeDataCore(_p2);
// 	LONGLONG key = 3854543231232312871;
// 	LONGLONG akey = 3854543231232312871;

// 	//info debug
// 	QString d = data->dEncryptionData(_p2, (int)key);
// 	//printf("Enc %s\n", toChar(d.toUtf8()));f
// 	const char* result = data->dDeEncryptionToChar(_p2, (int)key);
// 	LeeInfo* info = new LeeInfo();

// 	QString fileui = "C:\\Users\\LeePhan\\Documents\\GitHub\\leePicker\\QtExtClone\\leePicker.ui";
// 	//qDebug() << TOOLNAME;
// 	//LoadUiFile(fileui);
// 	//LeeFtp* ftp = new LeeFtp("20.204.10.27","lee","leM!nhduy1203");
// 	////-=----------------------
// 	//QString fol = "./abc";
// 	//ftp->FtpSentFile( "C:\\Users\\LeePhan\\Documents\\leePhan\\leePhan\\Clanguage\\PickerDym\\taoday.txt");
// 	//QDialog* window = new QDialog();
// 	//Ui_Dialog* dialog = new Ui_Dialog();
// 	//dialog->setupUi(window,"abc");
// 	//window->show();
// 	//QApplication mWindow(argc,argv);
// 	//QWidget* widget = new QWidget();
// 	//widget->show();
// 	//system("cd C:/Program Files/Microsoft Visual Studio/2022/Community");
// 	//system("cd C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/bin");
// 	//int abc = system("g++ C:/Users/LeePhan/Documents/leePhan/leePhan/Clanguage/PickerDym/main.cpp");
// 	//BrowserImage("C:\\Users\\LeePhan\\Documents");
// 	//std::map<COMMANDAPP, std::string>;



//     //argv[1] = 'www.aaa.com';

// 	system("PAUSE");
// 	return 0;
// }


int main(int, char**) {
	

	TConfiguration *config = new TConfiguration("C:/Users/LeePhan/Documents/GitHub/TLibraries/src/TConfigurations.json");
	QString abc="bbbbbbbbbbbbbbbb";
	config->TSetConfigName("folder2", abc);
	//qDebug() << config->TGetConfigName("folder") << endl;
	system("PAUSE");
	return 0;
}

