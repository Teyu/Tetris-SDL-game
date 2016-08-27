find_package(SDL_ttf REQUIRED)

if(SDLTTF_FOUND)
  include_directories(
    ${SDLTTF_INCLUDE_DIR}
    ${SDLTTF_INCLUDE_DIR}/SDL
  )
  target_link_libraries(Tetris
    ${SDLTTF_LIBRARY}
  )
endif()

if(NOT SDLTTF_LIBRARY)
  message( FATAL_ERROR "SDLTTF_LIBRARY not set. Please specify the path to the SDL_ttf library using the SDLTTF_LIBRARY tag.")
else()
  message( "Found SDLTTF_LIBRARIES under ${SDLTTF_LIBRARY}.")
endif()
if(NOT SDLTTF_INCLUDE_DIR)
  message( FATAL_ERROR "SDLTTF_INCLUDE_DIR not set. Please specify the path to the SDL_ttf include directoy using the SDLTTF_INCLUDE_DIR tag.")
else()
  message( "Found SDLTTF_INCLUDE_DIR under ${SDLTTF_INCLUDE_DIR}." )
endif()
