#ifndef RANDOM_FIGURE_FACTORY
#define RANDOM_FIGURE_FACTORY

#include <random>
#include <cstdint>
#include "FigureFactory.hpp"

class RandomFigureFactory : public FigureFactory {
    public:
        explicit RandomFigureFactory(std::uint32_t seed = std::random_device{}());
        std::unique_ptr<Figure> create() override;
    private:
        std::mt19937 engine;
};

#endif