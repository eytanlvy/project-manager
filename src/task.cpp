#include "../includes/task.hpp"
#include "../includes/debug.hpp"

#include <algorithm>

int Task::lastId = 0;

Task::Task(const std::string& name, int duration) : name(name), id(++lastId), duration(duration), accomplished(false)
{
	//Debug::print << "Naissance de : " << *this << "\n";
}

Task::Task(const Task& other): name(other.name), id(other.id), duration(other.duration), accomplished(other.accomplished)
{
    //Debug::print << "Copie de : " << *this << endl;
    dependencies.clear();

    for (Task* const &dep : other.dependencies)
        dependencies.push_back(new Task(*dep));
}

Task::~Task() {
    dependencies.clear();
    for (Task* tache : dependencies)
		delete tache;
	//Debug::print << "Cellule détruite: " << *this << endl;
}

// Getters

std::string const Task::getName() const {
	return (name);
}

int const Task::getId() const {
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

//Methods

bool Task::is_accomplishable() {
	for (Task *dependency: this->get_dependencies())
			if (!dependency->is_accomplished())
				return false;
	return true;
}

bool Task::accomplish() { // safe process
	return (this->accomplished = this->is_accomplishable());
}

void Task::accomplish_cascade() {
	if (this->accomplished)
		return;

	for (Task *dependency: this->get_dependencies())
        dependency->accomplish_cascade();

	this->accomplished = true;
}

bool Task::depends_from(Task & x) {
	int i{0};
    if (id == x.getId())
		return (true);
	while (i < dependencies.size())
	{
		if (dependencies[i]->getId() == x.getId() || dependencies[i]->depends_from(x))
			return (true);
		
		i++;
	}
	return (false);
}

bool Task::add_dependency(Task & x) {
	if (this->depends_from(x) || x.depends_from(*this) || id == x.getId())
		return (false);
	dependencies.push_back(&x);
	return (true);
}

int Task::duration_parallelized() {
	int max{0};

	for (Task *task_to_execute_before : this->dependencies)
		if (!task_to_execute_before->is_accomplished())
			max = std::max(max, task_to_execute_before->duration_parallelized());
	
	return max + this->duration;
}

const bool Task::isMarked() const {
	return (marked);
}

void Task::mark(bool value) {
	marked = value;
}

void Task::pp_postfixe(std::vector<Task*>& sortedTasks) {
    marked = true;
    for (Task* dep : dependencies)
    {
        if (!dep->marked)
            dep->pp_postfixe(sortedTasks);
    }
    sortedTasks.push_back(this);
}


std::ostream& operator<<(std::ostream &out , const Task &x ) {
	out << "#" << x.getId() << " : \"" << x.getName() << "\"";
	return (out);
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
                std::cout << dependency->getId();
            }
        }

        std::cout << std::endl;

        for (const Task* dependency : dependencies) {
            dependency->print_dependencies(printed);
        }
    }
}

void Task::print_dependencies() const {
    std::vector<int> printed;
    print_dependencies(printed);
}