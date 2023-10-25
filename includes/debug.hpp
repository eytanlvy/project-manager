#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>

class Debug {
public:
    static std::ostream& output_stream;
    static bool debug_enabled;

    template <typename T>
    static void log(const T& value);
    
    template <typename T>
    Debug& operator<<(const T& value);
    
    static Debug print;
};

template <typename T>
void Debug::log(const T& value) {
    if (Debug::debug_enabled)
        Debug::output_stream << "<Debug> " << value << "\n";
}

template <typename T>
Debug& Debug::operator<<(const T& value) {
    Debug::log(value);
    return *this;
}

#endif