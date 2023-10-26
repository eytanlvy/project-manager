# include "../includes/proto_project.hpp"
# include "../includes/debug.hpp"

using namespace std;

void ProtoProject::unsafe_hard_reset() {
    this->tasks.clear();

    Task* begin = new Task("Debut", 0);
	Task* end = new Task("Fin", 0);
	end->addDependency(*begin);
	tasks.push_back(end);
	tasks.push_back(begin);
}

ProtoProject::ProtoProject() {
    unsafe_hard_reset();
}

ProtoProject::ProtoProject(const ProtoProject& other) {
    this->tasks.clear();
    for (Task* const &task : other.tasks)
        tasks.push_back(new Task(*task));
}

void ProtoProject::insert_between_two_tasks(Task *new_task, Task *task_after, Task *task_before) {
    new_task->addDependency(*task_before);
    task_after->addDependency(*new_task);
    this->tasks.push_back(new_task);
	topological_sort();
}

bool ProtoProject::add(const string name, const int duration, const int task_id)
{
    Task *task_before = get_task(task_id);

    if (task_before == tasks.front())
        return false;
        
    this->insert_between_two_tasks(new Task(name, duration), tasks.front(), task_before);

    return true;
}

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

bool ProtoProject::add(const string name, const int duration, const int task1, const int task2) {
    if (task1 == task2) return false;

    int i{-1}, j{-1};

    for (int k = 0; k < tasks.size(); k++){
        if (tasks[k]->getId() == task1)
            i = k;
        if (tasks[k]->getId() == task2)
            j = k;
    }

    if (i == -1 || j == -1) return (false);
    
    if (j < i) std::swap(i, j); // i doit être inferieur à j

    this->insert_between_two_tasks(new Task(name, duration), tasks[i], tasks[j]);
    
    return (true);
}