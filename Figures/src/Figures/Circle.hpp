#ifndef CIRCLE
#define CIRCLE

#include "Figure.hpp"
#include "StringConvertible.hpp"

class Circle : public Figure, public String_Convertible {

    public:
        explicit Circle(const double _radius);
        double perimeter() const override;
        std::unique_ptr<Figure> clone() const override;

        std::string to_string() const override;
    private:
        const double radius;

};

#endif