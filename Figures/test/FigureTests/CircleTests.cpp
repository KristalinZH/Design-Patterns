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

TEST_CASE("Circle clone", "[prototype tests]")
{
    Circle original(5.0);

    SECTION("Clone is not nullptr")
    {
        auto cloned = original.clone();

        REQUIRE(cloned != nullptr);
    }

    SECTION("Clone has the same type")
    {
        auto cloned = original.clone();

        REQUIRE(dynamic_cast<Circle*>(cloned.get()) != nullptr);
    }

    SECTION("Clone has the same perimeter")
    {
        auto cloned = original.clone();

        REQUIRE(cloned->perimeter() == Catch::Approx(original.perimeter()));
    }

    SECTION("Clone is a different object")
    {
        auto cloned = original.clone();

        REQUIRE(cloned.get() != &original);
    }
}

TEST_CASE("Circle can be cloned polymorphically", "[prototype tests]")
{
    std::unique_ptr<Figure> original =
        std::make_unique<Circle>(2.345687);

    auto cloned = original->clone();

    REQUIRE(cloned != nullptr);
    REQUIRE(dynamic_cast<Circle*>(cloned.get()) != nullptr);
    REQUIRE(cloned->perimeter() == Catch::Approx(original->perimeter()));
    REQUIRE(cloned.get() != original.get());
}

TEST_CASE("Circle to_string", "[to_string]")
{
    SECTION("Converts an integer radius")
    {
        Circle circle(5.0);

        REQUIRE(circle.to_string() == "circle 5");
    }

    SECTION("Converts a fractional radius")
    {
        Circle circle(2.5);

        REQUIRE(circle.to_string() == "circle 2.5");
    }

    SECTION("Converts a small radius")
    {
        Circle circle(0.25);

        REQUIRE(circle.to_string() == "circle 0.25");
    }
}

TEST_CASE("Circle to_string preserves double precision", "[to_string]")
{
    SECTION("Handles many decimal digits")
    {
        const double radius = 2.345563254254365435;
        Circle circle(radius);

        std::ostringstream expected;
        expected << std::setprecision(
            std::numeric_limits<double>::max_digits10
        );
        expected << "circle " << radius;

        REQUIRE(circle.to_string() == expected.str());
    }

    SECTION("Handles very small values")
    {
        const double radius = std::numeric_limits<double>::denorm_min();
        Circle circle(radius);

        std::ostringstream expected;
        expected << std::setprecision(
            std::numeric_limits<double>::max_digits10
        );
        expected << "circle " << radius;

        REQUIRE(circle.to_string() == expected.str());
    }

    SECTION("Handles very large values")
    {
        const double radius = std::numeric_limits<double>::max() / 10.0;
        Circle circle(radius);

        std::ostringstream expected;
        expected << std::setprecision(
            std::numeric_limits<double>::max_digits10
        );
        expected << "circle " << radius;

        REQUIRE(circle.to_string() == expected.str());
    }

    SECTION("Can restore the original radius")
    {
        const double radius = 2.345563254254365435;
        Circle circle(radius);

        std::istringstream input(circle.to_string());

        std::string type;
        double restoredRadius;

        input >> type >> restoredRadius;

        REQUIRE(type == "circle");
        REQUIRE(restoredRadius == radius);
    }
}