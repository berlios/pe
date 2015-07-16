project(src)

# List all the files here in the alphabetical order

# .h files (headers)
set(SRC_HXX
)

# .cpp non-test files
set(SRC_CXX
  task01.cpp
  task02.cpp
  task03.cpp
  task04.cpp
  task05.cpp
  task06.cpp
  task07.cpp
  task08.cpp
  task10.cpp
  task11.cpp
  task12.cpp
  task13.cpp
  task14.cpp
  task15.cpp
  task16.cpp
  task17.cpp
  task18.cpp
  task19.cpp
  task20.cpp
  task21.cpp
  task22.cpp
  task23.cpp
  task25.cpp
  task26.cpp
  task27.cpp
  task28.cpp
  task29.cpp
  task30.cpp
  task31.cpp
  task32.cpp
  task33.cpp
  task34.cpp
  task35.cpp
  task36.cpp
  task37.cpp
  task38.cpp
  task39.cpp
  task40.cpp
  task41.cpp
  task42.cpp
  task43.cpp
)

# *_test.cpp files
set(SRC_TESTS
)

add_executable(out task_main.cpp ${SRC_CXX} ${SRC_HXX})
target_link_libraries(out base gtest ${LIBGMPXX_LIBRARIES})

add_executable(src_tests ${SRC_CXX} ${SRC_HXX} ${SRC_TESTS})
target_link_libraries(src_tests base gtest_main ${LIBGMPXX_LIBRARIES})
