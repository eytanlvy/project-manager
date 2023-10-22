# include "../includes/tache.hpp"

int Tache::lastId = 0;

Tache::Tache(const string& nom, int duree) : nom(nom), id(++lastId), duree(duree), realisee(false)
{
	cout << "Naissance de : " << *this << endl;
}

Tache::Tache(const Tache& other) {
    nom = other.nom;
    id = other.id;
    duree = other.duree;
    realisee = other.realisee;

    dependances.clear();
    for (Tache* dep : other.dependances) {
        dependances.push_back(new Tache(*dep));
    }
}

Tache& Tache::operator=(const Tache& other) {
    if (this == &other) {
        return *this;
    }
    nom = other.nom;
    id = other.id;
    duree = other.duree;
    realisee = other.realisee;

    for (Tache* dep : dependances) {
        delete dep;
    }
    dependances.clear();
    for (Tache* dep : other.dependances) {
        dependances.push_back(new Tache(*dep));
    }

    return *this;
}

Tache::~Tache()
{
	dependances.clear();
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
	if (x.depends_from(*this) || id == x.getId())
		return (false);
	dependances.push_back(&x);
	return (true);
}

int Tache::dureeParal()
{
	if (realisee)
		return (0);
	int i{0}, max{duree};
	while (i < dependances.size())
	{
		if (!dependances[i]->getRealisee())
		{
			int tmp = dependances[i]->dureeParal();
			if (tmp > max)
				max = tmp;
		}
		i++;
	}
	return (max);
}


ostream& operator<<( ostream &out , const Tache &x )
{
	out << "Tache #" << x.getId() << " : " << x.getNom();
	return (out);
}


int main() {
    // Test 1: Tâches et dépendances
    Tache tache1("Tache1", 3);
    Tache tache2("Tache2", 2);
    Tache tache3("Tache3", 4);

    tache1.ajouteDependance(tache2);
    tache1.ajouteDependance(tache3);
    tache2.ajouteDependance(tache3);

    std::cout << "Test 1 - Tâches et dépendances : " << std::endl;
    std::cout << "Tâches : " << std::endl;
    std::cout << tache1 << ", Dépendances : " << (tache1.depends_from(tache2) ? "Oui" : "Non") << std::endl;
    std::cout << tache2 << ", Dépendances : " << (tache2.depends_from(tache3) ? "Oui" : "Non") << std::endl;
    std::cout << tache3 << ", Dépendances : " << (tache3.depends_from(tache1) ? "Oui" : "Non") << std::endl;

    // Test 2: Durée totale de réalisation
    Tache tache4("Tache4", 2);
    Tache tache5("Tache5", 1);

    tache4.ajouteDependance(tache1);
    tache4.ajouteDependance(tache2);
    tache5.ajouteDependance(tache4);

    std::cout << "Test 2 - Durée totale de réalisation : " << std::endl;
    int dureeTotale = tache5.dureeParal();
    std::cout << "Durée totale de réalisation de tache5 : " << dureeTotale << std::endl;

    return 0;
}