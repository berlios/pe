cmake_minimum_required(VERSION 3.1)
project(pe)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wpedantic -Werror")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
find_package(GMPXX REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(external/googletest)

add_library(eigen INTERFACE)
target_include_directories(eigen INTERFACE external/eigen)

add_subdirectory(base)
add_subdirectory(src)
