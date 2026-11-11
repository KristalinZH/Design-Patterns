add_library(figureslib STATIC)

set_target_properties(figureslib PROPERTIES OUTPUT_NAME "figureslib")

target_sources(
    figureslib
    PRIVATE
        "Figures/Figure.hpp"
        "Figures/Circle.hpp"
        "Figures/Triangle.hpp"
        "Figures/Rectangle.hpp"
        "Figures/Utility/ParamValidation.hpp"
        "Figures/StringConvertible.hpp"
        "Figures/Circle.cpp"
        "Figures/Triangle.cpp"
        "Figures/Rectangle.cpp"
        "Figures/Utility/ParamValidation.cpp"

)

target_include_directories(
    figureslib
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Figures"
        "${CMAKE_CURRENT_SOURCE_DIR}/IO"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Figures/Utility"
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
        "app.cpp"
)

target_link_libraries(
    figuresapp
    PRIVATE
        figureslib
        myproject::build_options
        myproject::cxx_version
)
