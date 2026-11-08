macro(find_or_fetch_library)
  cmake_parse_arguments(
    FFL
    ""
    "NAME;GIT_REPOSITORY;GIT_TAG"
    "FIND_PACKAGE_ARGS"
    ${ARGN}
  )

  if(NOT FFL_NAME)
    message(FATAL_ERROR "find_or_fetch_library: NAME is required; use it to pass the name of the library.")
  endif()

  message(STATUS "find_or_fetch_library(): Let's try to find '${FFL_NAME}'...")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")

  set(FFL_LOCAL_COPY "${CMAKE_SOURCE_DIR}/lib/${FFL_NAME}")


  if(EXISTS "${FFL_LOCAL_COPY}")
    message(STATUS "Found '${FFL_NAME}' as a local copy under ${FFL_LOCAL_COPY}")
    add_subdirectory("${FFL_LOCAL_COPY}")

  else()

    message(STATUS "There is no local copy under ./lib/; invoking FetchContent_MakeAvailable...")

    include(FetchContent)

    FetchContent_Declare(
        ${FFL_NAME}
        GIT_REPOSITORY    ${FFL_GIT_REPOSITORY}
        GIT_TAG           ${FFL_GIT_TAG}
        FIND_PACKAGE_ARGS ${FIND_PACKAGE_ARGS}
    )

    FetchContent_MakeAvailable(${FFL_NAME})

  endif()

  message(STATUS "Finished processing. Dumping some variables below:")

  cmake_print_variables(CMAKE_MODULE_PATH)
  cmake_print_variables(${FFL_NAME}_DIR)
  cmake_print_variables(${FFL_NAME}_SOURCE_DIR)
  cmake_print_variables(${FFL_NAME}_FOUND)

  list(POP_BACK CMAKE_MESSAGE_INDENT)

endmacro()
