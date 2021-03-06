#	***** BEGIN LICENSE BLOCK *****
#
#	Copyright 2017 Yzena Tech
#
#	Licensed under the Apache License, Version 2.0 (the "Apache License")
#	with the following modification; you may not use this file except in
#	compliance with the Apache License and the following modification to it:
#	Section 6. Trademarks. is deleted and replaced with:
#
#	6. Trademarks. This License does not grant permission to use the trade
#		names, trademarks, service marks, or product names of the Licensor
#		and its affiliates, except as required to comply with Section 4(c) of
#		the License and to reproduce the content of the NOTICE file.
#
#	You may obtain a copy of the Apache License at
#
#		http://www.apache.org/licenses/LICENSE-2.0
#
#	Unless required by applicable law or agreed to in writing, software
#	distributed under the Apache License with the above modification is
#	distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
#	KIND, either express or implied. See the Apache License for the specific
#	language governing permissions and limitations under the Apache License.
#
#	****** END LICENSE BLOCK ******

cmake_minimum_required(VERSION 3.0)

project(yet C)

# Necessary to suppress a useless warning with QtCreator.
set(ignoreMe "${QT_QMAKE_EXECUTABLE}")
set(ignoreMe "${CMAKE_CXX_COMPILER}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

message(STATUS "${CMAKE_BUILD_TYPE}")

# If we are in debug mode...
if(("${CMAKE_BUILD_TYPE}" MATCHES "Debug" OR "${CMAKE_BUILD_TYPE}" MATCHES "RelWithDegInfo")
		AND "${CMAKE_C_COMPILER_ID}" MATCHES "Clang")

	# Create the sanitizer options.
	option(YET_SANITIZER_ADDRESS "Build with AddressSanitizer" ON)

	# If the memory sanitizer is in use, set the flag.
	if ("${YET_SANITIZER_ADDRESS}")
		string(CONCAT YET_SANITIZER_FLAGS " -fsanitize=address")
	endif()

	# Option to run the undefined behavior sanitizer.
	option(YET_SANITIZER_UNDEFINED "Build with UndefinedBehaviorSanitizer" ON)

	# If we want to run the undefined behavior sanitizer...
	if(YET_SANITIZER_UNDEFINED)
		string(CONCAT YET_SANITIZER_FLAGS " -fsanitize=undefined")
	endif()

endif()

# If we are using sanitizers...
if(DEFINED YET_SANITIZER_FLAGS)

	# We must use Clang as the linker.
	set(CMAKE_LINKER "${CMAKE_C_COMPILER}")

	# These are all options to make the print outs prettier.
	string(CONCAT YET_FLAGS "${YET_SANITIZER_FLAGS} -fno-omit-frame-pointer "
		"-fno-optimize-sibling-calls -fno-common")

	# We need to set compiler *and* linker flags.
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${YET_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${YET_FLAGS}")

	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-sanitize-recover=all")

endif()

# If we are in release mode...
if("${CMAKE_BUILD_TYPE}" MATCHES "Release")

	option(YET_ENABLE_LTO "Build with link time optimization" OFF)

	if ("${YET_ENABLE_LTO}")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -flto")
	endif()

	# Have an option to harden Dyna.
	option(YET_HARDEN "Build with hardened security" OFF)

	# If we are hardened, add Control Flow Integrity.
	# We would like to add Safe Stack, but it seg faults
	# with jemalloc right now.
	if("${YET_HARDEN}")

		# Set a bunch of initial flags.
		#set(YET_FLAGS "-fsanitize=cfi -fvisibility=hidden -fsanitize=safe-stack")
		set(YET_FLAGS "-fsanitize=cfi -fvisibility=hidden")

		# We need to set compiler flags.
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${YET_FLAGS}")

	endif()

endif()

enable_testing()

add_subdirectory(cmake)

add_subdirectory(docs)

set("YET_INCLUDE_DIR" "include")
set("YET_SRC_DIR" "src")

include_directories("${YET_INCLUDE_DIR}")
add_subdirectory("${YET_INCLUDE_DIR}")

add_subdirectory("${YET_SRC_DIR}")

