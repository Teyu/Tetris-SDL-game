
IF(TETRIS_BUILD_TESTS)
        MESSAGE( "Adding test environment. Type \"make test\" to run unit tests." )

        ADD_SUBDIRECTORY(gtest)

        INCLUDE_DIRECTORIES(
                ${gtest_SOURCE_DIR}/include
                ${gtest_SOURCE_DIR}
        )

        ADD_EXECUTABLE(TetrisUnitTests
                ${CMAKE_SOURCE_DIR}/tests/sample.cpp
        )

        TARGET_LINK_LIBRARIES(TetrisUnitTests
                gtest
                gtest_main
                TetrisCore
        )

        #this enables the add_test command and adds the "test" target to the Makefile. Typing the "make test" command will then run CTest.
        ENABLE_TESTING()

        ADD_TEST(
                NAME TetrisUnitTests
                COMMAND TetrisUnitTests
        )
ENDIF()

