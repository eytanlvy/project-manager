#include "../includes/task.hpp"
#include "../includes/debug.hpp"

using namespace std;

int Task::lastId = 0;

Task::Task(const string& nom, int duration) : name(nom), id(++lastId), duration(duration), is_accomplished(false)
{
	//Debug::print << "Naissance de : " << *this << "\n";
}

Task::Task(const Task& other): name(other.name), id(other.id), duration(other.duration), is_accomplished(other.is_accomplished)
{
    //Debug::print << "Copie de : " << *this << endl;
    dependances.clear();

    for (Task* const &dep : other.dependances)
        dependances.push_back(new Task(*dep));
}

const Task& Task::operator=(const Task& other)
{
    if (this == &other)
        return *this;

    name = other.name;
    id = other.id;
    duration = other.duration;
    is_accomplished = other.is_accomplished;

    dependances.clear();
    for (Task* const &dep : other.dependances)
		dependances.push_back(new Task(*dep));
    return (*this);
}

Task::~Task()
{
    dependances.clear();
    for (Task* tache : dependances)
		delete tache;
	//Debug::print << "Cellule détruite: " << *this << endl;
}

// Getters

string const Task::getName() const
{
	return (name);
}

int const Task::getId() const
{
	return (id);
}
int const Task::getDuration() const
{
	return (duration);
}

bool const Task::getIsAccomplished() const
{
	return (is_accomplished);
}

vector<Task*> const Task::getDependances() const
{
	return (dependances);
}

//Methods

bool Task::is_accomplishable() {
	for (Task *dependency: this->getDependances())
			if (!dependency->getIsAccomplished())
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

bool Task::depends_from(Task & x)
{
	int i{0};
    if (id == x.getId())
		return (true);
	while (i < dependances.size())
	{
		if (dependances[i]->getId() == x.getId() || dependances[i]->depends_from(x))
			return (true);
		
		i++;
	}
	return (false);
}

bool Task::addDependency(Task & x)
{
	if (this->depends_from(x) || x.depends_from(*this) || id == x.getId())
		return (false);
	dependances.push_back(&x);
	return (true);
}

int Task::durationParallalised()
{
	int i{0}, maxi{duration};
	while (i < dependances.size())
	{
		if (!dependances[i]->getIsAccomplished())
			maxi = max(dependances[i]->durationParallalised(), maxi);
		i++;
	}
	return (max(duration, maxi));
}

const bool Task::isMarked() const
{
	return (marked);
}

void Task::mark(bool value)
{
	marked = value;
}

void Task::PP_postfixe(vector<Task*>& sortedTasks)
{
    marked = true;
    for (Task* dep : dependances)
    {
        if (!dep->marked)
            dep->PP_postfixe(sortedTasks);
    }
    sortedTasks.push_back(this);
}


ostream& operator<<( ostream &out , const Task &x )
{
	out << "Task #" << x.getId() << " : " << x.getName();
	return (out);
}