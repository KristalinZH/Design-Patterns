#include <cmath>
#include <limits>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "Rectangle.hpp"
#include "ParamValidation.hpp"

Rectangle::Rectangle(const double _a, const double _b) : a(Validation::positiveFinite(_a)), b(Validation::positiveFinite(_b)) {
    if (!std::isfinite(2.0 * (a+b))) {
        throw std::overflow_error("Rectangle perimeter overflow");
    }
}

double Rectangle::perimeter() const {
    return 2.0 * (a+b);
}

std::unique_ptr<Figure> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}

std::string Rectangle::to_string() const {
    std::ostringstream ostr;
    ostr << std::setprecision(std::numeric_limits<double>::max_digits10);
    ostr << "rectangle " << a << ' ' << b;
    return ostr.str();
}