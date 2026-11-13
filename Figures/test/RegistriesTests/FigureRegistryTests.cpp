#include <memory>
#include <random>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "Circle.hpp"
#include "FigureRegistry.hpp"
#include "catch2/catch_all.hpp"

TEST_CASE("FigureRegistry registers and creates figures", "[successful registration]") {
    FigureRegistry& registry = FigureRegistry::instance();

    SECTION("Creates figure from parameters") {
        registry.register_figure(
            "test_circle_from_string",

            [](const std::vector<double>& parameters) {
                if (parameters.size() != 1) {
                    throw std::invalid_argument("Invalid parameters");
                }

                return std::make_unique<Circle>(parameters[0]);
            },

            [](std::mt19937&) {
                return std::make_unique<Circle>(5.0);
            }
        );

        auto figure = registry.create_from_string(
            "test_circle_from_string", {5.0}
        );

        REQUIRE(figure != nullptr);
        REQUIRE(figure->perimeter() == Circle(5.0).perimeter());
    }

    SECTION("Creates random figure") {
        registry.register_figure(
            "test_circle_random",

            [](const std::vector<double>& parameters) {
                if (parameters.size() != 1) {
                    throw std::invalid_argument("Invalid parameters");
                }

                return std::make_unique<Circle>(parameters[0]);
            },

            [](std::mt19937&) {
                return std::make_unique<Circle>(5.0);
            }
        );

        std::mt19937 engine(42);

        auto figure = registry.create_random("test_circle_random", engine);

        REQUIRE(figure != nullptr);
        REQUIRE(figure->perimeter() == Circle(5.0).perimeter());
    }

    SECTION("Returns registered types") {
        registry.register_figure(
            "test_circle_types",

            [](const std::vector<double>&) {
                return std::make_unique<Circle>(5.0);
            },

            [](std::mt19937&) {
                return std::make_unique<Circle>(5.0);
            }
        );

        const auto types = registry.registered_types();

        REQUIRE(
            std::find(
                types.begin(), types.end(), "test_circle_types"
            ) != types.end()
        );
    }
}

TEST_CASE("FigureRegistry rejects invalid registrations", "[unsuccessful registration]") {
    FigureRegistry& registry = FigureRegistry::instance();

    SECTION("Rejects empty name") {
        REQUIRE_THROWS_AS(
            registry.register_figure(
                "",
                [](const std::vector<double>&) {
                    return std::make_unique<Circle>(5.0);
                },
                [](std::mt19937&) {
                    return std::make_unique<Circle>(5.0);
                }
            ),
            std::invalid_argument
        );
    }

    SECTION("Rejects duplicate registration") {
        auto string_creator = [](const std::vector<double>&) {
            return std::make_unique<Circle>(5.0);
        };

        auto random_creator = [](std::mt19937&) {
            return std::make_unique<Circle>(5.0);
        };

        registry.register_figure(
            "test_duplicate_circle",
            string_creator,
            random_creator
        );

        REQUIRE_THROWS_AS(
            registry.register_figure(
                "test_duplicate_circle",
                string_creator,
                random_creator
            ),
            std::invalid_argument
        );
    }

    SECTION("Rejects missing creators") {
        REQUIRE_THROWS_AS(
            registry.register_figure(
                "test_missing_creator",
                {},
                [](std::mt19937&) {
                    return std::make_unique<Circle>(5.0);
                }
            ),
            std::invalid_argument
        );
    }
}

TEST_CASE("FigureRegistry rejects unknown figure types", "[unknown types]") {
    FigureRegistry& registry = FigureRegistry::instance();
    std::mt19937 engine(42);

    REQUIRE_THROWS_AS(
        registry.create_from_string("unknown_figure_type", {5.0}),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        registry.create_random("unknown_figure_type", engine),
        std::invalid_argument
    );
}
