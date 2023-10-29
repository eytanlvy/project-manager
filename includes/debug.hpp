#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>

class Debug {
    public:
        Debug(const Debug &) = delete;
        Debug& operator=(const Debug &) = delete;
        ~Debug() = default;
        template <typename T>
        Debug& operator<<(const T&);

        template <typename T>
        static void log(const T&);

        static std::ostream& output_stream;
        static bool debug_enabled;
        static Debug print;
};

template <typename T>
void Debug::log(const T& value) {
    if (Debug::debug_enabled)
        Debug::output_stream << "🚧 [   " << value << "   ]\n";
}

template <typename T>
Debug& Debug::operator<<(const T& value) {
    Debug::log(value);
    return *this;
}

#endif