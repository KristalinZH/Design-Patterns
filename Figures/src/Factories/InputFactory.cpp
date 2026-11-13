#include "InputFactory.hpp"
#include "InputMethodRegistry.hpp"
#include "InputMethodRegistration.hpp"

std::unique_ptr<InputMethod> InputFactory::create_input_from_string(const std::string& input_string) const {
    ensure_builtin_input_methods_registered();

    return InputMethodRegistry::instance().create(input_string);
}