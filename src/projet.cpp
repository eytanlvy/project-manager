#include "../includes/projet.hpp"
#include <stdexcept>

using namespace std;

Projet::Projet()
{
	//Debug::print << "Naissance de : " << *this << endl;
}

Projet::Projet(const Projet& other)
{
	taches.clear();
	for (Tache* const &tache : other.taches) {
		taches.push_back(new Tache(*tache));
	}
}

Projet& Projet::operator=(const Projet& other)
{
	if (this == &other) {
		return *this;
	}
	taches.clear();
	for (Tache* const &tache : other.taches) {
		taches.push_back(new Tache(*tache));
	}
	return *this;
}

Projet::~Projet()
{
	taches.clear();
	for (Tache* tache : taches) {
		delete tache;
	}
	//Debug::print << "Cellule détruite: " << *this << endl;
}

ostream& operator<<( ostream &out , const Projet &x )
{
	vector <Tache*> gtaches {x.consult_tasks()};
	for (int i {0}; i < gtaches.size() - 1; i++) {
		out << *gtaches[i] << ", ";
	}
	out << endl;
	return out;
}

Tache *Projet::get_task(const int task_id) {
	for (Tache *task : this->taches)
		if (task->getId() == task_id)
			return task;
	
	throw std::invalid_argument("This task id doesn't exist.");
	return nullptr;
}

vector<Tache*> const Projet::consult_tasks() const
{
	return (taches);
}

pair<int,int> Projet::pick_two_random_tasks()
{
	srand(time(NULL));
	int i =rand() % taches.size();
	int j =rand() % taches.size();
	while (taches[i]->depends_from(*taches[j])) {
		i = rand() % taches.size();
		j = rand() % taches.size();
	}
	return make_pair(i,j);
}

Tache* Projet::contains (string name)
{
	for (Tache* tache : taches) {
		if (tache->getNom() == name) {
			return tache;
		}
	}
	return NULL;
}

Tache* Projet::contains (int id)
{
	for (Tache* tache : taches)
	{
		if (tache->getId() == id)
			return tache;
	}
	return NULL;
}

void Projet::topological_sort()
{
	cleanMarks();

    vector<Tache*> sortedTasks;

    // Parcourir toutes les tâches du projet
    for (Tache* task : taches)
    {
        // Si la tâche n'est pas marquée, commencez un parcours en profondeur postfixe
        if (!task->is_marked())
        {
            task->PP_postfixe(sortedTasks);
        }
    }

}

void Projet::cleanMarks()
{
    for (Tache* task : taches)
        task->mark(0);
}
