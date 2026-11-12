#ifndef STDIN_METHOD
#define STDIN_METHOD

#include "InputMethod.hpp"

class STDINMethod : public InputMethod {
    public:
        explicit STDINMethod(const std::string& input);
        std::string get_method_name() const override; 
        std::unique_ptr<FigureFactory> create_factory() const override;
};

#endif