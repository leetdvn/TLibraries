set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
set(DEVKIT_DIR "F:/devkitBase")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Designer REQUIRED)
#=================== INCLUSION OF Project Files ====================#
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
#set(DEVKIT_DIR "${CMAKE_SOURCE_DIR}/devkitBase/include")
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})
include_directories(${DEVKIT_DIR}/include)

file(GLOB_RECURSE SOURCES
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
)

add_library(
    leetdvn STATIC
    ${SOURCES}
)
target_include_directories(leetdvn PUBLIC ${PROJECT_SOURCE_DIR}/include)
message(STATUS "abc : ${DEVKIT_LIB_DIR}")