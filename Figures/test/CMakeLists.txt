# Executable target for the unit tests
add_executable(unit-tests)

target_link_libraries(
    unit-tests
    PRIVATE
        figureslib
        Catch2::Catch2WithMain
        myproject::build_options
)

target_sources(
    unit-tests
    PRIVATE
        ""
)

catch_discover_tests(unit-tests ADD_TAGS_AS_LABELS)
