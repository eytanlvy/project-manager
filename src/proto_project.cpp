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

bool ProtoProject::add(const string name, const int duration) {
    srand(time(NULL));
    int i = rand() % tasks.size();
    int j = rand() % tasks.size();
    while (i == j){
        i = rand() % tasks.size();
        j = rand() % tasks.size();
    }
    if (j < i) std::swap(i, j);

    Task* t = new Task(name, duration);
    Task* t1 = tasks[i];
    Task* t2 = tasks[j];

    t1->addDependency(*t);
    t->addDependency(*t2);
    tasks.insert(tasks.begin()+j, t);
	topological_sort();
    return (true);
}

bool ProtoProject::add(const string name, const int duration, const int task_id)
{
    Task *task_before = get_task(task_id);
    if (task_before == tasks.front())
        return false;
        
    Task* the_new_task = new Task(name, duration);
    the_new_task->addDependency(*tasks.back());
    tasks.front()->addDependency(*the_new_task);

	topological_sort();
    return true;
}

bool ProtoProject::add(const string name, const int duration, const int task1, const int task2) {
    if (task1 == task2)
        return false;

    int i{-1}, j{-1};

    for (int k = 0; k < tasks.size(); k++){
        if (tasks[k]->getId() == task1)
            i = k;
        if (tasks[k]->getId() == task2)
            j = k;
    }

    if (i == -1 || j == -1)
        return (false);
    
    if (j < i) std::swap(i, j); // i doit être inferieur à j
    
    Task* new_task = new Task(name, duration);
    Task* task_after = tasks[i];
    Task* task_before = tasks[j];

    new_task->addDependency(*task_before);
    task_after->addDependency(*new_task);
    tasks.push_back(new_task);

	topological_sort();
    return (true);
}