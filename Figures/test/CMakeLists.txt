add_executable(unit-tests)

target_link_libraries(
    unit-tests
    PRIVATE
        figureslib
        Catch2::Catch2WithMain
        myproject::build_options
        myproject::cxx_version
)

target_sources(
    unit-tests
    PRIVATE
        "FigureTests/CircleTests.cpp"
        "FigureTests/RectangleTests.cpp"
        "FigureTests/TriangleTests.cpp"
        "FactoryTests/StringFigureFactoryTests.cpp"
        "FactoryTests/StreamFigureFactoryTests.cpp"
        "FactoryTests/RandomFigureFactoryTests.cpp"
        "InputMethodTests/FileMethodTests.cpp"
        "InputMethodTests/STDINMethodTests.cpp"
        "InputMethodTests/RandomMethodTests.cpp"
        "FactoryTests/InputFactoryTests.cpp"
        "RegistriesTests/FigureRegistryTests.cpp"
        "RegistriesTests/FigureRegistrationTests.cpp"
        "RegistriesTests/InputMethodRegistryTests.cpp"
        "RegistriesTests/InputMethodRegistrationTests.cpp"
)

catch_discover_tests(unit-tests ADD_TAGS_AS_LABELS)
