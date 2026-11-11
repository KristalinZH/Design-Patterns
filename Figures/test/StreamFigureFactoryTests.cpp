#include <string>
#include <sstream>
#include <stdexcept>
#include "Circle.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "catch2/catch_all.hpp"
#include "StreamFigureFactory.hpp"


TEST_CASE("StreamFigureFactory creates figures from stream", "[successful creation from stream]") {
    SECTION("Creates a circle") {
        std::istringstream input("circle 5\n");
        StreamFigureFactory factory(input);

        auto figure = factory.create();

        REQUIRE(dynamic_cast<Circle*>(figure.get()) != nullptr);
        REQUIRE(figure->perimeter() == Catch::Approx(2.0 * 3.14159265358979323846 * 5.0));
    }

    SECTION("Creates a rectangle") {
        std::istringstream input("rectangle 4 6\n");
        StreamFigureFactory factory(input);

        auto figure = factory.create();

        REQUIRE(dynamic_cast<Rectangle*>(figure.get()) != nullptr);
        REQUIRE(figure->perimeter() == Catch::Approx(20.0));
    }

    SECTION("Creates a triangle") {
        std::istringstream input("triangle 3 4 5\n");
        StreamFigureFactory factory(input);

        auto figure = factory.create();

        REQUIRE(dynamic_cast<Triangle*>(figure.get()) != nullptr);
        REQUIRE(figure->perimeter() == Catch::Approx(12.0));
    }

    SECTION("Creates multiple figures sequentially") {
        std::istringstream input(
            "circle 5\n"
            "rectangle 4 6\n"
            "triangle 3 4 5\n"
        );

        StreamFigureFactory factory(input);

        auto first = factory.create();
        auto second = factory.create();
        auto third = factory.create();

        REQUIRE(dynamic_cast<Circle*>(first.get()) != nullptr);
        REQUIRE(dynamic_cast<Rectangle*>(second.get()) != nullptr);
        REQUIRE(dynamic_cast<Triangle*>(third.get()) != nullptr);
    }
}


TEST_CASE("StreamFigureFactory handles whitespace correctly", "[successful creation from stream]") {
    SECTION("Accepts leading and trailing whitespace") {
        std::istringstream input("   circle   5   \n");
        StreamFigureFactory factory(input);

        auto figure = factory.create();

        REQUIRE(dynamic_cast<Circle*>(figure.get()) != nullptr);
    }

    SECTION("Accepts an empty line only as an invalid representation") {
        std::istringstream input("\n");
        StreamFigureFactory factory(input);

        REQUIRE_THROWS_AS(factory.create(), std::invalid_argument);
    }

    SECTION("Does not skip empty lines") {
        std::istringstream input(
            "circle 5\n"
            "\n"
            "rectangle 4 6\n"
        );

        StreamFigureFactory factory(input);

        auto first = factory.create();
        REQUIRE(dynamic_cast<Circle*>(first.get()) != nullptr);

        REQUIRE_THROWS_AS(factory.create(), std::invalid_argument);

        auto third = factory.create();
        REQUIRE(dynamic_cast<Rectangle*>(third.get()) != nullptr);
    }
}


TEST_CASE("StreamFigureFactory handles end of stream", "[emptying stream]") {
    SECTION("Throws when stream is initially empty") {
        std::istringstream input("");
        StreamFigureFactory factory(input);

        REQUIRE_THROWS_AS(factory.create(), std::out_of_range);
    }

    SECTION("Throws after all figures have been read") {
        std::istringstream input("circle 5\n");
        StreamFigureFactory factory(input);

        auto figure = factory.create();
        REQUIRE(dynamic_cast<Circle*>(figure.get()) != nullptr);

        REQUIRE_THROWS_AS(factory.create(), std::out_of_range);
    }

    SECTION("Reads the last line without a trailing newline") {
        std::istringstream input("circle 5");
        StreamFigureFactory factory(input);

        auto figure = factory.create();

        REQUIRE(dynamic_cast<Circle*>(figure.get()) != nullptr);
        REQUIRE_THROWS_AS(factory.create(), std::out_of_range);
    }

    SECTION("Reads the last line after a newline") {
        std::istringstream input("circle 5\n");
        StreamFigureFactory factory(input);

        auto figure = factory.create();
        REQUIRE(dynamic_cast<Circle*>(figure.get()) != nullptr);

        REQUIRE_THROWS_AS(factory.create(), std::out_of_range);
    }
}


TEST_CASE("StreamFigureFactory handles invalid figure representations", "[invalid figures in stream]") {
    SECTION("Propagates an exception for an unknown figure type") {
        std::istringstream input("pentagon 5 5 5 5 5\n");
        StreamFigureFactory factory(input);

        REQUIRE_THROWS_AS(factory.create(), std::invalid_argument);
    }

    SECTION("Propagates an exception for missing parameters") {
        std::istringstream input("rectangle 5\n");
        StreamFigureFactory factory(input);

        REQUIRE_THROWS_AS(factory.create(), std::invalid_argument);
    }

    SECTION("Propagates an exception for non-numeric parameters") {
        std::istringstream input("circle abc\n");
        StreamFigureFactory factory(input);

        REQUIRE_THROWS_AS(factory.create(), std::invalid_argument);
    }

    SECTION("Propagates constructor validation exceptions") {
        std::istringstream input("triangle 1 2 10\n");
        StreamFigureFactory factory(input);

        REQUIRE_THROWS_AS(factory.create(), std::invalid_argument);
    }
}


TEST_CASE("StreamFigureFactory can continue reading after invalid input", "[invalid figures in stream]") {
    std::istringstream input(
        "circle 5\n"
        "invalid data\n"
        "rectangle 4 6\n"
    );

    StreamFigureFactory factory(input);

    auto first = factory.create();
    REQUIRE(dynamic_cast<Circle*>(first.get()) != nullptr);

    REQUIRE_THROWS_AS(factory.create(), std::invalid_argument);

    auto third = factory.create();
    REQUIRE(dynamic_cast<Rectangle*>(third.get()) != nullptr);
}


TEST_CASE("StreamFigureFactory does not consume subsequent lines when parsing fails", "[parsing failure]") {
    std::istringstream input(
        "circle abc\n"
        "triangle 3 4 5\n"
    );

    StreamFigureFactory factory(input);

    REQUIRE_THROWS_AS(factory.create(), std::invalid_argument);

    auto second = factory.create();
    REQUIRE(dynamic_cast<Triangle*>(second.get()) != nullptr);
}



TEST_CASE("StreamFigureFactory distinguishes end of stream from read errors", "[bad stream]") {
    SECTION("Throws runtime_error when stream has badbit") {
        std::istringstream input("circle 5\n");
        input.setstate(std::ios::badbit);

        StreamFigureFactory factory(input);

        REQUIRE_THROWS_AS(factory.create(), std::runtime_error);
    }
}
