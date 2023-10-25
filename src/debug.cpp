#include "../includes/debug.hpp"
#include <iostream>

#ifdef DEBUG_ENABLED
    bool Debug::debug_enabled = true;
#else
    bool Debug::debug_enabled = false;
#endif

std::ostream& Debug::output_stream = std::cerr;