#include "STDINMethod.hpp"
#include "StreamFigureFactory.hpp"

#include <iostream>

STDINMethod::STDINMethod(const std::string& input) {
    if(input != "STDIN"){
        throw std::invalid_argument("Expected input in format: STDIN");
    }
}

std::string STDINMethod::get_method_name() const {
    return "STDIN";
}

std::unique_ptr<FigureFactory> STDINMethod::create_factory() const {
    return std::make_unique<StreamFigureFactory>(std::cin);
}