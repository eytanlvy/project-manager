#ifndef ERROR_MANAGEMENT_HPP
#define ERROR_MANAGEMENT_HPP

#include <stdexcept>

class NotImplemented : public std::logic_error
{
    public:
        NotImplemented() : std::logic_error("Function not yet implemented") { };
};

#endif