# include "../includes/proto_project.hpp"
# include "../includes/debug.hpp"

using namespace std;

/**
 * Safely reset the ProtoProject instance by clearing all tasks and adding default "Debut" and "Fin" tasks.
 */
void ProtoProject::unsafe_hard_reset() {
    this->tasks.clear();

    Task* end = new Task("Fin", 0);
    Task* begin = new Task("Debut", 0);
	end->add_dependency(*begin);
	tasks.push_back(end);
	tasks.push_back(begin);
}

/**
 * Initialize the ProtoProject instance with two default tasks: "Debut" and "Fin".
 */

ProtoProject::ProtoProject() {
    unsafe_hard_reset();
}

void ProtoProject::insert_between_two_tasks(Task *new_task, Task *task_after, Task *task_before) {
    new_task->add_dependency(*task_before);
    task_after->add_dependency(*new_task);
    this->tasks.push_back(new_task);
	topological_sort();
}

/**
 * Add a new task with the given name and duration before an existing task with the specified ID.
 *
 * @param name The name of the new task.
 * @param duration The duration of the new task.
 * @param task_id The ID of the existing task before which the new task should be inserted.
 * @return True if the new task was added successfully, false otherwise.
 */
bool ProtoProject::add(const string name, const int duration, const int task_id)
{
    Task *task_before = get_task(task_id);

    if (task_before == tasks.front() || task_before == nullptr)
        return false;
        
    this->insert_between_two_tasks(new Task(name, duration), tasks.front(), task_before);

    return true;
}

/**
 * Add a new task with the given name and duration between two randomly selected tasks.
 *
 * @param name The name of the new task.
 * @param duration The duration of the new task.
 * @return True if the new task was added successfully, false otherwise.
 */
bool ProtoProject::add(const string name, const int duration) {
    srand(time(NULL));
    
    int i = rand() % tasks.size();
    int j = rand() % tasks.size();
    
    if (i == j)
        j = (j + 1) % tasks.size();
    
    if (j < i) std::swap(i, j);

    this->insert_between_two_tasks(new Task(name, duration), tasks[i], tasks[j]);
    return (true);
}

/**
 * Add a new task with the given name and duration between two tasks with specified IDs.
 *
 * @param name The name of the new task.
 * @param duration The duration of the new task.
 * @param task1 The ID of the first task.
 * @param task2 The ID of the second task.
 * @return True if the new task was added successfully, false otherwise.
 */
bool ProtoProject::add(const string name, const int duration, const int task1, const int task2) {
    if (task1 == task2) return false;

    int i{-1}, j{-1};

    for (int k = 0; k < tasks.size(); k++){
        if (tasks[k]->get_id() == task1)
            i = k;
        if (tasks[k]->get_id() == task2)
            j = k;
    }

    if (i == -1 || j == -1) return (false);
    
    if (j < i) std::swap(i, j);

    this->insert_between_two_tasks(new Task(name, duration), tasks[i], tasks[j]);
    
    return (true);
}