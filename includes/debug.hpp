#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
#include <run_project.hpp>

class Debug {
    public:
        Debug(const Debug &) = delete;
        Debug& operator=(const Debug &) = delete;
        ~Debug() = default;
        template <typename T>
        Debug& operator<<(const T&);
        static Debug print;
        // -----------------------------------
        template <typename T>
        static void log(const T&);
        static std::ostream& output_stream;
        static bool debug_enabled;
        // -----------------------------------
        static std::string task_list_to_string(RunProject const & project, std::vector<int> const tasks_id);
        static std::string task_list_to_string(std::vector<Task *> tasks);
        static std::string bool_vector_to_string(std::vector<bool> const);
        static std::string int_vector_to_string(std::vector<int> const);
};

template <typename T>
void Debug::log(const T& value) {
    if (Debug::debug_enabled)
        Debug::output_stream << "🚧 " << value << "\n";
}

template <typename T>
Debug& Debug::operator<<(const T& value) {
    Debug::log(value);
    return *this;
}

#endif