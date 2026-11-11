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
        "CircleTests.cpp"
        "RectangleTests.cpp"
        "TriangleTests.cpp"
        "StringFigureFactoryTests.cpp"
        "StreamFigureFactoryTests.cpp"
)

catch_discover_tests(unit-tests ADD_TAGS_AS_LABELS)
