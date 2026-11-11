#ifndef FIGURE
#define FIGURE

class Figure{
    public:
        virtual double perimeter() const = 0;
        virtual ~Figure() = default;
};

#endif