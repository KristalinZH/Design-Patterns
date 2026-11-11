#include <numbers>
#include <limits>
#include <stdexcept>

#include "catch2/catch_all.hpp"
#include "Circle.hpp"

TEST_CASE("Circle calculates perimeter correctly", "[valid state]") {
    SECTION("Unit circle") {
        Circle circle(1.0);

        REQUIRE(circle.perimeter() == Catch::Approx(
            2.0 * std::numbers::pi
        ));
    }

    SECTION("Circle with integer radius") {
        Circle circle(5.0);

        REQUIRE(circle.perimeter() == Catch::Approx(
            10.0 * std::numbers::pi
        ));
    }

    SECTION("Circle with fractional radius") {
        Circle circle(2.5);

        REQUIRE(circle.perimeter() == Catch::Approx(
            5.0 * std::numbers::pi
        ));
    }

    SECTION("Circle with very small radius") {
        Circle circle(std::numeric_limits<double>::min());

        REQUIRE(std::isfinite(circle.perimeter()));
        REQUIRE(circle.perimeter() > 0.0);
    }

    SECTION("Circle with subnormal radius") {
        Circle circle(std::numeric_limits<double>::denorm_min());

        REQUIRE(std::isfinite(circle.perimeter()));
        REQUIRE(circle.perimeter() > 0.0);
    }
}

TEST_CASE("Circle rejects invalid radius", "[invalid radius]") {
    SECTION("Zero") {
        REQUIRE_THROWS_AS(Circle(0.0), std::invalid_argument);
    }

    SECTION("Negative value") {
        REQUIRE_THROWS_AS(Circle(-1.0), std::invalid_argument);
    }

    SECTION("Negative fractional value") {
        REQUIRE_THROWS_AS(Circle(-0.001), std::invalid_argument);
    }

    SECTION("NaN") {
        REQUIRE_THROWS_AS(
            Circle(std::numeric_limits<double>::quiet_NaN()),
            std::invalid_argument
        );
    }

    SECTION("Positive infinity") {
        REQUIRE_THROWS_AS(
            Circle(std::numeric_limits<double>::infinity()),
            std::invalid_argument
        );
    }

    SECTION("Negative infinity") {
        REQUIRE_THROWS_AS(
            Circle(-std::numeric_limits<double>::infinity()),
            std::invalid_argument
        );
    }
}

TEST_CASE("Circle rejects perimeter overflow", "[perimeter overflow]") {
    SECTION("Maximum double value") {
        REQUIRE_THROWS_AS(
            Circle(std::numeric_limits<double>::max()),
            std::overflow_error
        );
    }

    SECTION("A large finite radius") {
        const double max = std::numeric_limits<double>::max();

        REQUIRE_THROWS_AS(
            Circle(max / 2.0),
            std::overflow_error
        );
    }
}