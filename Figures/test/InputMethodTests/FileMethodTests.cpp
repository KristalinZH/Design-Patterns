#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "Circle.hpp"
#include "FileMethod.hpp"
#include "FigureFactory.hpp"
#include "catch2/catch_all.hpp"

TEST_CASE("FileMethod accepts valid input and creates a factory", "[valid input]") {
    const auto file_path =
        std::filesystem::temp_directory_path() /
        "figures_factory_method_test.txt";

    {
        std::ofstream file(file_path);
        REQUIRE(file.is_open());

        file << "circle 5\n";
    }

    FileMethod method("File " + file_path.string());

    REQUIRE(method.get_method_name() == "File");

    auto factory = method.create_factory();
    REQUIRE(factory != nullptr);

    auto figure = factory->create();

    REQUIRE(figure != nullptr);
    REQUIRE(dynamic_cast<Circle*>(figure.get()) != nullptr);
    REQUIRE(figure->perimeter() == Catch::Approx(2.0 * std::numbers::pi * 5.0));

    std::filesystem::remove(file_path);
}

TEST_CASE("FileMethod rejects invalid input format", "[invalid input]") {
    REQUIRE_THROWS_AS(
        FileMethod(""),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        FileMethod("Random"),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        FileMethod("File"),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        FileMethod("File   "),
        std::invalid_argument
    );
}

TEST_CASE("FileMethod rejects a file that cannot be opened", "[invalid input]") {
    const auto missing_file =
        std::filesystem::temp_directory_path() /
        "this_file_should_not_exist_12345.txt";

    REQUIRE_THROWS_AS(
        FileMethod("File " + missing_file.string()),
        std::runtime_error
    );
}