cmake_minimum_required(VERSION 3.10)

IF (DEFINED ENV{SDK_TOOLCHAIN_FILE})
	set(toolchain_file $ENV{SDK_TOOLCHAIN_FILE})
	#message(STATUS "toolchain file:${toolchain_file}")
	set(CMAKE_TOOLCHAIN_FILE $ENV{SDK_TOOLCHAIN_FILE})
	#message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}.")
ELSE()
	IF(DEFINED ENV{SDK_C_COMPLIER})
		set(CMAKE_C_COMPILER $ENV{SDK_C_COMPLIER})
		#MESSAGE(STATUS "Set CMAKE_C_COMPILER to ${CMAKE_C_COMPILER} by environment")
	ELSE()
		#MESSAGE(STATUS "Set CMAKE_C_COMPILER to ${CMAKE_C_COMPILER} by default")
	ENDIF()

	IF(DEFINED ENV{SDK_CXX_COMPLIER})
		set(CMAKE_CXX_COMPILER $ENV{SDK_CXX_COMPLIER})
    		#MESSAGE(STATUS "Set CMAKE_CXX_COMPILER to ${CMAKE_CXX_COMPILER} by environment")
	ELSE()
		#MESSAGE(STATUS "Set CMAKE_CXX_COMPILER to ${CMAKE_CXX_COMPILER} by default")
	ENDIF()
ENDIF()

#MESSAGE(STATUS "c complier:${CMAKE_C_COMPILER}")
#MESSAGE(STATUS "cxx complier:${CMAKE_CXX_COMPILER}")

set(CMAKE_DEBUG_POSTFIX "d")
IF (DEBUG)
	add_definitions(-D__DEBUG__)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
ENDIF()

#C++11 support is required
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} $ENV{SDK_CMAKE_C_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $ENV{SDK_CMAKE_CXX_FLAGS} -std=c++11 -pthread")

#set up platform
#CMAKE_GENERATOR_PLATFORM is the setting for vs
#message(STATUS "CMAKE_GENERATOR_PLATFORM: ${CMAKE_GENERATOR_PLATFORM}")
#OR ${CMAKE_GENERATOR_PLATFORM} STREQUAL ""
IF(NOT DEFINED ENV{CMAKE_GENERATOR_PLATFORM})
	set(plat_form "none")
ELSE()
	set(plat_form ${CMAKE_GENERATOR_PLATFORM})
ENDIF()

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" )

IF(${plat_form} STREQUAL "none")	
	IF(DEFINED PLATFORM )
		set(plat_form ${PLATFORM})
	ELSEIF(DEFINED ENV{PLATFORM} )
		set(plat_form $ENV{PLATFORM})
	ELSE()
		set(plat_form "x64")
	ENDIF()
ENDIF()
#message(STATUS "plat form: ${plat_form}")

IF (DEFINED CMAKE_SYSTEM_NAME)
ELSE()
	set(CMAKE_SYSTEM_NAME ${CMAKE_HOST_SYSTEM_NAME})
ENDIF()

IF (DEFINED ENV{SDK_TARGET_SYSTEM})
	set(os "android")
	add_definitions(-DANDROID_OS)
	set(ANDROID_ABI ${plat_form})
	#message(STATUS "target_platform:$ENV{SDK_TARGET_PLATFORM} os:${os} ANDROID_ABI:${ANDROID_ABI}")
ELSE()
	IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
		set(os "linux")
		add_definitions(-DLINUX_OS)
	ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
		set(os "windows")
		add_definitions(-DUNICODE -D_UNICODE)
		add_definitions(-DWINDOWS_OS)
		#specifically for windows.h and winsock2.h conflicting macro definitions.
		add_definitions(-DWIN32_LEAN_AND_MEAN)
	#mac system is Darwin
	ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
		add_definitions(-DMACOS)
		set(os "macos")
	ELSEIF (CMAKE_SYSTEM_NAME MATCHES "iOS")
		add_definitions(-DIOS)
		set(os "ios")
	ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
		add_definitions(-DANDROID_OS)
		set(os "android")
		if(DEFINED ANDROID_ABI)
			set(plat_form ${ANDROID_ABI})
		endif()
	ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
		add_definitions(-DFREEBSD_OS)
	ELSE ()
		MESSAGE(STATUS "other os: ${CMAKE_SYSTEM_NAME}   ${CMAKE_HOST_SYSTEM_NAME}")
		FATAL_ERROR("unknow os")
	ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
ENDIF()

#message(STATUS "current os:${os}")
#message(STATUS "current platform:${plat_form}")




