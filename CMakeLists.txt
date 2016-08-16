cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)

PROJECT(Tetris)

IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  MESSAGE(FATAL_ERROR "You are about to build inside of your source directory. Please create an out-of-source build.")
ENDIF()

OPTION(TETRIS_BUILD_TESTS "Build tetris unit tests." OFF)

ENABLE_TESTING()

FILE(COPY ${CMAKE_SOURCE_DIR}/fonts/FreeSans.ttf DESTINATION ${CMAKE_BINARY_DIR}/src)
FILE(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "CLANG")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -Wall -g")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -Wall")
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MDd")
ENDIF()

add_subdirectory(src)
ADD_SUBDIRECTORY(libs)

#TODO: asuführbare Dateien sollten im binary tree unter bin landen! Generell: Ausgabe strukturieren!
