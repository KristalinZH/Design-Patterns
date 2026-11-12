#include <stdexcept>
#include "RandomMethod.hpp"
#include "RandomFigureFactory.hpp"

RandomMethod::RandomMethod(const std::string& input) {
    if(input != "Random") {
        throw std::invalid_argument("Expected input in format: Random");
    }
}

std::string RandomMethod::get_method_name() const {
    return "Random";
}

std::unique_ptr<FigureFactory> RandomMethod::create_factory() const {
    return std::make_unique<RandomFigureFactory>();
}