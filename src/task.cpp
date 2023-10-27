#include "../includes/task.hpp"
#include "../includes/debug.hpp"

int Task::lastId = 0;

Task::Task(const std::string& name, int duration) : name(name), id(++lastId), duration(duration), is_accomplished(false)
{
	//Debug::print << "Naissance de : " << *this << "\n";
}

Task::Task(const Task& other): name(other.name), id(other.id), duration(other.duration), is_accomplished(other.is_accomplished)
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

int const Task::getDuration() const {
	return (duration);
}

bool const Task::isAccomplished() const {
	return (is_accomplished);
}

std::vector<Task*> const Task::getDependances() const {
	return (dependencies);
}

//Methods

bool Task::is_accomplishable() {
	for (Task *dependency: this->getDependances())
			if (!dependency->isAccomplished())
				return false;
	return true;
}

bool Task::accomplish() { // safe process
	return (this->is_accomplished = this->is_accomplishable());
}

void Task::accomplish_cascade() {
	if (this->is_accomplished)
		return;

	for (Task *dependency: this->getDependances())
        dependency->accomplish_cascade();

	this->is_accomplished = true;
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

bool Task::addDependency(Task & x) {
	if (this->depends_from(x) || x.depends_from(*this) || id == x.getId())
		return (false);
	dependencies.push_back(&x);
	return (true);
}

int Task::durationParallelized() {
	int max{0};

	for (Task *task_to_execute_before : this->dependencies)
		if (!task_to_execute_before->isAccomplished())
			max = std::max(max, task_to_execute_before->durationParallelized());
	
	return max + this->duration;
}

const bool Task::isMarked() const {
	return (marked);
}

void Task::mark(bool value) {
	marked = value;
}

void Task::PP_postfixe(std::vector<Task*>& sortedTasks) {
    marked = true;
    for (Task* dep : dependencies)
    {
        if (!dep->marked)
            dep->PP_postfixe(sortedTasks);
    }
    sortedTasks.push_back(this);
}


std::ostream& operator<<(std::ostream &out , const Task &x ) {
	out << "Task #" << x.getId() << " : " << x.getName();
	return (out);
}