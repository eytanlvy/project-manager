#include "../includes/debug.hpp"
#include <iostream>
#include <vector>
#include <run_project.hpp>
#include "debug.hpp"

#ifdef DEBUG_ENABLED
    bool Debug::debug_enabled = true;
#else
    bool Debug::debug_enabled = false;
#endif

std::ostream& Debug::output_stream = std::cerr;

// -----------------------------------

std::string Debug::task_list_to_string(RunProject const & project, std::vector<int> tasks_id) {
    std::string result = "[";
    for (auto task_id : tasks_id)
        result += project.contains(task_id)->get_name() + ", ";
    result += "]";
    return result;
};

std::string Debug::task_list_to_string(std::vector<Task *> tasks) {
    std::string result = "[";
    for (auto task : tasks)
        result += task->get_name() + ", ";
    result += "]";
    return result;
}

std::string Debug::bool_vector_to_string(std::vector<bool> const values)
{
    std::string result = "[";
    for (auto v : values)
        result += std::to_string(v) + ", ";
    result += "]";
    return result;
}

std::string Debug:: int_vector_to_string(std::vector<int> const values) {
    std::string result = "[";
    for (auto v : values)
        result += std::to_string(v) + ", ";
    result += "]";
    return result;
}