cmake_minimum_required(VERSION 3.0.0)
project(TLibraries VERSION 0.1.0)



#=================== SETUP EXECTUABLE ====================#
# Enable debug logging on RELWITHDEBINFO configuration
# set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
#     $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTEXT>
# )

include_directories(DEVKIT_INCLUDE_DIR)
include_directories(DEVKIT_LIB_DIR)
add_subdirectory(src)
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