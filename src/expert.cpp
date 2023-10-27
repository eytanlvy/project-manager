#include "../includes/expert.hpp"
#include "../includes/error_management.hpp"

/*
    Les taches peuvent être paraléllisées.
    renvois <liste de tache restantes, dans l'ordre, temps d'execution des taches>
    TODO : CHECK IF IT WORKS
*/
std::pair<std::vector<int>, int> Expert::review(const RunProject & project) {
    std::vector<Task *> tasks = project.consult_tasks();
    std::vector<int> remaning_tasks;
    
    int remaning_time = tasks.front()->durationParallelized();

    for (int i = tasks.size() - 1; i >= 0; i--) {
        Task *task = tasks[i];
        if (!task->isAccomplished())
            remaning_tasks.push_back(task->getId());
    }

    return {remaning_tasks, remaning_time};
}