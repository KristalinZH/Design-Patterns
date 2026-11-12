#ifndef INPUT_FACTORY
#define INPUT_FACTORY

#include <memory>
#include <string>
#include "InputMethod.hpp"

class InputFactory {
    public:
        std::unique_ptr<InputMethod> create_input_from_string(const std::string& input_string) const;
};

#endif