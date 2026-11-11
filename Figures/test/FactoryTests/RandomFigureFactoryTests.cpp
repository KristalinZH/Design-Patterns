#include <cmath>
#include <limits>
#include <string>
#include <vector>
#include <cstddef>
#include <sstream>
#include <typeinfo>
#include <algorithm>
#include "Circle.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "catch2/catch_all.hpp"
#include "RandomFigureFactory.hpp"

namespace {
    enum class FigureType {
        Circle,
        Rectangle,
        Triangle
    };

    FigureType get_figure_type(const Figure& figure) {
        if (dynamic_cast<const Circle*>(&figure) != nullptr) {
            return FigureType::Circle;
        }

        if (dynamic_cast<const Rectangle*>(&figure) != nullptr) {
            return FigureType::Rectangle;
        }

        if (dynamic_cast<const Triangle*>(&figure) != nullptr) {
            return FigureType::Triangle;
        }

        FAIL("RandomFigureFactory created an unknown figure type");
        return FigureType::Circle;
    }

    std::vector<double> get_dimensions(const Figure& figure) {
        std::istringstream input;

        switch (get_figure_type(figure)) {
            case FigureType::Circle: {
                const auto& circle = dynamic_cast<const Circle&>(figure);
                input.str(circle.to_string());
                break;
            }

            case FigureType::Rectangle: {
                const auto& rectangle = dynamic_cast<const Rectangle&>(figure);
                input.str(rectangle.to_string());
                break;
            }

            case FigureType::Triangle: {
                const auto& triangle = dynamic_cast<const Triangle&>(figure);
                input.str(triangle.to_string());
                break;
            }
        }

        std::string type;
        input >> type;

        std::vector<double> dimensions;
        double dimension;

        while (input >> dimension) {
            dimensions.push_back(dimension);
        }

        return dimensions;
    }
}

TEST_CASE("RandomFigureFactory creates figures", "[create valid figure]") {
    RandomFigureFactory factory(42);

    auto figure = factory.create();

    REQUIRE(figure != nullptr);
    REQUIRE(std::isfinite(figure->perimeter()));
    REQUIRE(figure->perimeter() > 0.0);
}

TEST_CASE("RandomFigureFactory creates only supported figure types", "[create valid figure]") {
    RandomFigureFactory factory(42);

    for (int i = 0; i < 1000; ++i) {
        auto figure = factory.create();

        REQUIRE(figure != nullptr);

        get_figure_type(*figure);
    }
}

TEST_CASE("RandomFigureFactory generates dimensions within valid ranges", "[create valid figure]") {
    RandomFigureFactory factory(42);

    constexpr double minLength = 1e-100;
    constexpr double maxLength = std::numeric_limits<double>::max() / 16.0;
    constexpr double maxTriangleSide = maxLength * 1.5;

    for (int i = 0; i < 1000; ++i) {
        auto figure = factory.create();

        REQUIRE(figure != nullptr);

        const auto dimensions = get_dimensions(*figure);

        REQUIRE_FALSE(dimensions.empty());

        for (const double dimension : dimensions) {
            REQUIRE(std::isfinite(dimension));
            REQUIRE(dimension >= minLength);

            if (get_figure_type(*figure) == FigureType::Triangle) {
                REQUIRE(dimension <= maxTriangleSide);
            } else {
                REQUIRE(dimension <= maxLength);
            }
        }
    }
}


TEST_CASE("RandomFigureFactory generates valid triangles", "[create valid figure]") {
    RandomFigureFactory factory(42);

    int trianglesCreated = 0;

    for (int i = 0; i < 1000; ++i) {
        auto figure = factory.create();

        if (get_figure_type(*figure) == FigureType::Triangle) {
            ++trianglesCreated;

            const auto dimensions = get_dimensions(*figure);

            REQUIRE(dimensions.size() == 3);

            double smallest = dimensions[0];
            double middle = dimensions[1];
            double largest = dimensions[2];

            if (smallest > middle) {
                std::swap(smallest, middle);
            }

            if (middle > largest) {
                std::swap(middle, largest);
            }

            if (smallest > middle) {
                std::swap(smallest, middle);
            }

            const double diff = largest - middle;
            const double err = (largest - diff) - middle;

            REQUIRE((smallest > diff ||(smallest == diff && err < 0)));

            REQUIRE(std::isfinite(figure->perimeter()));
            REQUIRE(figure->perimeter() > 0.0);
        }
    }

    REQUIRE(trianglesCreated > 0);
}


TEST_CASE("RandomFigureFactory is reproducible with the same seed", "[equal seeds]") {
    RandomFigureFactory firstFactory(12345);
    RandomFigureFactory secondFactory(12345);

    for (int i = 0; i < 100; ++i) {
        auto first = firstFactory.create();
        auto second = secondFactory.create();

        REQUIRE(typeid(*first) == typeid(*second));
        REQUIRE(first->perimeter() == second->perimeter());
    }
}

TEST_CASE("RandomFigureFactory generates an approximately uniform distribution", "[uniform distribution]") {
    RandomFigureFactory factory(42);

    constexpr int sampleSize = 3000;

    int circles = 0;
    int rectangles = 0;
    int triangles = 0;

    for (int i = 0; i < sampleSize; ++i) {
        auto figure = factory.create();

        switch (get_figure_type(*figure)) {
            case FigureType::Circle:
                ++circles;
                break;

            case FigureType::Rectangle:
                ++rectangles;
                break;

            case FigureType::Triangle:
                ++triangles;
                break;
        }
    }

    // При равномерно разпределение очакваме около 1000 от всеки вид.
    // Допускаме отклонение заради случайния характер на генерирането.
    REQUIRE(circles >= 800);
    REQUIRE(circles <= 1200);

    REQUIRE(rectangles >= 800);
    REQUIRE(rectangles <= 1200);

    REQUIRE(triangles >= 800);
    REQUIRE(triangles <= 1200);
}

TEST_CASE("RandomFigureFactory generates both small and large dimensions", "[dimension range]") {
    RandomFigureFactory factory(42);

    constexpr int sampleSize = 3000;

    constexpr double smallThreshold = 1e-50;
    constexpr double largeThreshold = 1e100;

    bool generatedSmallDimension = false;
    bool generatedLargeDimension = false;

    for (int i = 0; i < sampleSize; ++i) {
        auto figure = factory.create();

        const auto dimensions = get_dimensions(*figure);

        for (const double dimension : dimensions) {
            if (dimension < smallThreshold) {
                generatedSmallDimension = true;
            }

            if (dimension > largeThreshold) {
                generatedLargeDimension = true;
            }
        }

        if (generatedSmallDimension && generatedLargeDimension) {
            break;
        }
    }

    REQUIRE(generatedSmallDimension);
    REQUIRE(generatedLargeDimension);
}
