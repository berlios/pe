find_path(LIBGMPXX_INCLUDE_DIR gmpxx.h)

find_library(LIBGMPXX_LIBRARY gmpxx)
find_library(LIBGMP_LIBRARY gmp)

set(LIBGMPXX_INCLUDE_DIRS ${LIBGMPXX_INCLUDE_DIR})
set(LIBGMPXX_LIBRARIES ${LIBGMPXX_LIBRARY} ${LIBGMP_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GMPXX DEFAULT_MSG
                                  LIBGMPXX_LIBRARY LIBGMPXX_INCLUDE_DIR)

mark_as_advanced(LIBGMPXX_INCLUDE_DIR LIBGMPXX_LIBRARY LIBGMP_LIBRARY)
