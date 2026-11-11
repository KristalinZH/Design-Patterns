#ifndef CIRCLE
#define CIRCLE

#include "Figure.hpp"

class Circle : public Figure{

    public:
        explicit Circle(const double _radius);
        double perimeter() const override;
        std::unique_ptr<Figure> clone() const override;
    private:
        const double radius;

};

#endif