#include "../includes/project.hpp"
#include <stdexcept>
#include "../includes/debug.hpp"
#include <algorithm>

using namespace std;

/**
 * Constructor for the Project class.
 */
Project::Project()
{
	Debug::log("Naissance de projet\n");
}

/**
 * Destructor for the Project class.
 */
Project::~Project()
{
	tasks.clear();
	for (Task* task : tasks)
		delete task;
	Debug::log("Projet detruit\n");
}

/**
 * Overloaded stream operator to display a project and its tasks.
 *
 * @param out Output stream.
 * @param x Project to display.
 * @return Updated output stream.
 */
ostream& operator<<( ostream &out , const Project &x ) {
	vector <Task*> gtaches {x.consult_tasks()};
	for (int i {0}; i < gtaches.size(); i++)
		out << *gtaches[i] << ", ";
	out << endl;
	return out;
}

/**
 * Get a task by its ID.
 *
 * @param task_id ID of the task to retrieve.
 * @return Pointer to the task, or nullptr if not found.
 */
Task *Project::get_task(const int task_id) {
	for (Task *task : this->tasks)
		if (task->get_id() == task_id)
			return task;
	return nullptr;
}

/**
 * Get a list of tasks associated with the project.
 *
 * @return Vector of task pointers.
 */
vector<Task*> const Project::consult_tasks() const {
	return (tasks);
}

/**
 * Pick two random tasks that are not dependent on each other.
 *
 * @return Pair of task IDs that can be executed in parallel.
 */
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

/**
 * Check if a task with the given name exists in the project.
 *
 * @param name Name of the task to search for.
 * @return Pointer to the task if found, otherwise nullptr.
 */
Task* Project::contains (string name) const {
	for (Task* task : tasks)
		if (task->get_name() == name)
			return task;
	return NULL;
}

/**
 * Check if a task with the given ID exists in the project.
 *
 * @param id ID of the task to search for.
 * @return Pointer to the task if found, otherwise nullptr.
 */
Task* Project::contains (int id) const {
	for (Task* task : tasks)
		if (task->get_id() == id)
			return task;
	return NULL;
}

/**
 * Perform a topological sort of tasks.
 */
void Project::topological_sort() {
	clean_marks();

    vector<Task*> sortedTasks;

    for(Task* task : tasks)
		if (!task->isMarked())
        	task->pp_postfixe(sortedTasks);
	
	std::reverse(sortedTasks.begin(), sortedTasks.end());
	tasks = sortedTasks;
}

/**
 * Clear the "marked" status of tasks.
 */
void Project::clean_marks() {
    for (Task* task : this->tasks)
        task->mark(0);
}
