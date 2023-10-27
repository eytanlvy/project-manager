#include "../includes/expert.hpp"
#include "../includes/error_management.hpp"

/*
    Les taches peuvent être paraléllisées.
    renvois <liste de tache restantes, dans l'ordre, temps d'execution des taches>
*/
std::pair<std::vector<int>, int> Expert::review(const RunProject & project) {
    std::vector<Task *> tasks = project.consult_tasks();
    std::vector<int> remaning_tasks;
    
    int remaning_time = 0;

    throw new NotImplemented();

    return {remaning_tasks, remaning_time};
}