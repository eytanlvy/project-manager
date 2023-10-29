#include "../includes/project.hpp"
#include <stdexcept>
#include "../includes/debug.hpp"
#include <algorithm>

using namespace std;

Project::Project()
{
	//Debug::log("Naissance de : " + (*this) + "\n");
}

Project::~Project()
{
	tasks.clear();
	for (Task* task : tasks)
		delete task;
	//Debug::print << "Cellule détruite: " << *this << endl;
}

ostream& operator<<( ostream &out , const Project &x ) {
	vector <Task*> gtaches {x.consult_tasks()};
	for (int i {0}; i < gtaches.size(); i++)
		out << *gtaches[i] << ", ";
	out << endl;
	return out;
}

Task *Project::get_task(const int task_id) {
	for (Task *task : this->tasks)
		if (task->getId() == task_id)
			return task;
	return nullptr;
}

vector<Task*> const Project::consult_tasks() const {
	return (tasks);
}

pair<int,int> Project::pick_two_random_tasks() const {
	srand(time(NULL));
	int i =rand() % tasks.size();
	int j =rand() % tasks.size();
	while (tasks[i]->depends_from(*tasks[j])) {
		i = rand() % tasks.size();
		j = rand() % tasks.size();
	}
	return make_pair(i,j);
}

Task* Project::contains (string name) const {
	for (Task* task : tasks)
		if (task->getName() == name)
			return task;
	return NULL;
}

Task* Project::contains (int id) const {
	for (Task* task : tasks)
		if (task->getId() == id)
			return task;
	return NULL;
}

void Project::topological_sort() {
	cleanMarks();

    vector<Task*> sortedTasks;

    for(Task* task : tasks)
		if (!task->isMarked())
        	task->pp_postfixe(sortedTasks);
	
	std::reverse(sortedTasks.begin(), sortedTasks.end());
	tasks = sortedTasks;
}

void Project::cleanMarks() {
    for (Task* task : this->tasks)
        task->mark(0);
}
