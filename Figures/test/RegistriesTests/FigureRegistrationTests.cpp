#include <cmath>
#include <random>
#include <algorithm>
#include "FigureRegistry.hpp"
#include "catch2/catch_all.hpp"
#include "FigureRegistration.hpp"

TEST_CASE("Builtin figures are registered correctly", "[successful registration]") {
    FigureRegistry& registry = FigureRegistry::instance();

    ensure_builtin_figures_registered();

    SECTION("All expected types are registered") {
        const auto types = registry.registered_types();

        REQUIRE(
            std::find(types.begin(), types.end(), "circle") != types.end()
        );

        REQUIRE(
            std::find(types.begin(), types.end(), "rectangle") != types.end()
        );

        REQUIRE(
            std::find(types.begin(), types.end(), "triangle") != types.end()
        );
    }

    SECTION("Creates all figures from parameters") {
        REQUIRE(
            registry.create_from_string("circle", {5.0})->perimeter() > 0
        );

        REQUIRE(
            registry.create_from_string("rectangle", {2.0, 3.0})->perimeter() > 0
        );

        REQUIRE(
            registry.create_from_string("triangle", {3.0, 4.0, 5.0})->perimeter() > 0
        );
    }

    SECTION("Creates valid random figures") {
        std::mt19937 engine(42);

        for (int i = 0; i < 100; ++i) {
            for (const auto& type : registry.registered_types()) {
                auto figure = registry.create_random(type, engine);

                REQUIRE(figure != nullptr);
                REQUIRE(figure->perimeter() > 0);
                REQUIRE(std::isfinite(figure->perimeter()));
            }
        }
    }
}

TEST_CASE("Builtin figure registration is performed only once", "[successful registration]") {
    FigureRegistry& registry = FigureRegistry::instance();

    REQUIRE_NOTHROW(ensure_builtin_figures_registered());

    const auto types_after_first_call = registry.registered_types();

    REQUIRE(
        std::find(
            types_after_first_call.begin(),
            types_after_first_call.end(),
            "circle"
        ) != types_after_first_call.end()
    );

    REQUIRE(
        std::find(
            types_after_first_call.begin(),
            types_after_first_call.end(),
            "rectangle"
        ) != types_after_first_call.end()
    );

    REQUIRE(
        std::find(
            types_after_first_call.begin(),
            types_after_first_call.end(),
            "triangle"
        ) != types_after_first_call.end()
    );

    REQUIRE_NOTHROW(ensure_builtin_figures_registered());
    REQUIRE_NOTHROW(ensure_builtin_figures_registered());

    REQUIRE(
        registry.registered_types().size() == types_after_first_call.size()
    );
}
