#include <cmath>
#include <mutex>
#include <limits>
#include <random>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "FigureRegistration.hpp"

namespace {

    double generate_random_length(std::mt19937& engine) {
        constexpr double min_length = 1e-100;
        constexpr double max_length = std::numeric_limits<double>::max() / 16.0;

        std::uniform_real_distribution<double> distribution(std::log(min_length), std::log(max_length));

        return std::exp(distribution(engine));
    }

    void register_circle(FigureRegistry& registry) {
        registry.register_figure(
            "circle",

            [](const std::vector<double>& parameters) {
                if (parameters.size() != 1) {
                    throw std::invalid_argument(
                        "Circle requires exactly one parameter"
                    );
                }

                return std::make_unique<Circle>(parameters[0]);
            },

            [](std::mt19937& engine) {
                return std::make_unique<Circle>(
                    generate_random_length(engine)
                );
            }
        );
    }

    void register_rectangle(FigureRegistry& registry) {
        registry.register_figure(
            "rectangle",

            [](const std::vector<double>& parameters) {
                if (parameters.size() != 2) {
                    throw std::invalid_argument(
                        "Rectangle requires exactly two parameters"
                    );
                }

                return std::make_unique<Rectangle>(
                    parameters[0],
                    parameters[1]
                );
            },

            [](std::mt19937& engine) {
                return std::make_unique<Rectangle>(
                    generate_random_length(engine),
                    generate_random_length(engine)
                );
            }
        );
    }

    void register_triangle(FigureRegistry& registry) {
        registry.register_figure(
            "triangle",

            [](const std::vector<double>& parameters) {
                if (parameters.size() != 3) {
                    throw std::invalid_argument(
                        "Triangle requires exactly three parameters"
                    );
                }

                return std::make_unique<Triangle>(
                    parameters[0],
                    parameters[1],
                    parameters[2]
                );
            },

            [](std::mt19937& engine) {
                const double a = generate_random_length(engine);
                const double b = generate_random_length(engine);

                const double larger = std::max(a, b);
                const double smaller = std::min(a, b);

                std::uniform_real_distribution<double> deviation(-0.5, 0.5);

                const double c = larger + deviation(engine) * smaller;

                return std::make_unique<Triangle>(a, b, c);
            }
        );
    }
}

void register_builtin_figures(FigureRegistry& registry) {
    register_circle(registry);
    register_rectangle(registry);
    register_triangle(registry);
}

void ensure_builtin_figures_registered() {
    static std::once_flag registration_flag;

    std::call_once(registration_flag, []() {
        register_builtin_figures(FigureRegistry::instance());
    });
}