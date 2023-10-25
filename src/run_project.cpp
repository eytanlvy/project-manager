#include "../includes/run_project.hpp"

#include "../includes/error_management.hpp"
#include <vector>

RunProject::RunProject(ProtoProject proto_projet) {
    this->tasks = proto_projet.tasks;
    proto_projet.unsafe_hard_reset();
};

bool RunProject::run(Task *tache, bool force_dependencies) {
    if (!force_dependencies)
        return tache->accomplish();
    
    tache->accomplish_cascade();

    return true;
}

bool RunProject::run(std::vector<Task *> tasks, bool force_dependencies) {
    if (!force_dependencies)
        throw NotImplemented();

    for (Task *task : tasks)
        this->run(task);

    return true;
}

bool RunProject::run(const int tache_id, bool force_dependencies) {
    Task *task = this->get_task(tache_id);
    return this->run(task, force_dependencies);
}

bool RunProject::run(std::vector<int> taches_id, bool force_dependencies) {
    if (!force_dependencies)
        throw NotImplemented();

    for (int task : taches_id)
        this->run(task);

    return true;
}