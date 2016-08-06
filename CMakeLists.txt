cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)

PROJECT(Tetris)

OPTION(TETRIS_BUILD_TESTS "Build tetris unit tests." OFF) #enable this option by setting the -DTETRIS_BUILD_TESTS flag

#tell compiler where to search for include-files
INCLUDE_DIRECTORIES( inc )

ADD_SUBDIRECTORY(libs) #subdirectories must contain a CMakeLists.txt file

#file( GLOB ...) allows globbing expressions
FILE(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

#set compiler flags
IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR 
   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "CLANG")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")#CMake will automatically convert unix-style flags to msvc-style
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
ENDIF()

ADD_EXECUTABLE( Tetris ${SOURCES})
ADD_LIBRARY(TetrisCore STATIC ${SOURCES})
TARGET_LINK_LIBRARIES(Tetris TetrisCore) #this way the source files only need to be compiled once (i.e. if one wants to create unit tests)

#include SDL-library
FIND_PACKAGE(SDL REQUIRED)

IF(SDL_FOUND)
        INCLUDE_DIRECTORIES( ${SDL_INCLUDE_DIRS})
        TARGET_LINK_LIBRARIES(Tetris ${SDL_LIBRARY})
ENDIF()

IF(NOT SDL_LIBRARY)
        MESSAGE( FATAL_ERROR "SDL_LIBRARIES not set" )
ELSE()
        MESSAGE( "found SDL_LIBRARIES under ${SDL_LIBRARY}")
ENDIF()
IF(NOT SDL_INCLUDE_DIR)
        MESSAGE( FATAL_ERROR "SDL_INCLUDE_DIR not set" )
ELSE()
        MESSAGE( "found SDL_INCLUDE_DIR under ${SDL_INCLUDE_DIR}" )
ENDIF()

#include SDL_ttf-library
FIND_PACKAGE(SDL_ttf REQUIRED)

IF(SDL_TTF_FOUND)
        INCLUDE_DIRECTORIES( ${SDL_TTF_INCLUDE_DIRS})
        TARGET_LINK_LIBRARIES(Tetris ${SDL_TTF_LIBRARY})
ENDIF()

IF(NOT SDL_TTF_LIBRARY)
        MESSAGE( FATAL_ERROR "SDL_TTF_LIBRARIES not set" )
ELSE()
        MESSAGE( "found SDL_TTF_LIBRARIES under ${SDL_TTF_LIBRARY}")
ENDIF()
IF(NOT SDL_TTF_INCLUDE_DIR)
        MESSAGE( FATAL_ERROR "SDL_TTF_INCLUDE_DIR not set" )
ELSE()
        MESSAGE( "found SDL_TTF_INCLUDE_DIR under ${SDL_TTF_INCLUDE_DIR}" )
ENDIF()
