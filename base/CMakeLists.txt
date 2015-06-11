project(base)

# List all the files here in the alphabetical order

# .h files (headers)
set(BASE_HXX
  common.h
  digit_manipulation.h
  number_theory.h
  pythagorean_triple.h
  task.h
)

# .cpp non-test files
set(BASE_CXX
  common.cpp
  digit_manipulation.cpp
  number_theory.cpp
  task.cpp
)

# *_test.cpp files
set(BASE_TESTS
  common_test.cpp
  digit_manipulation_test.cpp
  number_theory_test.cpp
  pythagorean_triple_test.cpp
)

add_library(base ${BASE_CXX} ${BASE_HXX})
target_link_libraries(base ${LIBGMPXX_LIBRARIES})

add_executable(base_tests ${BASE_TESTS})
target_link_libraries(base_tests base gtesting ${LIBGMPXX_LIBRARIES})
