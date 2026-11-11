#ifndef FIGURE_FACTORY
#define FIGURE_FACTORY

#include <memory>
#include <string>
#include "Figure.hpp"

class StringFigureFactory {
    public:
        std::unique_ptr<Figure> create_from_string(const std::string& representation) const;
};

#endif