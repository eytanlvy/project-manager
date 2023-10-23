# include "../includes/tache.hpp"

int Tache::lastId = 0;

Tache::Tache(const string& nom, int duree) : nom(nom), id(++lastId), duree(duree), realisee(false)
{
	cout << "Naissance de : " << *this << endl;
}

Tache::Tache(const Tache& other): nom(other.nom), id(other.id), duree(other.duree), realisee(other.realisee)
{
    cout << "Copie de : " << *this << endl;
    dependances.clear();
    for (Tache* dep : other.dependances)
        dependances.push_back(new Tache(*dep));
}

Tache& Tache::operator=(const Tache& other)
{
    if (this == &other)
        return *this;

    nom = other.nom;
    id = other.id;
    duree = other.duree;
    realisee = other.realisee;

    dependances.clear();
    for (Tache* dep : other.dependances)
        this->ajouteDependance(*dep);

    return (*this);
}

Tache::~Tache()
{
    dependances.clear();
    for (Tache* tache : dependances)
		delete tache;
	cout << "Cellule détruite: " << *this << endl;
}

// Getters

string const Tache::getNom() const
{
	return (nom);
}

int const Tache::getId() const
{
	return (id);
}
int const Tache::getDuree() const
{
	return (duree);
}

bool const Tache::getRealisee() const
{
	return (realisee);
}

vector<Tache*> const Tache::getDependances() const
{
	return (dependances);
}

//Methods

bool Tache::realise()
{
	int i{0};
	while (i < dependances.size())
	{
		if (!dependances[i]->getRealisee())
			return (false);
		i++;
	}
	realisee = true;
	return (true);
}

bool Tache::depends_from(Tache & x)
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

bool Tache::ajouteDependance(Tache & x)
{
	if (this->depends_from(x) || x.depends_from(*this) || id == x.getId())
		return (false);
	dependances.push_back(&x);
	return (true);
}

int Tache::dureeParal()
{
	int i{0}, maxi{duree};
	while (i < dependances.size())
	{
		maxi = max(dependances[i]->dureeParal(), maxi);
		i++;
	}
	return (max(duree, maxi));
}


ostream& operator<<( ostream &out , const Tache &x )
{
	out << "Tache #" << x.getId() << " : " << x.getNom();
	return (out);
}