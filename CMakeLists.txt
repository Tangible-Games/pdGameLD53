cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_STANDARD 11)

set(ENVSDK $ENV{PLAYDATE_SDK_PATH})

if (NOT ${ENVSDK} STREQUAL "")
	# Convert path from Windows
	file(TO_CMAKE_PATH ${ENVSDK} SDK)
else()
	execute_process(
			COMMAND bash -c "egrep '^\\s*SDKRoot' $HOME/.Playdate/config"
			COMMAND head -n 1
			COMMAND cut -c9-
			OUTPUT_VARIABLE SDK
			OUTPUT_STRIP_TRAILING_WHITESPACE
	)
endif()

if (NOT EXISTS ${SDK})
	message(FATAL_ERROR "SDK Path not found; set ENV value PLAYDATE_SDK_PATH")
	return()
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_XCODE_GENERATE_SCHEME TRUE)

# Game Name Customization
set(PLAYDATE_GAME_NAME pdGameLD53)
set(PLAYDATE_GAME_DEVICE pdGameLD53_arm)

project(${PLAYDATE_GAME_NAME} C CXX ASM)

if (TOOLCHAIN STREQUAL "armgcc")
	add_executable(${PLAYDATE_GAME_DEVICE} Lib/stubs.c Lib/main.c Lib/game.cpp)
else()
	add_library(${PLAYDATE_GAME_NAME} SHARED Lib/stubs.c Lib/main.c Lib/game.cpp)

	enable_testing()

	add_executable(vector2d-test Lib/PdSymphony/vector2d_test.cpp)
	add_test(vector2d-test vector2d-test)

	add_executable(point2d-test Lib/PdSymphony/point2d_test.cpp)
	add_test(point2d-test point2d-test)

	add_executable(segment2d-test Lib/PdSymphony/segment2d_test.cpp)
	add_test(segment2d-test segment2d-test)
endif()

include(${SDK}/C_API/buildsupport/playdate_game.cmake)

