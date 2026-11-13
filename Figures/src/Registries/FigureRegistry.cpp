#include <utility>
#include <stdexcept>

#include "FigureRegistry.hpp"

FigureRegistry& FigureRegistry::instance() {
    static FigureRegistry registry;
    return registry;
}

void FigureRegistry::register_figure(const std::string& name, StringCreator string_creator, RandomCreator random_creator) {
    if (name.empty()) {
        throw std::invalid_argument("Figure name cannot be empty");
    }

    if (!string_creator || !random_creator) {
        throw std::invalid_argument("Figure creators cannot be empty");
    }

    const auto [it, inserted] = creators.emplace(
        name,
        FigureCreators{
            std::move(string_creator),
            std::move(random_creator)
        }
    );

    if (!inserted) {
        throw std::invalid_argument("Figure type is already registered");
    }
}

std::unique_ptr<Figure> FigureRegistry::create_from_string(const std::string& name, const std::vector<double>& parameters) const {
    const auto it = creators.find(name);

    if (it == creators.end()) {
        throw std::invalid_argument("Unknown figure type: " + name);
    }

    return it->second.string_creator(parameters);
}

std::unique_ptr<Figure> FigureRegistry::create_random(const std::string& name, std::mt19937& engine) const {
    const auto it = creators.find(name);

    if (it == creators.end()) {
        throw std::invalid_argument("Unknown figure type: " + name);
    }

    return it->second.random_creator(engine);
}

std::vector<std::string> FigureRegistry::registered_types() const {
    std::vector<std::string> types;
    types.reserve(creators.size());

    for (const auto& [name, figure_creators] : creators) {
        types.push_back(name);
    }

    return types;
}