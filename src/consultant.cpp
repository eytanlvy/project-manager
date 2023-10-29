#include "../includes/consultant.hpp"
#include "../includes/error_management.hpp"

#include <vector>

/**
 * Review the project and provide a list of remaining tasks and the total remaining time to complete them.
 *
 * @param project A RunProject instance representing the project to be reviewed.
 * @return A pair containing a vector of task IDs representing the remaining tasks and the total remaining time to complete them.
 */
std::pair<std::vector<int>, int> Consultant::review(const RunProject &project) {
    std::vector<Task *> tasks = project.consult_tasks();
    std::vector<int> remaning_tasks;

    int remaning_time = 0;
    for (int i = tasks.size() - 1; i >= 0; i--) {
        Task *task = tasks[i];

        if (!task->is_accomplished()) {
            remaning_tasks.push_back(task->get_id());
            remaning_time += task->get_duration();
        }
    }

    return {remaning_tasks, remaning_time};
}