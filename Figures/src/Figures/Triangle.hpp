#ifndef TRIANGLE
#define TRIANGLE

#include "Figure.hpp"

class Triangle : public Figure{
    public:
        explicit Triangle(const double _a, const double _b, const double _c);
        double perimeter() const override;
        std::unique_ptr<Figure> clone() const override;
    private:
        const double a;
        const double b;
        const double c;
};

#endif