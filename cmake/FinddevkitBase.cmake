find_path(DEVKIT_INCLUDE_DIR
	NAMES
          "*.h"
	PATHS "ExtLibs/devkitBase/include"
)

if(WIN32)
	find_path(DEVKIT_LIB_DIR
		NAMES "*.lib"
		PATHS "ExtLibs/devkitBase/lib"
	)
	file(GLOB DEVKIT_LIBS "${DEVKIT_LIB_DIR}/*.lib")
else()
	find_path(DEVKIT_LIB_DIR
		NAMES "*.lib"
		PATHS "ExtLibs/devkitBase/lib"
	)
	file(GLOB DEVKIT_LIBS "${DEVKIT_LIB_DIR}/*.a")
endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
  Devkit DEFAULT_MSG DEVKIT_INCLUDE_DIR DEVKIT_LIBS
)
