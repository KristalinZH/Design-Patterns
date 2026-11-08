include_guard(GLOBAL)

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.16.1
    FIND_PACKAGE_ARGS 3 CONFIG QUIET
)

FetchContent_MakeAvailable(Catch2)


if(EXISTS "${catch2_SOURCE_DIR}/extras/Catch.cmake")
    list(PREPEND CMAKE_MODULE_PATH
        "${catch2_SOURCE_DIR}/extras"
    )
endif()

include(Catch)
