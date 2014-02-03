find_path(LIBGMP_INCLUDE_DIR gmp.h)

find_library(LIBGMP_LIBRARY gmp)

set(LIBGMP_INCLUDE_DIRS ${LIBGMP_INCLUDE_DIR})
set(LIBGMP_LIBRARIES ${LIBGMP_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GMP DEFAULT_MSG
                                  LIBGMP_LIBRARY LIBGMP_INCLUDE_DIR)

mark_as_advanced(LIBGMP_INCLUDE_DIR LIBGMP_LIBRARY)
