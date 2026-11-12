#ifndef INPUT_METHOD
#define INPUT_METHOD

#include <string>
#include <memory>
#include "FigureFactory.hpp"

class InputMethod {
    public:
        virtual std::string get_method_name() const = 0; 
        virtual std::unique_ptr<FigureFactory> create_factory() const = 0;
        virtual ~InputMethod() = default;
};

#endif