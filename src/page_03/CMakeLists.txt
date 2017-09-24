# List all the files here in the alphabetical order
set(PAGE_03_CXX
  task101.cpp
)

add_library(page_03 ${PAGE_03_CXX})
target_link_libraries(page_03 base gtest ${LIBGMPXX_LIBRARIES} eigen)

