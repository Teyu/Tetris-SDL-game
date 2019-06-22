cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)

project(Sylwia)
set (SYLWIA_VERSION_MAJOR 1)
set (SYLWIA_VERSION_MINOR 0)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "Please create an out-of-source build.")
endif()

file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR}/src)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "CLANG")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
endif()

configure_file (
  "${PROJECT_SOURCE_DIR}/SylwiaConfig.h.in"
  "${PROJECT_BINARY_DIR}/SylwiaConfig.h"
)
include_directories(${PROJECT_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(thirdparty)
