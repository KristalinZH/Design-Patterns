#include <cmath>
#include <numbers>
#include <stdexcept>
#include "Circle.hpp"
#include "ParamValidation.hpp"

Circle:: Circle(const double _radius) : radius(Validation::positiveFinite(_radius)){
    if (!std::isfinite(2.0 * std::numbers::pi * radius)) {
        throw std::overflow_error("Circle perimeter overflow");
    }
}

double Circle::perimeter() const {
    return 2.0 * std::numbers::pi * radius;
}
