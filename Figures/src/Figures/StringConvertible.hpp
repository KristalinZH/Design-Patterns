#ifndef STRING_CONVERTIBLE
#define STRING_CONVERTIBLE

#include <string>

class String_Convertible{
    public:
        virtual std::string to_string() const = 0;
        virtual ~String_Convertible() = default;
};

#endif