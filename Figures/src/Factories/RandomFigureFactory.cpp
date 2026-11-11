#include <cmath>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include "Circle.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "RandomFigureFactory.hpp"

RandomFigureFactory::RandomFigureFactory(std::uint32_t seed) : engine(seed) {}

double RandomFigureFactory::random_length() {
    constexpr double minLength = 1e-100;
    constexpr double maxLength = std::numeric_limits<double>::max() / 16.0;

    std::uniform_real_distribution<double> distribution(std::log(minLength), std::log(maxLength));

    return std::exp(distribution(engine));
}

std::unique_ptr<Figure> RandomFigureFactory::create() {
    std::uniform_int_distribution<int> figureType(0, 2);

    switch (figureType(engine)) {
        case 0:
            return std::make_unique<Circle>(random_length());

        case 1:
            return std::make_unique<Rectangle>(
                random_length(),
                random_length()
            );

        case 2: {
            const double a = random_length();
            const double b = random_length();

            const double larger = std::max(a, b);
            const double smaller = std::min(a, b);

            std::uniform_real_distribution<double> deviation(-0.5, 0.5);

            const double c = larger + deviation(engine) * smaller;

            return std::make_unique<Triangle>(a, b, c);
        }
    }

    throw std::runtime_error("Failed to generate a figure");
}
