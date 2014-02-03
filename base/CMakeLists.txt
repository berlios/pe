project(base)

# List all the files here in the alphabetical order

# .h files (headers)
set(BASE_CXX
  mp.cpp
)

# .cpp non-test files
set(BASE_HXX
  mp.h
)

# *_test.cpp files
set(BASE_TESTS
  mp_test.cpp
)

add_library(base ${BASE_CXX} ${BASE_HXX})
add_executable(base_tests ${BASE_TESTS})
target_link_libraries(base_tests base gtesting ${GMPXX_LIBRARY})
