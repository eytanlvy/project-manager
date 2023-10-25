#include "../includes/project.hpp"
#include <stdexcept>
#include "../includes/debug.hpp"

using namespace std;

Project::Project()
{
	//Debug::log("Naissance de : " + (*this) + "\n");
}

Project::Project(const Project& other) {
	this->tasks.clear();
	for (Task* const &task : other.tasks) {
		this->tasks.push_back(new Task(*task));
	}
}

Project& Project::operator=(const Project& other) {
	if (this == &other) {
		return *this;
	}
	tasks.clear();
	for (Task* const &task : other.tasks) {
		tasks.push_back(new Task(*task));
	}
	return *this;
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
	for (int i {0}; i < gtaches.size() - 1; i++)
		out << *gtaches[i] << ", ";
	out << endl;
	return out;
}

Task *Project::get_task(const int task_id) {
	for (Task *task : this->tasks)
		if (task->getId() == task_id)
			return task;
	
	throw std::invalid_argument("This task id doesn't exist.");
	return nullptr;
}

vector<Task*> const Project::consult_tasks() const {
	return (tasks);
}

pair<int,int> Project::pick_two_random_tasks() {
	srand(time(NULL));
	int i =rand() % tasks.size();
	int j =rand() % tasks.size();
	while (tasks[i]->depends_from(*tasks[j])) {
		i = rand() % tasks.size();
		j = rand() % tasks.size();
	}
	return make_pair(i,j);
}

Task* Project::contains (string name) {
	for (Task* task : tasks)
		if (task->getName() == name)
			return task;
	return NULL;
}

Task* Project::contains (int id) {
	for (Task* task : tasks)
		if (task->getId() == id)
			return task;
	return NULL;
}

void Project::topological_sort() {
	cleanMarks();

    vector<Task*> sortedTasks;

    // Parcourir toutes les tâches du projet
    for (Task* task : tasks)
        // Si la tâche n'est pas marquée, commencez un parcours en profondeur postfixe
        if (!task->isMarked())
            task->PP_postfixe(sortedTasks);
}

void Project::cleanMarks() {
    for (Task* task : tasks)
        task->mark(0);
}
