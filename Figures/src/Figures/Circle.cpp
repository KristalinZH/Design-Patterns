#include <cmath>
#include <limits>
#include <numbers>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "Circle.hpp"
#include "ParamValidation.hpp"

Circle::Circle(const double _radius) : radius(Validation::positiveFinite(_radius)) {
    if (!std::isfinite(2.0 * std::numbers::pi * radius)) {
        throw std::overflow_error("Circle perimeter overflow");
    }
}

double Circle::perimeter() const {
    return 2.0 * std::numbers::pi * radius;
}

std::unique_ptr<Figure> Circle::clone() const {
    return std::make_unique<Circle>(*this);
}

std::string Circle::to_string() const {
    std::ostringstream ostr;
    ostr << std::setprecision(std::numeric_limits<double>::max_digits10);
    ostr << "circle " << radius;
    return ostr.str();
}