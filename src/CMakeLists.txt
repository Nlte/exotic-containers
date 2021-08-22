# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Declare header only library
add_library(containers INTERFACE)

# Add header files
target_include_directories(containers INTERFACE ../include)

# All users of this library will need at least C++17
target_compile_features(containers INTERFACE cxx_std_17)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
