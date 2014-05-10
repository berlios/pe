project(base)

# List all the files here in the alphabetical order

# .h files (headers)
set(BASE_HXX
  common.h
  task.h
)

# .cpp non-test files
set(BASE_CXX
  common.cpp
  task.cpp
)

# *_test.cpp files
set(BASE_TESTS
  common_test.cpp
)

add_library(base ${BASE_CXX} ${BASE_HXX})
target_link_libraries(base)

add_executable(base_tests ${BASE_TESTS})
target_link_libraries(base_tests base gtesting)
