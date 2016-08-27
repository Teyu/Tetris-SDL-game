
message( "Adding test environment." )

include_directories(
  ${gmock_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR}/include
)

add_executable(TetrisUnitTests
  ${CMAKE_SOURCE_DIR}/src/tests/MockForm.cpp
)

target_link_libraries(TetrisUnitTests
  gmock_main
  TetrisCore
)

add_test(
  NAME TetrisUnitTests
  COMMAND TetrisUnitTests
)
