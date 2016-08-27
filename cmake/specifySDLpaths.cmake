find_package(SDL REQUIRED)

if(SDL_FOUND)
  include_directories(
    ${SDL_INCLUDE_DIR}
    ${SDL_INCLUDE_DIR}/SDL
  )
  target_link_libraries(Tetris
    ${SDL_LIBRARY}
  )
endif()

if(NOT SDL_LIBRARY)
  message( FATAL_ERROR "SDL_LIBRARY not set. Please specify the path to the SDL library using the SDL_LIBRARY tag.")
else()
  message( "Found SDL_LIBRARY under ${SDL_LIBRARY}.")
endif()
if(NOT SDL_INCLUDE_DIR)
  message( FATAL_ERROR "SDL_INCLUDE_DIR not set. Please specify the path to the SDL include directoy using the SDL_INCLUDE_DIR tag.")
else()
  message( "Found SDL_INCLUDE_DIR under ${SDL_INCLUDE_DIR}." )
endif()


