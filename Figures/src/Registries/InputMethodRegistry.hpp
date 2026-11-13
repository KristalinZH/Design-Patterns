#ifndef INPUT_METHOD_REGISTRY
#define INPUT_METHOD_REGISTRY

#include <memory>
#include <string>
#include <functional>
#include <unordered_map>

#include "InputMethod.hpp"

class InputMethodRegistry {
public:
    using MethodCreator = std::function<std::unique_ptr<InputMethod>(const std::string&)>;

    static InputMethodRegistry& instance();

    void register_method(const std::string& name, MethodCreator creator);

    std::unique_ptr<InputMethod> create(const std::string& input) const;

    InputMethodRegistry(const InputMethodRegistry&) = delete;
    InputMethodRegistry& operator=(const InputMethodRegistry&) = delete;

    InputMethodRegistry(InputMethodRegistry&&) = delete;
    InputMethodRegistry& operator=(InputMethodRegistry&&) = delete;

private:
    InputMethodRegistry() = default;

    std::unordered_map<std::string, MethodCreator> creators;
};

#endif
