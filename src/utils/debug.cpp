#include "../../includes/utils/debug.hpp"

template <typename T>
static void log(const T& value) {
    if (Debug::debug_enabled)
        Debug::output_stream << "Debug" << value;
}

template <typename T>
Debug& Debug::operator<<(const T& value) {
    Debug::log(value);
    return *this;
}

#ifdef DEBUG_ENABLED
    bool Debug::debug_enabled = true;
#else
    bool Debug::debug_enabled = false;
#endif

std::ostream& Debug::output_stream = std::cerr;