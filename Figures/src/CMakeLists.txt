# Sample static library
add_library(figureslib STATIC)

set_target_properties(figureslib PROPERTIES OUTPUT_NAME "figureslib")

target_sources(
    figureslib
    PRIVATE
        "library.cpp"
        "library.h"
)

target_link_libraries(
    figureslib
    PRIVATE
        myproject::build_options
        myproject::cxx_version
)

add_executable(figuresapp)

set_target_properties(figuresapp PROPERTIES OUTPUT_NAME "figures")

target_sources(
    figuresapp
    PRIVATE
        ""
)

target_link_libraries(
    figuresapp
    PRIVATE
        figureslib
        myproject::build_options
        myproject::cxx_version
)
