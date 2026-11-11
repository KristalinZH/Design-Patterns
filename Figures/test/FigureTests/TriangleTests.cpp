#include <limits>
#include <stdexcept>

#include "catch2/catch_all.hpp"
#include "Triangle.hpp"

TEST_CASE("Triangle calculates perimeter correctly", "[valid state]") {
    SECTION("Equilateral triangle") {
        Triangle triangle(5.0, 5.0, 5.0);

        REQUIRE(triangle.perimeter() == Catch::Approx(15.0));
    }

    SECTION("Right triangle") {
        Triangle triangle(3.0, 4.0, 5.0);

        REQUIRE(triangle.perimeter() == Catch::Approx(12.0));
    }

    SECTION("Triangle with fractional sides") {
        Triangle triangle(2.5, 3.5, 4.0);

        REQUIRE(triangle.perimeter() == Catch::Approx(10.0));
    }

    SECTION("Triangle with different side lengths") {
        Triangle triangle(7.0, 8.0, 9.0);

        REQUIRE(triangle.perimeter() == Catch::Approx(24.0));
    }

    SECTION("Triangle with very small sides") {
        const double small = std::numeric_limits<double>::min();

        Triangle triangle(small, small, small);

        REQUIRE(std::isfinite(triangle.perimeter()));
        REQUIRE(triangle.perimeter() > 0.0);
    }

    SECTION("Triangle with subnormal sides") {
        const double small = std::numeric_limits<double>::denorm_min();

        Triangle triangle(small, small, small);

        REQUIRE(std::isfinite(triangle.perimeter()));
        REQUIRE(triangle.perimeter() > 0.0);
    }

    SECTION("Triangle with very large sides but finite perimeter") {
        const double large = std::numeric_limits<double>::max() / 4.0;

        Triangle triangle(large, large, large);

        REQUIRE(std::isfinite(triangle.perimeter()));
        REQUIRE(triangle.perimeter() > 0.0);
    }
}

TEST_CASE("Triangle accepts sides in any order", "[valid state side permutations]") {
    SECTION("First permutation") {
        Triangle triangle(3.0, 4.0, 5.0);
        REQUIRE(triangle.perimeter() == Catch::Approx(12.0));
    }

    SECTION("Second permutation") {
        Triangle triangle(3.0, 5.0, 4.0);
        REQUIRE(triangle.perimeter() == Catch::Approx(12.0));
    }

    SECTION("Third permutation") {
        Triangle triangle(4.0, 3.0, 5.0);
        REQUIRE(triangle.perimeter() == Catch::Approx(12.0));
    }

    SECTION("Fourth permutation") {
        Triangle triangle(4.0, 5.0, 3.0);
        REQUIRE(triangle.perimeter() == Catch::Approx(12.0));
    }

    SECTION("Fifth permutation") {
        Triangle triangle(5.0, 3.0, 4.0);
        REQUIRE(triangle.perimeter() == Catch::Approx(12.0));
    }

    SECTION("Sixth permutation") {
        Triangle triangle(5.0, 4.0, 3.0);
        REQUIRE(triangle.perimeter() == Catch::Approx(12.0));
    }
}
TEST_CASE("Triangle rejects invalid sides", "[invalid sides]") {
    SECTION("First side is zero") {
        REQUIRE_THROWS_AS(
            Triangle(0.0, 4.0, 5.0),
            std::invalid_argument
        );
    }

    SECTION("Second side is zero") {
        REQUIRE_THROWS_AS(
            Triangle(3.0, 0.0, 5.0),
            std::invalid_argument
        );
    }

    SECTION("Third side is zero") {
        REQUIRE_THROWS_AS(
            Triangle(3.0, 4.0, 0.0),
            std::invalid_argument
        );
    }

    SECTION("First side is negative") {
        REQUIRE_THROWS_AS(
            Triangle(-3.0, 4.0, 5.0),
            std::invalid_argument
        );
    }

    SECTION("Second side is negative") {
        REQUIRE_THROWS_AS(
            Triangle(3.0, -4.0, 5.0),
            std::invalid_argument
        );
    }

    SECTION("Third side is negative") {
        REQUIRE_THROWS_AS(
            Triangle(3.0, 4.0, -5.0),
            std::invalid_argument
        );
    }

    SECTION("First side is NaN") {
        REQUIRE_THROWS_AS(
            Triangle(
                std::numeric_limits<double>::quiet_NaN(),
                4.0,
                5.0
            ),
            std::invalid_argument
        );
    }

    SECTION("Second side is NaN") {
        REQUIRE_THROWS_AS(
            Triangle(
                3.0,
                std::numeric_limits<double>::quiet_NaN(),
                5.0
            ),
            std::invalid_argument
        );
    }

    SECTION("Third side is NaN") {
        REQUIRE_THROWS_AS(
            Triangle(
                3.0,
                4.0,
                std::numeric_limits<double>::quiet_NaN()
            ),
            std::invalid_argument
        );
    }

    SECTION("First side is infinity") {
        REQUIRE_THROWS_AS(
            Triangle(
                std::numeric_limits<double>::infinity(),
                4.0,
                5.0
            ),
            std::invalid_argument
        );
    }

    SECTION("Second side is infinity") {
        REQUIRE_THROWS_AS(
            Triangle(
                3.0,
                std::numeric_limits<double>::infinity(),
                5.0
            ),
            std::invalid_argument
        );
    }

    SECTION("Third side is negative infinity") {
        REQUIRE_THROWS_AS(
            Triangle(
                3.0,
                4.0,
                -std::numeric_limits<double>::infinity()
            ),
            std::invalid_argument
        );
    }
}

TEST_CASE("Triangle rejects non-existing triangles", "[non-existing triangles]") {
    SECTION("Two smaller sides have a sum smaller than the largest") {
        REQUIRE_THROWS_AS(
            Triangle(2.0, 3.0, 6.0),
            std::invalid_argument
        );
    }

    SECTION("Two smaller sides have a sum equal to the largest") {
        REQUIRE_THROWS_AS(
            Triangle(2.0, 3.0, 5.0),
            std::invalid_argument
        );
    }

    SECTION("Degenerate triangle with equal smaller sides") {
        REQUIRE_THROWS_AS(
            Triangle(3.0, 3.0, 6.0),
            std::invalid_argument
        );
    }

    SECTION("Invalid triangle with sides in different order") {
        REQUIRE_THROWS_AS(
            Triangle(10.0, 3.0, 4.0),
            std::invalid_argument
        );
    }

    SECTION("Another invalid triangle with sides in different order") {
        REQUIRE_THROWS_AS(
            Triangle(4.0, 10.0, 3.0),
            std::invalid_argument
        );
    }

    SECTION("Very small sides cannot form a triangle") {
        const double small = std::numeric_limits<double>::min();

        REQUIRE_THROWS_AS(
            Triangle(small, small, 3.0 * small),
            std::invalid_argument
        );
    }
    
    SECTION("Two smaller sides have a sum smaller than the largest") {
        REQUIRE_THROWS_AS(
            Triangle(2.0, 3.0, 6.0),
            std::invalid_argument
        );
    }

    SECTION("Two smaller sides have a sum equal to the largest") {
        REQUIRE_THROWS_AS(
            Triangle(2.0, 3.0, 5.0),
            std::invalid_argument
        );
    }

    SECTION("Degenerate triangle with equal smaller sides") {
        REQUIRE_THROWS_AS(
            Triangle(3.0, 3.0, 6.0),
            std::invalid_argument
        );
    }

    SECTION("Invalid triangle with sides in different order") {
        REQUIRE_THROWS_AS(
            Triangle(10.0, 3.0, 4.0),
            std::invalid_argument
        );
    }

    SECTION("Another invalid triangle with sides in different order") {
        REQUIRE_THROWS_AS(
            Triangle(4.0, 10.0, 3.0),
            std::invalid_argument
        );
    }

    SECTION("Very small sides cannot form a triangle") {
        const double small = std::numeric_limits<double>::min();

        REQUIRE_THROWS_AS(
            Triangle(small, small, 3.0 * small),
            std::invalid_argument
        );
    }
}

TEST_CASE("Triangle handles values near the triangle inequality boundary", "[boudnary values]") {
    const double boundary = 0.5;
    const double largest = 1.0;

    SECTION("Sides exactly on the boundary are rejected") {
        REQUIRE_THROWS_AS(
            Triangle(boundary, boundary, largest),
            std::invalid_argument
        );
    }

    SECTION("Smallest side slightly below the boundary is rejected") {
        const double side = std::nextafter(
            boundary,
            0.0
        );

        REQUIRE_THROWS_AS(
            Triangle(side, boundary, largest),
            std::invalid_argument
        );
    }

    SECTION("Smallest side slightly above the boundary is accepted") {
        const double side = std::nextafter(
            boundary,
            1.0
        );

        Triangle triangle(side, boundary, largest);

        REQUIRE(std::isfinite(triangle.perimeter()));
        REQUIRE(triangle.perimeter() > 0.0);
    }
}
TEST_CASE("Triangle rejects perimeter overflow", "[perimeter overflow]") {
    const double max = std::numeric_limits<double>::max();

    SECTION("Valid triangle with perimeter overflow") {
        REQUIRE_THROWS_AS(
            Triangle(max / 2.0, max / 2.0, max / 2.0),
            std::overflow_error
        );
    }

    SECTION("Invalid triangle whose perimeter would overflow") {
        REQUIRE_THROWS_AS(
            Triangle(max / 4.0, max / 4.0, max),
            std::invalid_argument
        );
    }
}


TEST_CASE("Triangle clone", "[prototype tests]")
{
    Triangle original(3.0, 4.0, 5.0);

    SECTION("Clone is not nullptr")
    {
        auto cloned = original.clone();

        REQUIRE(cloned != nullptr);
    }

    SECTION("Clone has the same type")
    {
        auto cloned = original.clone();

        REQUIRE(dynamic_cast<Triangle*>(cloned.get()) != nullptr);
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

TEST_CASE("Triangle can be cloned polymorphically", "[prototype tests]")
{
    std::unique_ptr<Figure> original =
        std::make_unique<Triangle>(4.0, 5.5234, 6.0);

    auto cloned = original->clone();

    REQUIRE(cloned != nullptr);
    REQUIRE(dynamic_cast<Triangle*>(cloned.get()) != nullptr);
    REQUIRE(cloned->perimeter() == Catch::Approx(original->perimeter()));
    REQUIRE(cloned.get() != original.get());
}

TEST_CASE("Triangle to_string", "[to_string]")
{
    SECTION("Converts integer sides")
    {
        Triangle triangle(3.0, 4.0, 5.0);

        REQUIRE(triangle.to_string() == "triangle 3 4 5");
    }

    SECTION("Converts fractional sides")
    {
        Triangle triangle(2.5, 3.5, 4.5);

        REQUIRE(triangle.to_string() == "triangle 2.5 3.5 4.5");
    }

    SECTION("Converts equal sides")
    {
        Triangle triangle(5.0, 5.0, 5.0);

        REQUIRE(triangle.to_string() == "triangle 5 5 5");
    }
}

TEST_CASE("Triangle to_string preserves double precision", "[to_string]")
{
    SECTION("Handles many decimal digits")
    {
        const double a = 3.123456789123456789;
        const double b = 4.234567891234567891;
        const double c = 5.345678912345678912;

        Triangle triangle(a, b, c);

        std::ostringstream expected;
        expected << std::setprecision(
            std::numeric_limits<double>::max_digits10
        );
        expected << "triangle " << a << " " << b << " " << c;

        REQUIRE(triangle.to_string() == expected.str());
    }

    SECTION("Can restore the original sides")
    {
        const double a = 3.123456789123456789;
        const double b = 4.234567891234567891;
        const double c = 5.345678912345678912;

        Triangle triangle(a, b, c);

        std::istringstream input(triangle.to_string());

        std::string type;
        double restoredA;
        double restoredB;
        double restoredC;

        input >> type >> restoredA >> restoredB >> restoredC;

        REQUIRE(type == "triangle");
        REQUIRE(restoredA == a);
        REQUIRE(restoredB == b);
        REQUIRE(restoredC == c);
    }
}