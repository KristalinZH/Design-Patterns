#include <stdexcept>
#include "FileMethod.hpp"
#include "STDINMethod.hpp"
#include "RandomMethod.hpp"
#include "InputFactory.hpp"

std::unique_ptr<InputMethod> InputFactory::create_input_from_string(const std::string& input_string) const {
    if(input_string.starts_with("Random")){
        return std::make_unique<RandomMethod>(input_string);
    }

    if(input_string.starts_with("STDIN")){
        return std::make_unique<STDINMethod>(input_string);
    }

    if(input_string.starts_with("File")){
        return std::make_unique<FileMethod>(input_string);
    }

    throw std::invalid_argument("Non-existent input method");
}