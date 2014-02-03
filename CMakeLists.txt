project(pe)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
find_package(GMPXX REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(
  ${CMAKE_SOURCE_DIR}/external/gtest/include
  ${CMAKE_SOURCE_DIR}/external/gmock/include
  ${CMAKE_SOURCE_DIR}
)

# It's not needed to add gtest subdirectory since gmock does it automatically.
# However directory with google test must be named "gtest".
add_subdirectory(external/gmock)

add_subdirectory(base)

add_library(gtesting gtest_main_custom.cpp)
target_link_libraries(gtesting gtest gmock)
