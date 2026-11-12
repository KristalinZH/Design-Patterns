#ifndef RANDOM_METHOD
#define RANDOM_METHOD

#include "InputMethod.hpp"

class RandomMethod : public InputMethod {
    public:
        explicit RandomMethod(const std::string& input);
        std::string get_method_name() const override; 
        std::unique_ptr<FigureFactory> create_factory() const override;
};

#endif