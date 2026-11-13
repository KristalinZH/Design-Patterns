#include <mutex>
#include "FileMethod.hpp"
#include "STDINMethod.hpp"
#include "RandomMethod.hpp"
#include "InputMethodRegistration.hpp"

namespace {

    void register_random_method(InputMethodRegistry& registry) {
        registry.register_method(
            "Random",
            [](const std::string& input) {
                return std::make_unique<RandomMethod>(input);
            }
        );
    }

    void register_stdin_method(InputMethodRegistry& registry) {
        registry.register_method(
            "STDIN",
            [](const std::string& input) {
                return std::make_unique<STDINMethod>(input);
            }
        );
    }

    void register_file_method(InputMethodRegistry& registry) {
        registry.register_method(
            "File",
            [](const std::string& input) {
                return std::make_unique<FileMethod>(input);
            }
        );
    }

}

void register_builtin_input_methods(InputMethodRegistry& registry) {
    register_random_method(registry);
    register_stdin_method(registry);
    register_file_method(registry);
}

void ensure_builtin_input_methods_registered() {
    static std::once_flag registration_flag;

    std::call_once(registration_flag, []() {
        register_builtin_input_methods(InputMethodRegistry::instance());
    });
}
