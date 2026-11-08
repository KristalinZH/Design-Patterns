include_guard(GLOBAL)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_library(myproject_build_options INTERFACE)
add_library(myproject::build_options ALIAS myproject_build_options)

target_compile_options(myproject_build_options INTERFACE
    "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/MP>"
    "$<$<COMPILE_LANG_AND_ID:CXX,GNU>:-Wall;-Wextra;-Wpedantic>"
)

add_library(myproject_cxx_version INTERFACE)
add_library(myproject::cxx_version ALIAS myproject_cxx_version)
target_compile_features(myproject_cxx_version INTERFACE cxx_std_20)
