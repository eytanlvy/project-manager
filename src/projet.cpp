# include "../includes/projet.hpp"

Projet::Projet()
{
	cout << "Naissance de : " << *this << endl;
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
	cout << "Cellule détruite: " << *this << endl;
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
    for (Tache* task : taches)
    {
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
ostream& operator<<( ostream &out , const Projet &x )
{
	vector <Tache*> gtaches {x.consult_tasks()};
	for (int i {0}; i < gtaches.size() - 1; i++) {
		out << *gtaches[i] << ", ";
	}
	out << endl;
	return out;
}

int main() {
    // Test 1: Tâches et dépendances
    Tache tache1("Tache1", 3);
    Tache tache2("Tache2", 2);
    Tache tache3("Tache3", 4);

    tache1.ajouteDependance(tache2);
    tache1.ajouteDependance(tache3);
    tache2.ajouteDependance(tache3);

	assert(tache1.depends_from(tache2));
	assert(!tache2.depends_from(tache1));
	assert(tache2.depends_from(tache3));
	assert(!tache3.depends_from(tache1));

    Tache tache4("Tache4", 2);
    Tache tache5("Tache5", 1);

    tache4.ajouteDependance(tache1);
    tache4.ajouteDependance(tache2);
    tache5.ajouteDependance(tache4);

    tache3 = tache5;
	assert( tache3.depends_from(tache1) && tache3.depends_from(tache2) &&tache3.depends_from(tache4));
	assert(tache5.depends_from(tache1) && tache5.depends_from(tache2) && tache5.depends_from(tache4));
	assert(tache5.dureeParal() == tache3.dureeParal());

    return 0;
}
