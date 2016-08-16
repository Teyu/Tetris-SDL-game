SET(TETRIS_SOURCE_FILES
  ${CMAKE_SOURCE_DIR}/src/Field.cpp
  ${CMAKE_SOURCE_DIR}/src/Form.cpp
  ${CMAKE_SOURCE_DIR}/src/Framework.cpp
  ${CMAKE_SOURCE_DIR}/src/Game.cpp
  ${CMAKE_SOURCE_DIR}/src/Player.cpp
  ${CMAKE_SOURCE_DIR}/src/Sprite.cpp
  ${CMAKE_SOURCE_DIR}/src/Timer.cpp
)

ADD_EXECUTABLE( Tetris
  ${CMAKE_SOURCE_DIR}/src/main.cpp
)

INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/inc )

ADD_LIBRARY(TetrisCore STATIC
  ${TETRIS_SOURCE_FILES}
)

TARGET_LINK_LIBRARIES(Tetris
  TetrisCore
)

IF(TETRIS_BUILD_TESTS)
  add_subdirectory(tests)
ENDIF()

#include SDL-library
#
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
#
