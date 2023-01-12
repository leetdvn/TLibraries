add_library(
	SRC
	lPublic.cpp
	LeeInfo.cpp
	LeeFtpsvc.cpp
	LeeDataBase.cpp
	AssetsManage.cpp
)

target_include_directories(SRC PUBLIC "${PROJECT_NAME}/lib")