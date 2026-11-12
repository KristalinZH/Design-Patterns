#ifndef FILE_METHOD
#define FILE_METHOD

#include <fstream>
#include "InputMethod.hpp"

class FileMethod : public InputMethod {
    public:
        explicit FileMethod(const std::string& input);
        std::string get_method_name() const override; 
        std::unique_ptr<FigureFactory> create_factory() const override;
    private:
        std::unique_ptr<std::ifstream> stream;
};

#endif