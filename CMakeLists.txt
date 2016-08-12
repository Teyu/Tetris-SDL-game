cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)

PROJECT(Tetris)

IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
        MESSAGE(FATAL_ERROR "You are about to build inside of your source directory. Please create an out-of-source build.")
ENDIF()

OPTION(TETRIS_BUILD_TESTS "Build tetris unit tests." OFF) #enable this option by setting the -DTETRIS_BUILD_TESTS flag

#tell compiler where to search for include-files
INCLUDE_DIRECTORIES( inc )

ADD_SUBDIRECTORY(libs) #subdirectories must contain a CMakeLists.txt file

#this enables the add_test command and adds the "test" target to the Makefile. Typing the "make test" command will then run CTest.
ENABLE_TESTING()

FILE(COPY ${CMAKE_SOURCE_DIR}/fonts/FreeSans.ttf DESTINATION ${CMAKE_BINARY_DIR})
FILE(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

SET(TETRIS_SOURCE_FILES 
		${CMAKE_SOURCE_DIR}/src/Field.cpp
		${CMAKE_SOURCE_DIR}/src/Form.cpp
		${CMAKE_SOURCE_DIR}/src/Framework.cpp
		${CMAKE_SOURCE_DIR}/src/Game.cpp
		${CMAKE_SOURCE_DIR}/src/Player.cpp
		${CMAKE_SOURCE_DIR}/src/Sprite.cpp
		${CMAKE_SOURCE_DIR}/src/Timer.cpp
)

#set compiler flags
IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "CLANG")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -Wall -g")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -Wall")
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MDd")
ENDIF()

ADD_EXECUTABLE( Tetris
        ${CMAKE_SOURCE_DIR}/src/main.cpp
)
ADD_LIBRARY(TetrisCore STATIC
        ${TETRIS_SOURCE_FILES}
)
TARGET_LINK_LIBRARIES(Tetris
        TetrisCore #this way the source files only need to be compiled once (i.e. for unit tests)
)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

#include SDL-library
FIND_PACKAGE(SDL REQUIRED)

IF(SDL_FOUND)
        INCLUDE_DIRECTORIES(
                ${SDL_INCLUDE_DIR}
                ${SDL_INCLUDE_DIR}/SDL
        )
        TARGET_LINK_LIBRARIES(Tetris 
                ${SDL_LIBRARY}
		)
ENDIF()


IF(NOT SDL_LIBRARY)
        MESSAGE( FATAL_ERROR "SDL_LIBRARY not set. Please specify the path to the SDL library using the SDL_LIBRARY tag.")
ELSE()
        MESSAGE( "Found SDL_LIBRARY under ${SDL_LIBRARY}.")
ENDIF()
IF(NOT SDL_INCLUDE_DIR)
        MESSAGE( FATAL_ERROR "SDL_INCLUDE_DIR not set. Please specify the path to the SDL include directoy using the SDL_INCLUDE_DIR tag.")
ELSE()
        MESSAGE( "Found SDL_INCLUDE_DIR under ${SDL_INCLUDE_DIR}." )
ENDIF()

#include SDL_ttf-library
FIND_PACKAGE(SDL_ttf REQUIRED)

IF(SDLTTF_FOUND)
        INCLUDE_DIRECTORIES(
                ${SDLTTF_INCLUDE_DIR}
                ${SDLTTF_INCLUDE_DIR}/SDL
        )
        TARGET_LINK_LIBRARIES(Tetris 
					${SDLTTF_LIBRARY}
		)
ENDIF()

IF(NOT SDLTTF_LIBRARY)
        MESSAGE( FATAL_ERROR "SDLTTF_LIBRARY not set. Please specify the path to the SDL_ttf library using the SDLTTF_LIBRARY tag.")
ELSE()
        MESSAGE( "Found SDLTTF_LIBRARIES under ${SDLTTF_LIBRARY}.")
ENDIF()
IF(NOT SDLTTF_INCLUDE_DIR)
        MESSAGE( FATAL_ERROR "SDLTTF_INCLUDE_DIR not set. Please specify the path to the SDL_ttf include directoy using the SDLTTF_INCLUDE_DIR tag.")
ELSE()
        MESSAGE( "Found SDLTTF_INCLUDE_DIR under ${SDLTTF_INCLUDE_DIR}." )
ENDIF()
