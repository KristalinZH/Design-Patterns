#ifndef RECTANGLE
#define RECTANGLE

#include "Figure.hpp"

class Rectangle : public Figure{
    public:
        explicit Rectangle(const double _a, const double _b);
        double perimeter() const override;
    private:
        const double a;
        const double b;
};

#endif