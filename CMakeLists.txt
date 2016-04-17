cmake_minimum_required (VERSION 2.8.12)

project(Tetris)

#tell compiler where to search for include-files
include_directories( inc )
include_directories( inc/SDL ) # THIS SHOULD BE TAKEN OUT

#tell linker where to search for libraries 
#link_directories( /usr/lib )
#set (LIBS libSDL.so libSDL_ttf.so)

#file( GLOB ...) allows globbing expressions
file(GLOB SOURCES src/*.cpp)

#set compiler flags
set (CMAKE_CXX_FLAGS "-std=c++11")

add_executable( Tetris ${SOURCES} )
#target_link_libraries( Tetris ${LIBS} )

find_package (SDL REQUIRED)
if (SDL_FOUND)
	include_directories(${SDL_INCLUDE_DIRS}) #DOENS'T FIND HEADER FILES??
	target_link_libraries (Tetris ${SDL_LIBRARIES})
endif (SDL_FOUND)

