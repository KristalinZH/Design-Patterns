#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Circle.hpp"
#include "STDINMethod.hpp"
#include "FigureFactory.hpp"
#include "catch2/catch_all.hpp"


class CinRedirect {
public:
    explicit CinRedirect(std::istream& new_input)
        : old_buffer(std::cin.rdbuf(new_input.rdbuf())) {}

    ~CinRedirect() {
        std::cin.rdbuf(old_buffer);
        std::cin.clear();
    }

private:
    std::streambuf* old_buffer;
};

TEST_CASE("STDINMethod accepts valid input", "[valid input]") {
    STDINMethod method("STDIN");

    REQUIRE(method.get_method_name() == "STDIN");
}

TEST_CASE("STDINMethod rejects invalid input", "[invlaid input]") {
    REQUIRE_THROWS_AS(
        STDINMethod("stdin"),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        STDINMethod("Random"),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        STDINMethod("STDIN extra"),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        STDINMethod(""),
        std::invalid_argument
    );
}

TEST_CASE("STDINMethod creates a factory that reads from std::cin", "[valid input]") {
    std::istringstream input("circle 5\n");
    CinRedirect redirect(input);

    STDINMethod method("STDIN");
    auto factory = method.create_factory();

    auto figure = factory->create();

    REQUIRE(figure != nullptr);
    REQUIRE(dynamic_cast<Circle*>(figure.get()) != nullptr);
    REQUIRE(figure->perimeter() == Catch::Approx(2.0 * std::numbers::pi * 5.0));
}
