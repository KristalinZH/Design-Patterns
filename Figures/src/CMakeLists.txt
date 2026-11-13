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
        "Factories/StringFigureFactory.hpp"
        "Factories/StreamFigureFactory.hpp"
        "Factories/RandomFigureFactory.hpp"
        "InputMethods/InputMethod.hpp"
        "InputMethods/FileMethod.hpp"
        "InputMethods/RandomMethod.hpp"
        "InputMethods/STDINMethod.hpp"
        "Factories/InputFactory.hpp"
        "Registries/FigureRegistry.hpp"
        "Registries/FigureRegistration.hpp"
        "Registries/InputMethodRegistry.hpp"
        "Registries/InputMethodRegistration.hpp"

        "Figures/Circle.cpp"
        "Figures/Triangle.cpp"
        "Figures/Rectangle.cpp"
        "Figures/Utility/ParamValidation.cpp"
        "Factories/StringFigureFactory.cpp"
        "Factories/StreamFigureFactory.cpp"
        "Factories/RandomFigureFactory.cpp"
        "InputMethods/FileMethod.cpp"
        "InputMethods/RandomMethod.cpp"
        "InputMethods/STDINMethod.cpp"
        "Factories/InputFactory.cpp"
        "Registries/FigureRegistry.cpp"
        "Registries/FigureRegistration.cpp"
        "Registries/InputMethodRegistry.cpp"
        "Registries/InputMethodRegistration.cpp"

)

target_include_directories(
    figureslib
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/InputMethods"
        "${CMAKE_CURRENT_SOURCE_DIR}/Registries"
        "${CMAKE_CURRENT_SOURCE_DIR}/Factories"
        "${CMAKE_CURRENT_SOURCE_DIR}/Figures"
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
