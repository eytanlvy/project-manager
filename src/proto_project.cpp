# include "../includes/proto_project.hpp"

using namespace std;

void ProtoProject::unsafe_hard_reset() {
    this->tasks.clear();

    Task* debut = new Task("Debut", 0);
	Task* fin = new Task("Fin", 0);
	fin->addDependency(*debut);
	tasks.push_back(debut);
	tasks.push_back(fin);
}

ProtoProject::ProtoProject()
{
    unsafe_hard_reset();
}

bool ProtoProject::ajoute(const string name, const int duration) {
    int i = rand() % tasks.size();
    int j = rand() % tasks.size();
    while (i == j) {
        j = rand() % tasks.size();
    }

	i = i < j ? i : j;
    Task* t = new Task(name, duration);
    Task* t1 = tasks[i];
    Task* t2 = tasks[j];

    t2->addDependency(*t);
    t->addDependency(*t1);
    tasks.insert(tasks.begin() + j, t);
	topological_sort();
    return (true);
}

bool ProtoProject::ajoute(const string name, const int duration, const int task_id)
{
	int i = 0;
	while (i < tasks.size()){
		if (tasks[i]->getId() == task_id)
			break;
		i++;
	}
	if (i == tasks.size() || i == tasks.size() - 1)
		return (false);
	
    int j = tasks.size() - 1;

    Task* t = new Task(name, duration);
    Task* t1 = tasks[i];
    Task* t2 = tasks[j];

    t2->addDependency(*t);
    t->addDependency(*t1);
    tasks.insert(tasks.begin() + j, t);
	topological_sort();
    return (true);
}

