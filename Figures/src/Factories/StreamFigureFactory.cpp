#include <string>
#include <stdexcept>

#include "StreamFigureFactory.hpp"

StreamFigureFactory::StreamFigureFactory(std::istream& _input) : input(_input) {}

std::unique_ptr<Figure> StreamFigureFactory::create() {
    std::string representation;

    if (!std::getline(input, representation)) {
        if (input.eof()) {
            throw std::out_of_range("No more figures available in stream");
        }

        throw std::runtime_error("Failed to read from input stream");
    }

    return stringFactory.create_from_string(representation);
}
