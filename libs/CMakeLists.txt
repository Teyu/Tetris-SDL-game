#set compiler flags
IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR 
   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "CLANG")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")#CMake will automatically convert unix-style flags to msvc-style
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
ENDIF()

FILE(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

ADD_LIBRARY(TetrisCore STATIC ${SOURCES})
