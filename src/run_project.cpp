#include "../includes/run_project.hpp"
#include "../includes/debug.hpp"

#include <vector>


/**
 * Constructor for the RunProject class, initializes the tasks based on a ProtoProject.
 *
 * @param proto_project A ProtoProject instance from which to initialize the tasks.
 */
RunProject::RunProject(ProtoProject proto_projet) {
    Debug::log("Naissance de RunProjet\n");
    this->tasks = proto_projet.tasks;
    proto_projet.unsafe_hard_reset();
};

/**
 * Reset the task accomplishment status using a vector of boolean values.
 *
 * @param memory A vector of boolean values representing the task accomplishment status.
 */
void RunProject::reset_tasks(std::vector<bool> memory) {
    for (int i = 0; i < memory.size(); i++)
        this->tasks[i]->accomplished = memory[i];
}

/**
 * Run a single task in the project. Optionally, force the execution of its dependencies.
 *
 * @param task The task to run.
 * @param force_dependencies If true, forcefully execute all dependencies.
 * @return True if the task was executed successfully, false otherwise.
 */
bool RunProject::run(Task *task, bool force_dependencies) {
    if (!force_dependencies)
        return task->accomplish();
    
    task->accomplish_cascade();

    return true;
}

/**
 * Run a list of tasks in the project. Optionally, force the execution of their dependencies.
 *
 * @param tasks A vector of tasks to run.
 * @param force_dependencies If true, forcefully execute all dependencies.
 * @return True if all tasks were executed successfully, false otherwise.
 */
bool RunProject::run(std::vector<Task *> tasks, bool force_dependencies) {
    if (force_dependencies) {
        // case without error
        for (Task *task : tasks)
            task->accomplish_cascade();
        return true;
    }

    // case with error
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

/**
 * Run a single task in the project by specifying its ID. Optionally, force the execution of its dependencies.
 *
 * @param task_id The ID of the task to run.
 * @param force_dependencies If true, forcefully execute all dependencies.
 * @return True if the task was executed successfully, false otherwise.
 */
bool RunProject::run(const int task_id, bool force_dependencies) {
    Task *task = this->get_task(task_id);
    return this->run(task, force_dependencies);
}

/**
 * Run a list of tasks in the project by specifying their IDs. Optionally, force the execution of their dependencies.
 *
 * @param tasks_id A vector of task IDs to run.
 * @param force_dependencies If true, forcefully execute all dependencies.
 * @return True if all tasks were executed successfully, false otherwise.
 */
bool RunProject::run(std::vector<int> tasks_id, bool force_dependencies) {
    std::vector<Task *> tasks;
    for (int task_id : tasks_id)
        tasks.push_back(this->get_task(task_id));
    return this->run(tasks, force_dependencies);
}