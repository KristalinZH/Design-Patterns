#ifndef FIGURE_FACTORY
#define FIGURE_FACTORY

#include <memory>
#include "Figure.hpp"

class FigureFactory {
    public:
        virtual std::unique_ptr<Figure> create() = 0;
        virtual ~FigureFactory() = default;
};


#endif