set(TETRIS_SOURCE_FILES
  ${CMAKE_SOURCE_DIR}/src/Form.cpp
  ${CMAKE_SOURCE_DIR}/src/Framework.cpp
  ${CMAKE_SOURCE_DIR}/src/Game.cpp
  ${CMAKE_SOURCE_DIR}/src/Sprite.cpp
  ${CMAKE_SOURCE_DIR}/src/Timer.cpp
)

add_executable( Tetris
  ${CMAKE_SOURCE_DIR}/src/main.cpp
)

include_directories( ${CMAKE_SOURCE_DIR}/inc )

add_library(TetrisCore STATIC
  ${TETRIS_SOURCE_FILES}
)

target_link_libraries(Tetris
  TetrisCore
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(specifySDLpaths)
include(specifySDLTTFpaths)

if(TETRIS_BUILD_TESTS)
  add_subdirectory(tests)
endif()
