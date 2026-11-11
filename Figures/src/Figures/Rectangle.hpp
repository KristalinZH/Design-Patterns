#ifndef RECTANGLE
#define RECTANGLE

#include "Figure.hpp"
#include "StringConvertible.hpp"

class Rectangle : public Figure, public String_Convertible {
    public:
        explicit Rectangle(const double _a, const double _b);
        double perimeter() const override;
        std::unique_ptr<Figure> clone() const override;

        std::string to_string() const override;
    private:
        const double a;
        const double b;
};

#endif