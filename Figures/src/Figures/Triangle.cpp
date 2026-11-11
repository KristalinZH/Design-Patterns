#include <cmath>
#include <limits>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include "Triangle.hpp"
#include "ParamValidation.hpp"

Triangle::Triangle(const double _a, const double _b, const double _c) : a(Validation::positiveFinite(_a)), b(Validation::positiveFinite(_b)), c(Validation::positiveFinite(_c)) {
    double min = a, mid = b, max = c;
    if (min > mid) std::swap(min, mid);
    if (mid > max) std::swap(mid, max);
    if (min > mid) std::swap(min, mid);

    //TwoSum algorithm by Knuth for
    //elimination of subtraction cancellation
    //when max and mid are very close
    const double diff = max - mid;
    const double err  = (max - diff) - mid;

    if (min < diff || (min == diff && err >= 0)) {
        throw std::invalid_argument("Non-existing triangle");
    }
        
    if (!std::isfinite(a + b + c)) {
        throw std::overflow_error("Triangle perimeter overflow");
    }
}

double Triangle::perimeter() const {
    return a + b + c;
}

std::unique_ptr<Figure> Triangle::clone() const {
    return std::make_unique<Triangle>(*this);
}

std::string Triangle::to_string() const {
    std::ostringstream ostr;
    ostr << std::setprecision(std::numeric_limits<double>::max_digits10);
    ostr << "triangle " << a << ' ' << b << ' ' << c;
    return ostr.str();
}