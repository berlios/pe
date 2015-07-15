project(pe)
cmake_minimum_required(VERSION 2.6)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
find_package(GMPXX REQUIRED)

include_directories(
  ${CMAKE_SOURCE_DIR}/external/gtest/include
  ${CMAKE_SOURCE_DIR}/external/gmock/include
  ${CMAKE_SOURCE_DIR}
)

# It's not needed to add gtest subdirectory since gmock does it automatically.
# However directory with google test must be named "gtest".
add_subdirectory(external/gmock)

add_subdirectory(base)
add_subdirectory(src)
