# A Tetris SDL-game

This is a remake of the classic tetris game in progress.

This project serves for me to improve my c++ skills, learn cross-platform programming with cmake, 
as well as putting in audio and animations. First of all I want to improve my skills (I am a newbie) and hopefully the result will
be a game that everyone is welcome to play and to just have fun with it :-)

![Screenshot](https://github.com/Teyu/Tetris-SDL-game/blob/master/TetrisScreenshot.png)

## Building Instructions

### Requirements:

* CMake
* SDL 1.2 developement library
* SDL_ttf 1.2 developement library
* gnu, clang or msvc compiler

### Linux

First you need to install the required libsdl1.2-dev ("sudo apt-get install libsdl1.2-dev") and libsdl-ttf2.0-dev ("sudo apt-get install libsdl-ttf2.0-dev")
packages as well as cmake ("sudo apt-get install cmake"). Create a build directory where you want to build the source code and go into that
directory if you are using the shell. Type cmake <path/to/source/dir> or specify the build and source code directories using the cmake-gui.

NOTE: In-source-builds are not supported, cmake will throw an error if you are trying to do so. Your build and source directories have to differ.

CMake will know try to find the SDL libraries searching in default locations. If they could not be found an error will be thrown and a message appears
which tells you to specify the path to these libraries manually. (for example:
type "cmake -DSDL_INCLUDE_DIR=<yourPath>/include -DSDL_LIBRARY=<yourPath>/lib/SDL.lib" in the shell or just click on these when you are using cmake-gui)

When CMake has finished successfully just type "make" or use your preferable IDE to compile the software. Happy Coding! :-)

### Windows

You can download the required libraries at <http://www.libsdl.org> (choose the SDL1.2 develop lib)
and <http://www.libsdl.org/projects/SDL_ttf/release-1.2.html>. Unpack them to any
location you want. Create a build directoy where you want to build the source code. Run the cmake-gui and specify the build and source directories.

NOTE: In-source-builds are not supported, cmake will throw an error if you are trying to do so. Your build and source directories have to differ.

Now click configure and elect your default native compiler. CMake will now most likely throw an error that it can't find the location of the SDL libraries.
Set the SDL_INCLUDE_DIR, SDL_LIBRARY, SDLMAIN_LIBRARY as well as the SDLTTF_INCLUDE_DIR and SDLTTF_LIBRARY tags manually to the path to the location
of the SDL libraries (for example: SDL_INCLUDE_DIR = <yourPath>/include,  SDL_LIBRARY = <yourPath>/lib/SDL.lib).

NOTE: I recommend to first try "x86" regardless of your operating system.
In many cases using the x64 libraries caused a really annoying (0x000007b) error when executing or the compiler complained that it could not find SDL.
(If anyone knows the reason for that I would be very thankful if you could post me a message)

Copy the SDL dll files from the appropiate(!) x64 or x84 directory to C:/Windows/SysWOW64. After doing so and if CMake finished successfully you can now open the created project using your
preferable IDE to compile the software (for example: if you are using Visual Studio, CMake created a Tetris.sln solution for you). Happy Coding! :-)


## Unit Tests (under construction)

To build the unit tests you have to set the TETRIS_BUILD_TESTS flag (for example: "cmake -DTETRIS_BUILD_TESTS = ON"). Now type "make test"
or simply run the created executable TetrisUnitTests to run the unit tests.
