#include "../includes/consultant.hpp"
#include "../includes/error_management.hpp"

#include <vector>

/*
    Une seul personne doit réaliser les tasks => pas de parralèllisation
    renvois <liste de tache restantes, dans l'ordre, somme du temps des tasks>
*/
std::pair<std::vector<int>, int> Consultant::review(const RunProject &project) {
    std::vector<Task *> tasks = project.consult_tasks();
    std::vector<int> remaning_tasks;

    int remaning_time = 0;
    for (int i = tasks.size() - 1; i >= 0; i--) {
        Task *task = tasks[i];

        if (!task->isAccomplished()) {
            remaning_tasks.push_back(task->getId());
            remaning_time += task->getDuration();
        }
    }

    return {remaning_tasks, remaning_time};
}