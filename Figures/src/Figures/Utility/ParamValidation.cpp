#include <cmath>
#include <stdexcept>
#include "ParamValidation.hpp"

double Validation::positiveFinite(double value)
{
    if (!std::isfinite(value) || value <= 0.0) {
        throw std::invalid_argument(
            "Figure parameters must be positive finite numbers"
        );
    }

    return value;
}