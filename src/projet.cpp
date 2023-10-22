# include "../includes/projet.hpp"

Projet::Projet()
{
	cout << "Naissance de : " << *this << endl;
}

Projet::Projet(const Projet& other)
{
	taches.clear();
	for (Tache* tache : other.taches) {
		taches.push_back(new Tache(*tache));
	}
}

// Projet& Projet::operator=(const Projet& other) //TODO
// {}

Projet::~Projet()
{
	for (Tache* tache : taches) {
		delete tache;
	}
	cout << "Cellule détruite: " << *this << endl;
}

vector<Tache*> const Projet::getTaches() const
{
	return (taches);
}

ostream& operator<<( ostream &out , const Projet &x )
{
	vector <Tache*> gtaches {x.getTaches()};
	out << "Projet : " << gtaches[gtaches.size() - 1] << endl;
	return out;
}
