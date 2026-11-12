#include <cmath>
#include "RandomMethod.hpp"
#include "FigureFactory.hpp"
#include "catch2/catch_all.hpp"

TEST_CASE("RandomMethod accepts valid input", "[valid input]") {
    RandomMethod method("Random");

    REQUIRE(method.get_method_name() == "Random");

    auto factory = method.create_factory();
    REQUIRE(factory != nullptr);

    auto figure = factory->create();
    REQUIRE(figure != nullptr);
    REQUIRE(std::isfinite(figure->perimeter()));
    REQUIRE(figure->perimeter() > 0.0);
}

TEST_CASE("RandomMethod rejects invalid input", "[invalid input]") {
    REQUIRE_THROWS_AS(
        RandomMethod("random"),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        RandomMethod("STDIN"),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        RandomMethod("Random extra"),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        RandomMethod(""),
        std::invalid_argument
    );
}
