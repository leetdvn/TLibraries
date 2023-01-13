#ifndef ASSETSMANAGE_H
#define ASSETSMANAGE_H
#pragma once
#include <QtCore/QFile>
#include "lPublic.h"

#define ABC(...) { printf("processor %s\n",__VA_ARGS__);}

using namespace std;


class EXPORT_API AssetsManage
{
public:
	WINAPI AssetsManage();
	void demo(int abc) {}

private:

};

#endif //ASSETMANAGE
