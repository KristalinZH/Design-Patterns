#ifndef INPUT_METHOD_REGISTRATION
#define INPUT_METHOD_REGISTRATION

#include "InputMethodRegistry.hpp"

void register_builtin_input_methods(InputMethodRegistry& registry);

void ensure_builtin_input_methods_registered();

#endif
