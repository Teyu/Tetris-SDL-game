set(SYLWIA_SOURCE_FILES
  ${CMAKE_SOURCE_DIR}/src/Framework.cpp
  ${CMAKE_SOURCE_DIR}/src/Game.cpp
  ${CMAKE_SOURCE_DIR}/src/Sprite.cpp
  ${CMAKE_SOURCE_DIR}/src/Timer.cpp
)

add_executable( Sylwia
  ${CMAKE_SOURCE_DIR}/src/main.cpp
)

include_directories( ${CMAKE_SOURCE_DIR}/inc )

add_library(SylwiaCore STATIC
  ${SYLWIA_SOURCE_FILES}
)

target_link_libraries(Sylwia
  SylwiaCore
  ${SDL_LIBRARY}
  ${SDLMAIN_LIBRARY}
)

if(SYLWIA_BUILD_TESTS)
  add_subdirectory(tests)
endif()
