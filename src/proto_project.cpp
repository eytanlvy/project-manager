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

bool ProtoProject::add(const string nom, const int duree) {
    srand(time(NULL));
    int i = rand() % tasks.size();
    int j = rand() % tasks.size();
    while (i == j){
        i = rand() % tasks.size();
        j = rand() % tasks.size();
    }
    if (j < i) std::swap(i, j);

    Task* t = new Task(nom, duree);
    Task* t1 = tasks[i];
    Task* t2 = tasks[j];

    t1->addDependency(*t);
    t->addDependency(*t2);
    tasks.insert(tasks.begin()+j, t);
	topological_sort();
    return (true);
}

bool ProtoProject::add(const string nom, const int duree, const int task_id)
{
	int i = 0;
	while (i < tasks.size()){
		if (tasks[i]->getId() == task_id)
			break;
		i++;
	}
	if (i == tasks.size() || i == 0)
		return (false);
	
    Task* t = new Task(nom, duree);
    Task* t1 = tasks[0];
    Task* t2 = tasks[i];

    t1->addDependency(*t);
    t->addDependency(*t2);
    tasks.insert(tasks.begin() + i, t);
	topological_sort();
    return (true);
}

bool ProtoProject::add(const string nom, const int duree, const int task1, const int task2)
{
    int i = -1;
    int j = -1;

    for (int k = 0; k < tasks.size(); k++){
        if (tasks[k]->getId() == task1)
            i = k;
        if (tasks[k]->getId() == task2)
            j = k;
    }
    if (i == -1 || j == -1)
        return (false);
    if (j < i) std::swap(i, j);
    Task* t = new Task(nom, duree);
    Task* t1 = tasks[i];
    Task* t2 = tasks[j];

    t1->addDependency(*t);
    t->addDependency(*t2);
    tasks.insert(tasks.begin() + j, t);
	topological_sort();
    return (true);
}