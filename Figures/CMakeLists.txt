cmake_minimum_required (VERSION 3.24)

project (Figures VERSION 1.4 LANGUAGES CXX)

include(CMakePrintHelpers)

cmake_print_variables(
    CMAKE_MODULE_PATH
    CMAKE_PREFIX_PATH
    CMAKE_INSTALL_PREFIX
)

include(cmake/ProjectSettings.cmake)
include(cmake/Dependencies.cmake)

include_directories("src")

include(CTest)

if(BUILD_TESTING)
    include(cmake/Testing.cmake)
endif()

add_subdirectory(src)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()