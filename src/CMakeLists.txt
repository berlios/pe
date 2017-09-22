project(src)

# List all the files here in the alphabetical order

# .h files (headers)
set(SRC_HXX
)

# .cpp non-test files
set(SRC_CXX
  task001.cpp
  task002.cpp
  task003.cpp
  task004.cpp
  task005.cpp
  task006.cpp
  task007.cpp
  task008.cpp
  task010.cpp
  task011.cpp
  task012.cpp
  task013.cpp
  task014.cpp
  task015.cpp
  task016.cpp
  task017.cpp
  task018.cpp
  task019.cpp
  task020.cpp
  task021.cpp
  task022.cpp
  task023.cpp
  task025.cpp
  task026.cpp
  task027.cpp
  task028.cpp
  task029.cpp
  task030.cpp
  task031.cpp
  task032.cpp
  task033.cpp
  task034.cpp
  task035.cpp
  task036.cpp
  task037.cpp
  task038.cpp
  task039.cpp
  task040.cpp
  task041.cpp
  task042.cpp
  task043.cpp
  task044.cpp
  task045.cpp
  task046.cpp
  task047.cpp
  task048.cpp
  task049.cpp
  task050.cpp
  task051.cpp
  task052.cpp
  task053.cpp
  task054.cpp
  task055.cpp
  task056.cpp
  task057.cpp
  task058.cpp
  task059.cpp
  task060.cpp
  task061.cpp
  task062.cpp
  task063.cpp
  task064.cpp
  task065.cpp
  task066.cpp
  task067.cpp
  task068.cpp
  task069.cpp
  task070.cpp
  task071.cpp
  task072.cpp
  task073.cpp
  task074.cpp
  task075.cpp
  task076.cpp
  task077.cpp
  task078.cpp
  task079.cpp
  task080.cpp
  task081.cpp
  task082.cpp
  task083.cpp
  task084.cpp
  task085.cpp
  task086.cpp
  task087.cpp
  task088.cpp
  task089.cpp
  task090.cpp
  task091.cpp
  task092.cpp
  task093.cpp
  task094.cpp
  task095.cpp
  task096.cpp
  task097.cpp
  task098.cpp
  task099.cpp
)

# *_test.cpp files
set(SRC_TESTS
)

add_executable(out task_main.cpp ${SRC_CXX} ${SRC_HXX})
target_link_libraries(out base gtest ${LIBGMPXX_LIBRARIES})
target_include_directories(out PUBLIC ${CMAKE_SOURCE_DIR}/external/eigen)

add_custom_command(TARGET out PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data)

add_executable(src_tests ${SRC_CXX} ${SRC_HXX} ${SRC_TESTS})
target_link_libraries(src_tests base gtest_main ${LIBGMPXX_LIBRARIES})
target_include_directories(src_tests PUBLIC ${CMAKE_SOURCE_DIR}/external/eigen)
