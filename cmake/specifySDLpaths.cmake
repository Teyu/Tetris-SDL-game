find_package(SDL REQUIRED)

#if(SDL_FOUND)
#endif()

if(NOT SDL_LIBRARY)
  message( FATAL_ERROR "SDL_LIBRARY not set. Please specify the path to the SDL library using the SDL_LIBRARY tag.")
else()
  message( "Found SDL_LIBRARY under ${SDL_LIBRARY}.")
endif()


