#include <stdexcept>
#include "Circle.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "StringFigureFactory.hpp"
#include "catch2/catch_all.hpp"

TEST_CASE("FigureFactory creates figures from valid strings", "[valid figure string formats]") {
    const StringFigureFactory factory;

    SECTION("Circle") {
        auto figure = factory.create_from_string("circle 5");

        REQUIRE(dynamic_cast<Circle*>(figure.get()) != nullptr);
        REQUIRE(figure->perimeter() == Catch::Approx(2.0 * 3.14159265358979323846 * 5.0));
    }

    SECTION("Rectangle") {
        auto figure = factory.create_from_string("rectangle 4 6");

        REQUIRE(dynamic_cast<Rectangle*>(figure.get()) != nullptr);
        REQUIRE(figure->perimeter() == Catch::Approx(20.0));
    }

    SECTION("Triangle") {
        auto figure = factory.create_from_string("triangle 3 4 5");

        REQUIRE(dynamic_cast<Triangle*>(figure.get()) != nullptr);
        REQUIRE(figure->perimeter() == Catch::Approx(12.0));
    }

    SECTION("Whitespace around parameters is accepted") {
        auto figure = factory.create_from_string("   circle   5   ");

        REQUIRE(dynamic_cast<Circle*>(figure.get()) != nullptr);
    }
}

TEST_CASE("FigureFactory rejects invalid strings", "[invalid figure string formats]") {
    const StringFigureFactory factory;

    SECTION("Empty string") {
        REQUIRE_THROWS_AS(
            factory.create_from_string(""),
            std::invalid_argument
        );
    }

    SECTION("Missing figure type") {
        REQUIRE_THROWS_AS(
            factory.create_from_string("   "),
            std::invalid_argument
        );
    }

    SECTION("Unknown figure type") {
        REQUIRE_THROWS_AS(
            factory.create_from_string("pentagon 5 5 5 5 5"),
            std::invalid_argument
        );
    }

    SECTION("Missing circle parameter") {
        REQUIRE_THROWS_AS(
            factory.create_from_string("circle"),
            std::invalid_argument
        );
    }

    SECTION("Missing rectangle parameter") {
        REQUIRE_THROWS_AS(
            factory.create_from_string("rectangle 5"),
            std::invalid_argument
        );
    }

    SECTION("Missing triangle parameter") {
        REQUIRE_THROWS_AS(
            factory.create_from_string("triangle 3 4"),
            std::invalid_argument
        );
    }

    SECTION("Non-numeric parameter") {
        REQUIRE_THROWS_AS(
            factory.create_from_string("circle abc"),
            std::invalid_argument
        );
    }

    SECTION("Too many circle parameters") {
        REQUIRE_THROWS_AS(
            factory.create_from_string("circle 5 10"),
            std::invalid_argument
        );
    }

    SECTION("Too many rectangle parameters") {
        REQUIRE_THROWS_AS(
            factory.create_from_string("rectangle 4 6 8"),
            std::invalid_argument
        );
    }

    SECTION("Too many triangle parameters") {
        REQUIRE_THROWS_AS(
            factory.create_from_string("triangle 3 4 5 6"),
            std::invalid_argument
        );
    }
}

TEST_CASE("FigureFactory delegates figure validation to constructors", "[valid figure strings with invalid values]") {
    const StringFigureFactory factory;

    SECTION("Invalid circle radius") {
        REQUIRE_THROWS_AS(
            factory.create_from_string("circle -5"),
            std::invalid_argument
        );
    }

    SECTION("Invalid rectangle sides") {
        REQUIRE_THROWS_AS(
            factory.create_from_string("rectangle 4 0"),
            std::invalid_argument
        );
    }

    SECTION("Invalid triangle sides") {
        REQUIRE_THROWS_AS(
            factory.create_from_string("triangle 1 2 10"),
            std::invalid_argument
        );
    }

    SECTION("Circle perimeter overflow") {
        REQUIRE_THROWS_AS(
            factory.create_from_string("circle 1e308"),
            std::overflow_error
        );
    }
}
