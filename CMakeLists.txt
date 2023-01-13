cmake_minimum_required(VERSION 3.0.0)
project(TLibraries VERSION 0.1.0)

add_compile_definitions("_LEELIB")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)

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
set(DEVKIT_DIR "${CMAKE_SOURCE_DIR}/devkitBase/include")
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})
include_directories(${DEVKIT_DIR})
file(GLOB_RECURSE SOURCES
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
)


#=================== SETUP EXECTUABLE ====================#
# Enable debug logging on RELWITHDEBINFO configuration
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTEXT>
)

add_library(
    leetdvn STATIC
    ${SOURCES}
)

target_include_directories(leetdvn PUBLIC "${PROJECT_SOURCE_DIR}/include")

# add_subdirectory(src)
# add_subdirectory(lib)
# add_subdirectory(devkitBase)
# include_directories(src)
# include_directories(include)
# include_directories("${PROJECT_NAME}/devkitBase/include")
# #link_directories("C:/Program Files/Autodesk/Maya2019/lib")
# #add_library(Foundation.lib OpenMaya.lib OpenMayaUI.lib OpenMayaAnim.lib Qt5Core.lib Qt5Widgets.lib Qt5Gui.lib Qt5Network.lib)
# #target_link_directories()

# set(MYVAR ${MAYA_INCLUDE})
# function(print MYVAR)
# message("${var}=${${var}}")
# message("${ARGN}")
# message("${ARGC}")
# message("${ARGV0}")
# endfunction()