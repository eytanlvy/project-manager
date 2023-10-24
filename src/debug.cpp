#include "../includes/debug.hpp"
#include <iostream>

#ifdef DEBUG_ENABLED
    bool Debug::debug_enabled = true;
#else
    bool Debug::debug_enabled = false;
#endif

std::ostream& Debug::output_stream = std::cerr;

template <typename T>
void Debug::log(const T& value) {
    if (Debug::debug_enabled)
        Debug::output_stream << "<Debug> " << value;
}

template <typename T>
Debug& Debug::operator<<(const T& value) {
    Debug::log(value);
    return *this;
}