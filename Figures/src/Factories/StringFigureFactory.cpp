#include <vector>
#include <sstream>
#include <stdexcept>
#include "FigureRegistration.hpp"
#include "StringFigureFactory.hpp"

// std::unique_ptr<Figure> StringFigureFactory::create_from_string(const std::string& representation) const {
//     std::istringstream input(representation);

//     std::string figureType;

//     if (!(input >> figureType)) {
//         throw std::invalid_argument("Missing figure type");
//     }

//     double a, b, c;

//     if (figureType == "circle") {
//         if (!(input >> a)) {
//             throw std::invalid_argument("Invalid parameters for circle");
//         }

//         std::string extra;
//         if (input >> extra) {
//             throw std::invalid_argument("Too many parameters for circle");
//         }

//         return std::make_unique<Circle>(a);
//     }

//     if (figureType == "rectangle") {
//         if (!(input >> a >> b)) {
//             throw std::invalid_argument("Invalid parameters for rectangle");
//         }

//         std::string extra;
//         if (input >> extra) {
//             throw std::invalid_argument("Too many parameters for rectangle");
//         }

//         return std::make_unique<Rectangle>(a, b);
//     }

//     if (figureType == "triangle") {
//         if (!(input >> a >> b >> c)) {
//             throw std::invalid_argument("Invalid parameters for triangle");
//         }

//         std::string extra;
//         if (input >> extra) {
//             throw std::invalid_argument("Too many parameters for triangle");
//         }

//         return std::make_unique<Triangle>(a, b, c);
//     }

//     throw std::invalid_argument("Unknown figure type: " + figureType);
// }

std::unique_ptr<Figure> StringFigureFactory::create_from_string(const std::string& representation) const {
    ensure_builtin_figures_registered();
    std::istringstream input(representation);

    std::string figure_type;

    if (!(input >> figure_type)) {
        throw std::invalid_argument("Empty figure representation");
    }

    std::vector<double> parameters;
    double parameter;

    while (input >> parameter) {
        parameters.push_back(parameter);
    }

    if (!input.eof()) {
        throw std::invalid_argument("Invalid figure parameters");
    }

    return FigureRegistry::instance().create_from_string(
        figure_type,
        parameters
    );
}