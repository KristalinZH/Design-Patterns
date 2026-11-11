#ifndef TRIANGLE
#define TRIANGLE

#include "Figure.hpp"
#include "StringConvertible.hpp"

class Triangle : public Figure, public String_Convertible {
    public:
        explicit Triangle(const double _a, const double _b, const double _c);
        double perimeter() const override;
        std::unique_ptr<Figure> clone() const override;

        std::string to_string() const override;
    private:
        const double a;
        const double b;
        const double c;
};

#endif