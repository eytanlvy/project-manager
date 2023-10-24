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

#endif