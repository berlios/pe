add_subdirectory(page_01)
add_subdirectory(page_02)
add_subdirectory(page_03)

add_executable(out task_main.cpp)
target_link_libraries(out
  "-Wl,--whole-archive" page_01 page_02 page_03 "-Wl,--no-whole-archive"
)

add_custom_command(TARGET out PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data)

add_executable(src_tests gtest_main.cpp)
target_link_libraries(src_tests
  gtest
  "-Wl,--whole-archive" page_01 page_02 page_03 "-Wl,--no-whole-archive"
)
