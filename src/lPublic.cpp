#include "lPublic.h"


void WINAPI getPencil(pencil* arg)
{
	arg = new pencil("new pencil");
	qDebug() << arg->toStr() << endl;

}

INTERNET_STATUS WINAPI IsConnectedToNet()
{
	INTERNET_STATUS connectedStatus = INTERNET_STATUS::CONNECTION_ERROR;
	HRESULT hr = S_FALSE;
	try
	{
		hr = CoInitialize(NULL);
		if (SUCCEEDED(hr))
		{
			INetworkListManager* pNetworkListManager;
			hr = CoCreateInstance(CLSID_NetworkListManager, NULL, CLSCTX_ALL, __uuidof(INetworkListManager), (LPVOID*)&pNetworkListManager);
			if (SUCCEEDED(hr))
			{
				NLM_CONNECTIVITY nlmConnectivity = NLM_CONNECTIVITY::NLM_CONNECTIVITY_DISCONNECTED;
				VARIANT_BOOL isConnected = VARIANT_FALSE;
				hr = pNetworkListManager->get_IsConnectedToInternet(&isConnected);
				if (SUCCEEDED(hr))
				{
					if (isConnected == VARIANT_TRUE)
						connectedStatus = INTERNET_STATUS::CONNECTED;
					else
						connectedStatus = INTERNET_STATUS::DISCONNECTED;
				}

				if (isConnected == VARIANT_FALSE && SUCCEEDED(pNetworkListManager->GetConnectivity(&nlmConnectivity)))
				{
					if (nlmConnectivity & (NLM_CONNECTIVITY_IPV4_LOCALNETWORK | NLM_CONNECTIVITY_IPV4_SUBNET | NLM_CONNECTIVITY_IPV6_LOCALNETWORK | NLM_CONNECTIVITY_IPV6_SUBNET))
					{
						connectedStatus = INTERNET_STATUS::CONNECTED_TO_LOCAL;
					}
				}

				pNetworkListManager->Release();
			}
		}

		CoUninitialize();
	}
	catch (...)
	{
		connectedStatus = INTERNET_STATUS::CONNECTION_ERROR;
	}

	return connectedStatus;
}

const char* WINAPI toData(QString str) { return QByteArray(str.toLocal8Bit()).constData(); }

bool WINAPI FileEx(QString filepath) { return  QFile(filepath).exists(); }

bool WINAPI isQOnline()
{
	QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
	bool result = false;
	for (int i = 0; i < ifaces.count(); i++)
	{
		QNetworkInterface iface = ifaces.at(i);
		if (iface.flags().testFlag(QNetworkInterface::IsUp)
			&& !iface.flags().testFlag(QNetworkInterface::IsLoopBack))
		{
			for (int j = 0; j < iface.addressEntries().count(); j++)
			{
				// we have an interface that is up, and has an ip address
				// therefore the link is present
				// we will only enable this check on first positive,
				// all later results are incorrect
				if (result == false)
					result = true;
			}
		}

	}
	return result;
}

LPCWSTR WINAPI toWData(QString str) { return (const wchar_t*)str.utf16(); }

QString WINAPI FileDetach(QString inStr)
{
	QStringList strlist = inStr.split('/');
	if (strlist.length() <= 1) {
		strlist = inStr.split("\\");
		if (strlist.length() <= 1)
			return "";
	}
	QString result = strlist[strlist.length() - 1];
	return  result;
}

QWidget* WINAPI LoadUiFile(QString filepath)
{
	if (filepath.isEmpty() || filepath.isNull() || filepath == "") return Q_NULLPTR;
	QMainWindow* wid = new QMainWindow();
	QFormBuilder loader;
	QFile file(filepath);
	if (!file.exists()) {
		qDebug() << "file : " << filepath << "does'nt exists\n" << endl;
	}
	file.open(QFile::ReadOnly);
	QWidget* pane = loader.load(&file, wid);
	pane->show();
	file.close();
	return pane;
}

QString WINAPI BrowserImage(QString Previous)
{
	QString selfilter = "PNG (*.png)";
	QString ImgPath = QFileDialog::getOpenFileName(
		nullptr,
		" Image Choise ",
		Previous, 
		"All files (*.*);;JPEG (*.jpg *.jpeg);;TIFF (*.tif);;PNG (*.png)",
		&selfilter);

	return ImgPath;
}

constexpr const char* WINAPI App2Name(APPINFO lApp)
{
	switch (lApp)
	{
		case APPINFO::LMAYA: return "Maya";
		case APPINFO::LHONDINI: return "Hondini";
		case APPINFO::LMAX: return "3DMax";
		case APPINFO::LBLENDER: return "Blender";
		case APPINFO::LUNREAL: return "Unreal";
	}
	return NULL;
}
//void WINAPI hello(callback helo) {
//	const char* mess = toData("Directive Processcor : " + QApplication::applicationDisplayName());
//	MGlobal::displayWarning(mess);
//	helo = TDisplayName(QString("helo callback"));
//	return ;
//}

QString WINAPI TDisplayName(QString Message)
{
	const char* mess = toData("Directive Processcor : " + Message);
	MGlobal::displayWarning(mess);
	return QApplication::applicationDisplayName();
}

QString WINAPI GetDomain()
{
	QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
	bool result = false;
	for (int i = 0; i < ifaces.count(); i++) {
		QNetworkInterface iface = ifaces.at(i);
		if (iface.hardwareAddress() != "") {
			return iface.hardwareAddress();
		}
	}
	return new char();
}

QString WINAPI GetIp()
{
	QString ipResult;
	foreach(const QNetworkInterface & qNetInterface, QNetworkInterface::allInterfaces()) {
		foreach(const QNetworkAddressEntry & qNetInterfaceAddress, qNetInterface.addressEntries()) {
			if (qNetInterfaceAddress.ip().protocol() == QAbstractSocket::IPv4Protocol && qNetInterfaceAddress.ip() != QHostAddress(QHostAddress::LocalHost))
			{
				ipResult += qNetInterfaceAddress.ip().toString();
			}
		}
	}
	return ipResult;
}

bool WINAPI isConnected()
{
	INTERNET_STATUS status = INTERNET_STATUS::CONNECTION_ERROR;
	status = IsConnectedToNet();
	switch (status)
	{
	case INTERNET_STATUS::CONNECTED:
		//std::cout << "Connected to the internet" << endl;
		return true;
	case INTERNET_STATUS::DISCONNECTED:
		//std::cout << "Internet is not available" << endl;
		return false;
	case INTERNET_STATUS::CONNECTED_TO_LOCAL:
		//std::cout << "Connected to the local network." << endl;
		return false;
	case INTERNET_STATUS::CONNECTION_ERROR:
	default:
		//std::cout << "Unknown error has been occurred." << endl;
		return false;
	}
	return false;
}

template <class T>
bool WINAPI TWidgetAction(void*& action, QString label, QString name)
{
	QWidget* w = new QWidget();
	w->setAttribute(Qt::WA_DeleteOnClose, true);
	QHBoxLayout* layout = new QHBoxLayout(w);
	layout->setContentsMargins(5, 5, 5, 5);
	QWidgetAction* _nAct = new QWidgetAction(w);
	action = new T(w);
	if (label != NULL) {
		QLabel* lbel = (QLabel*&)action;
		lbel->setText(label);
	}
	w->setObjectName(name);
	layout->setAlignment(Qt::AlignCenter);
	w->setLayout(layout);
	_nAct->setDefaultWidget(w);
	layout->addWidget((T*)action);
	return _nAct;
}

pencil::pencil(QString str)
{
	inp = str;
}

QString pencil::toStr()
{
	return toData(inp);
}
