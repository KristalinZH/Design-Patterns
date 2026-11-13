#include <random>
#include <stdexcept>
#include "FigureRegistry.hpp"
#include "FigureRegistration.hpp"
#include "RandomFigureFactory.hpp"

RandomFigureFactory::RandomFigureFactory(std::uint32_t seed) : engine(seed) {}

std::unique_ptr<Figure> RandomFigureFactory::create() {
    ensure_builtin_figures_registered();

    FigureRegistry& registry = FigureRegistry::instance();

    const std::vector<std::string> types = registry.registered_types();

    if (types.empty()) {
        throw std::runtime_error("No figure types registered");
    }

    std::uniform_int_distribution<std::size_t> distribution(0, types.size() - 1);

    const std::string& selected_type = types[distribution(engine)];

    return registry.create_random(selected_type, engine);
}
