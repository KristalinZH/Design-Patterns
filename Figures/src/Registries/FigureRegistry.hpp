#ifndef FIGURE_REGISTRY
#define FIGURE_REGISTRY

#include <memory>
#include <random>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

#include "Figure.hpp"

class FigureRegistry {
public:
    using StringCreator = std::function<std::unique_ptr<Figure>(const std::vector<double>&)>;

    using RandomCreator = std::function<std::unique_ptr<Figure>(std::mt19937&)>;

    static FigureRegistry& instance();

    void register_figure(const std::string& name, StringCreator string_creator, RandomCreator random_creator);

    std::unique_ptr<Figure> create_from_string(const std::string& name, const std::vector<double>& parameters) const;

    std::unique_ptr<Figure> create_random(const std::string& name, std::mt19937& engine) const;

    std::vector<std::string> registered_types() const;

    FigureRegistry(const FigureRegistry&) = delete;
    FigureRegistry& operator=(const FigureRegistry&) = delete;

    FigureRegistry(FigureRegistry&&) = delete;
    FigureRegistry& operator=(FigureRegistry&&) = delete;

private:
    struct FigureCreators {
        StringCreator string_creator;
        RandomCreator random_creator;
    };

    std::unordered_map<std::string, FigureCreators> creators;

    FigureRegistry() = default;
};

#endif