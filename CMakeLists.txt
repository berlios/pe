project(pe)
cmake_minimum_required(VERSION 2.6)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Werror")

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
add_subdirectory(src)

add_library(gtesting gtest_main_custom.cpp)
target_link_libraries(gtesting gtest gmock)

add_library(tasks task_main.cpp)
target_link_libraries(tasks base)
