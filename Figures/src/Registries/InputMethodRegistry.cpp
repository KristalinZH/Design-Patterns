#include <sstream>
#include <utility>
#include <stdexcept>
#include "InputMethodRegistry.hpp"

InputMethodRegistry& InputMethodRegistry::instance() {
    static InputMethodRegistry registry;
    return registry;
}

void InputMethodRegistry::register_method(const std::string& name, MethodCreator creator) {
    if (name.empty()) {
        throw std::invalid_argument("Method name cannot be empty");
    }

    if (!creator) {
        throw std::invalid_argument("Method creator cannot be empty");
    }

    const auto [iterator, inserted] = creators.emplace(name, std::move(creator));

    if (!inserted) {
        throw std::invalid_argument("Method is already registered: " + name);
    }
}

std::unique_ptr<InputMethod> InputMethodRegistry::create(const std::string& input) const {
    std::istringstream input_stream(input);

    std::string method_name;

    if (!(input_stream >> method_name)) {
        throw std::invalid_argument("Input method cannot be empty");
    }

    const auto iterator = creators.find(method_name);

    if (iterator == creators.end()) {
        throw std::invalid_argument("Unknown input method: " + method_name);
    }

    return iterator->second(input);
}
