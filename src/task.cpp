#include "../includes/task.hpp"
#include "../includes/debug.hpp"

#include <algorithm>

int Task::last_id = 0;

/**
 * Constructor for the Task class.
 *
 * @param name Name of the task.
 * @param duration Duration of the task.
 */
Task::Task(const std::string& name, int duration) : name(name), id(++last_id), duration(duration), accomplished(false)
{
	Debug::log("Naissance de : " + this->get_name() + "\n");
}

/**
 * Copy constructor for the Task class.
 *
 * @param other Task to copy.
 */
Task::Task(const Task& other): name(other.name), id(other.id), duration(other.duration), accomplished(other.accomplished)
{
	Debug::log("Copie de : " + this->get_name() + "\n");
    dependencies.clear();

    for (Task* const &dep : other.dependencies)
        dependencies.push_back(new Task(*dep));
}

/**
 * Destructor for the Task class.
 */
Task::~Task() {
    dependencies.clear();
    for (Task* tache : dependencies)
		delete tache;
	Debug::log("Tâche " + this->get_name() + "detruite\n");
}

/**
 * Getters
 *
 * @return Task attributes.
 */

std::string const Task::get_name() const {
	return (name);
}

int const Task::get_id() const {
	return (id);
}

int const Task::get_duration() const {
	return (duration);
}

bool const Task::is_accomplished() const {
	return (accomplished);
}

std::vector<Task*> const Task::get_dependencies() const {
	return (dependencies);
}

/**
 * Check if the task is accomplishable by verifying its dependencies.
 *
 * @return True if the task is accomplishable, otherwise false.
 */
bool Task::is_accomplishable() {
	for (Task *dependency: this->get_dependencies())
			if (!dependency->is_accomplished())
				return false;
	return true;
}

/**
 * Accomplish the task if it is accomplishable.
 *
 * @return True if the task has been accomplished, otherwise false.
 */
bool Task::accomplish() {
	return (this->accomplished = this->is_accomplishable());
}

/**
 * Accomplish the task and its dependencies in cascade.
 */
void Task::accomplish_cascade() {
	if (this->accomplished)
		return;

	for (Task *dependency: this->get_dependencies())
        dependency->accomplish_cascade();

	this->accomplished = true;
}

/**
 * Check if the task depends on the given task.
 *
 * @param x Task to check.
 * @return True if the task depends on the given task, otherwise false.
 */
bool Task::depends_from(Task & x) {
	int i{0};
    if (id == x.get_id())
		return (true);
	while (i < dependencies.size())
	{
		if (dependencies[i]->get_id() == x.get_id() || dependencies[i]->depends_from(x))
			return (true);
		
		i++;
	}
	return (false);
}

/**
 * Add a dependency to the task.
 *
 * @param x Task to add as a dependency.
 * @return True if the dependency was added, otherwise false.
 */
bool Task::add_dependency(Task & x) {
	if (this->depends_from(x) || x.depends_from(*this) || id == x.get_id())
		return (false);
	dependencies.push_back(&x);
	return (true);
}

/**
 * Calculate the parallelized duration of the task, taking dependencies into account.
 *
 * @return Parallelized duration of the task.
 */
int Task::duration_parallelized() {
	int max{0};

	for (Task *task_to_execute_before : this->dependencies)
		if (!task_to_execute_before->is_accomplished())
			max = std::max(max, task_to_execute_before->duration_parallelized());
	
	return max + this->duration;
}

/**
 * Check if the task is marked, during topological sort.
 *
 * @return True if the task is marked, otherwise false.
 */
const bool Task::is_marked() const {
	return (marked);
}

/**
 * Mark or unmark the task.
 *
 * @param value True to mark the task, false to unmark.
 */
void Task::mark(bool value) {
	marked = value;
}

/**
 * Perform a postfix traversal of tasks and add them to sortedTasks.
 *
 * @param sortedTasks Vector to store the sorted tasks.
 */
void Task::pp_postfixe(std::vector<Task*>& sortedTasks) {
    marked = true;
    for (Task* dep : dependencies)
    {
        if (!dep->marked)
            dep->pp_postfixe(sortedTasks);
    }
    sortedTasks.push_back(this);
}

/**
 * Overloaded stream operator to display a task.
 *
 * @param out Output stream.
 * @param x Task to display.
 * @return Updated output stream.
 */
std::ostream& operator<<(std::ostream &out , const Task &x ) {
	out << "#" << x.get_id() << " : \"" << x.get_name() << "\"";
	return (out);
}

/**
 * Display task dependencies while avoiding repetitions.
 */
void Task::print_dependencies() const {
    std::vector<int> printed;
    print_dependencies(printed);
}

void Task::print_dependencies(std::vector<int>& printed) const {
    if (std::find(printed.begin(), printed.end(), id) == printed.end()) {
        printed.push_back(id);
        std::cout << *this;

        if (!dependencies.empty()) {
            std::cout << " --> ";
            bool first = true;
            for (const Task* dependency : dependencies) {
                if (first) {
                    first = false;
                } else {
                    std::cout << ", ";
                }
                std::cout << dependency->get_id();
            }
        }

        std::cout << std::endl;

        for (const Task* dependency : dependencies) {
            dependency->print_dependencies(printed);
        }
    }
}