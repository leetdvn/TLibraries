add_library(
	lee-libUtils
	STATIC
	cmakelib.cpp
)
target_include_directories(lee-libUtils PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_subdirectory(include)