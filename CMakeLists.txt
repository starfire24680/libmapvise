CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(libmapvise C)

ADD_SUBDIRECTORY(libmapvise)

option(ENABLE_TESTING OFF)
option(MINGW_TESTING OFF)
option(HUGEFILE_TESTING ON) # Requires 8 GB RAM

if (MINGW_TESTING)
	find_program(WINE_EXECUTABLE wine)

	if(WINE_EXECUTABLE)
		message(STATUS "Wine found: ${WINE_EXECUTABLE}")
	else()
		message(ERROR "Wine not found")
	endif()

	SET(CMAKE_SYSTEM_NAME Windows)
	SET(CMAKE_SYSTEM_VERSION 1)

	SET(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
else()
	SET(CMAKE_C_COMPILER gcc)
endif()

if (ENABLE_TESTING)
	enable_testing()
	include_directories(${CMAKE_SOURCE_DIR})
	add_subdirectory("test")
endif()

unset(CMAKE_SYSTEM_NAME CACHE)
unset(CMAKE_SYSTEM_VERSION CACHE)
unset(CMAKE_C_COMPILER CACHE)
