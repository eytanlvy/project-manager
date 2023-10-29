#include "../includes/run_project.hpp"

#include "../includes/error_management.hpp"
#include <vector>

RunProject::RunProject(ProtoProject proto_projet) {
    this->tasks = proto_projet.tasks;
    proto_projet.unsafe_hard_reset();
};

void RunProject::reset_tasks(std::vector<bool> memory) {
    for (int i = 0; i < memory.size(); i++)
        this->tasks[i]->accomplished = memory[i];
}

bool RunProject::run(Task *task, bool force_dependencies) {
    if (!force_dependencies)
        return task->accomplish();
    
    task->accomplish_cascade();

    return true;
}

bool RunProject::run(std::vector<Task *> tasks, bool force_dependencies) {
    if (force_dependencies) {
        // cas sans erreur
        for (Task *task : tasks)
            task->accomplish_cascade();
        return true;
    }

    // cas avec erreur
    std::vector<bool> memory;
    for (Task *task : tasks)
        memory.push_back(task->is_accomplished());

    bool success = true;
    for (Task * task : tasks)
        success &= (task->accomplish());
    if (success) return true;

    this->reset_tasks(memory);
    return false;
}

bool RunProject::run(const int task_id, bool force_dependencies) {
    Task *task = this->get_task(task_id);
    return this->run(task, force_dependencies);
}

bool RunProject::run(std::vector<int> tasks_id, bool force_dependencies) {
    std::vector<Task *> tasks;
    for (int task_id : tasks_id)
        tasks.push_back(this->get_task(task_id));
    return this->run(tasks, force_dependencies);
}