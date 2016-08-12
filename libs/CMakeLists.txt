
#TODO:make subdirectory tests to src and inc, move CMakeLists Code to subdirectory tests
# leave this:
#IF (TETRIS_BUILD_TESTS)
# ADD_SUBDIRECTORIES(gtest)
#ENDIF()
IF(TETRIS_BUILD_TESTS)
        MESSAGE( "Adding test environment." )

        ADD_SUBDIRECTORY(googletest)

        INCLUDE_DIRECTORIES(
                ${gmock_SOURCE_DIR}/include
                ${gtest_SOURCE_DIR}/include
        )

        ADD_EXECUTABLE(TetrisUnitTests
                ${CMAKE_SOURCE_DIR}/tests/MockForm.cpp
        )

        TARGET_LINK_LIBRARIES(TetrisUnitTests
                gmock_main
                TetrisCore
        )

        ADD_TEST(
                NAME TetrisUnitTests
                COMMAND TetrisUnitTests
        )
ENDIF()

