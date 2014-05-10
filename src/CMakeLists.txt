project(src)

# List all the files here in the alphabetical order

# .h files (headers)
set(SRC_HXX
)

# .cpp non-test files
set(SRC_CXX
  task1.cpp
  task2.cpp
  task3.cpp
  task4.cpp
  task5.cpp
  task6.cpp
  task7.cpp
  task8.cpp
  task10.cpp
  task11.cpp
  task12.cpp
  task13.cpp
  task14.cpp
  task15.cpp
  task16.cpp
  task17.cpp
  task18.cpp
)

# *_test.cpp files
set(SRC_TESTS
)

add_executable(out ${SRC_CXX} ${SRC_HXX})
target_link_libraries(out tasks gtest ${LIBGMPXX_LIBRARIES})

add_executable(src_tests ${SRC_CXX} ${SRC_TESTS})
target_link_libraries(src_tests base gtesting ${LIBGMPXX_LIBRARIES})
