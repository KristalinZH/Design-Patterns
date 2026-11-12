#include <fstream>
#include <stdexcept>
#include <filesystem>
#include "FileMethod.hpp"
#include "STDINMethod.hpp"
#include "InputFactory.hpp"
#include "RandomMethod.hpp"
#include "catch2/catch_all.hpp"

TEST_CASE("InputFactory creates RandomMethod", "[valid input]") {
    InputFactory factory;

    auto input = factory.create_input_from_string("Random");

    REQUIRE(input != nullptr);
    REQUIRE(dynamic_cast<RandomMethod*>(input.get()) != nullptr);
}

TEST_CASE("InputFactory rejects invalid Random input", "[invalid input]") {
    InputFactory factory;

    REQUIRE_THROWS_AS(
        factory.create_input_from_string("Random extra"),
        std::invalid_argument
    );
}

TEST_CASE("InputFactory creates STDINMethod", "[valid input]") {
    InputFactory factory;

    auto input = factory.create_input_from_string("STDIN");

    REQUIRE(input != nullptr);
    REQUIRE(dynamic_cast<STDINMethod*>(input.get()) != nullptr);
}

TEST_CASE("InputFactory rejects invalid STDIN input") {
    InputFactory factory;

    REQUIRE_THROWS_AS(
        factory.create_input_from_string("STDIN extra"),
        std::invalid_argument
    );
}

TEST_CASE("InputFactory creates FileMethod", "[valid input]") {
    InputFactory factory;

    const auto file_path =
        std::filesystem::temp_directory_path() /
        "input_factory_test.txt";

    {
        std::ofstream file(file_path);
        REQUIRE(file.is_open());
        file << "circle 5\n";
    }

    auto input = factory.create_input_from_string(
        "File " + file_path.string()
    );

    REQUIRE(input != nullptr);
    REQUIRE(dynamic_cast<FileMethod*>(input.get()) != nullptr);

    std::filesystem::remove(file_path);
}

TEST_CASE("InputFactory rejects File without filename", "[invalid input]") {
    InputFactory factory;

    REQUIRE_THROWS_AS(
        factory.create_input_from_string("File"),
        std::invalid_argument
    );
}

TEST_CASE("InputFactory rejects unknown input method", "[invalid input]") {
    InputFactory factory;

    REQUIRE_THROWS_AS(
        factory.create_input_from_string("Unknown"),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        factory.create_input_from_string(""),
        std::invalid_argument
    );
}