
MESSAGE( "Adding test environment." )

INCLUDE_DIRECTORIES(
  ${gmock_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR}/include
)

ADD_EXECUTABLE(TetrisUnitTests
  ${CMAKE_SOURCE_DIR}/src/tests/MockForm.cpp
)

TARGET_LINK_LIBRARIES(TetrisUnitTests
  gmock_main
  TetrisCore
)

ADD_TEST(
  NAME TetrisUnitTests
  COMMAND TetrisUnitTests
)
