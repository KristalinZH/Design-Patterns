#include <sstream>
#include <stdexcept>
#include "FileMethod.hpp"
#include "StreamFigureFactory.hpp"

FileMethod::FileMethod(const std::string& input) {
    std::istringstream input_stream(input);

    std::string method, filename;

    if (!(input_stream >> method) || method != "File") {
        throw std::invalid_argument("Expected input in format: File <filename>");
    }

    std::getline(input_stream >> std::ws, filename);

    if (filename.empty()) {
        throw std::invalid_argument("Missing filename");
    }

    stream = std::make_unique<std::ifstream>(filename);

    if (!stream->is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

}

std::string FileMethod::get_method_name() const {
    return "File";
} 

std::unique_ptr<FigureFactory> FileMethod::create_factory() const {
    return std::make_unique<StreamFigureFactory>(*stream);
}