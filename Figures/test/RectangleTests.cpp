#include <limits>
#include <stdexcept>

#include "catch2/catch_all.hpp"
#include "Rectangle.hpp"

TEST_CASE("Rectangle calculates perimeter correctly", "[valid state]") {
    SECTION("Square") {
        Rectangle rectangle(5.0, 5.0);

        REQUIRE(rectangle.perimeter() == Catch::Approx(20.0));
    }

    SECTION("Regular rectangle") {
        Rectangle rectangle(4.0, 6.0);

        REQUIRE(rectangle.perimeter() == Catch::Approx(20.0));
    }

    SECTION("Rectangle with fractional sides") {
        Rectangle rectangle(2.5, 3.5);

        REQUIRE(rectangle.perimeter() == Catch::Approx(12.0));
    }

    SECTION("Rectangle with very different sides") {
        Rectangle rectangle(0.25, 1000.0);

        REQUIRE(rectangle.perimeter() == Catch::Approx(2000.5));
    }

    SECTION("Rectangle with very small sides") {
        Rectangle rectangle(
            std::numeric_limits<double>::min(),
            std::numeric_limits<double>::min()
        );

        REQUIRE(std::isfinite(rectangle.perimeter()));
        REQUIRE(rectangle.perimeter() > 0.0);
    }

    SECTION("Rectangle with subnormal sides") {
        const double small = std::numeric_limits<double>::denorm_min();

        Rectangle rectangle(small, small);

        REQUIRE(std::isfinite(rectangle.perimeter()));
        REQUIRE(rectangle.perimeter() > 0.0);
    }
}

TEST_CASE("Rectangle rejects invalid sides", "[invalid sides]") {
    SECTION("First side is zero") {
        REQUIRE_THROWS_AS(
            Rectangle(0.0, 5.0),
            std::invalid_argument
        );
    }

    SECTION("Second side is zero") {
        REQUIRE_THROWS_AS(
            Rectangle(5.0, 0.0),
            std::invalid_argument
        );
    }

    SECTION("First side is negative") {
        REQUIRE_THROWS_AS(
            Rectangle(-5.0, 3.0),
            std::invalid_argument
        );
    }

    SECTION("Second side is negative") {
        REQUIRE_THROWS_AS(
            Rectangle(5.0, -3.0),
            std::invalid_argument
        );
    }

    SECTION("First side is NaN") {
        REQUIRE_THROWS_AS(
            Rectangle(
                std::numeric_limits<double>::quiet_NaN(),
                5.0
            ),
            std::invalid_argument
        );
    }

    SECTION("Second side is NaN") {
        REQUIRE_THROWS_AS(
            Rectangle(
                5.0,
                std::numeric_limits<double>::quiet_NaN()
            ),
            std::invalid_argument
        );
    }

    SECTION("First side is infinity") {
        REQUIRE_THROWS_AS(
            Rectangle(
                std::numeric_limits<double>::infinity(),
                5.0
            ),
            std::invalid_argument
        );
    }

    SECTION("Second side is negative infinity") {
        REQUIRE_THROWS_AS(
            Rectangle(
                5.0,
                -std::numeric_limits<double>::infinity()
            ),
            std::invalid_argument
        );
    }
}

TEST_CASE("Rectangle rejects perimeter overflow", "[perimeter overflow]") {
    const double max = std::numeric_limits<double>::max();

    SECTION("Both sides are half of maximum double") {
        REQUIRE_THROWS_AS(
            Rectangle(max / 2.0, max / 2.0),
            std::overflow_error
        );
    }

    SECTION("Both sides are maximum double") {
        REQUIRE_THROWS_AS(
            Rectangle(max, max),
            std::overflow_error
        );
    }
}