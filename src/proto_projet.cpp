# include "../includes/proto_projet.hpp"

using namespace std;

void ProtoProjet::unsafe_hard_reset() {
    this->taches.clear();

    Tache* debut = new Tache("Debut", 0);
	Tache* fin = new Tache("Fin", 0);
	fin->ajouteDependance(*debut);
	taches.push_back(debut);
	taches.push_back(fin);
}

ProtoProjet::ProtoProjet()
{
    unsafe_hard_reset();
	
}

bool ProtoProjet::ajoute(const string nom, const int duree) {
    int i = rand() % taches.size();
    int j = rand() % taches.size();
    while (i == j) {
        j = rand() % taches.size();
    }

	i = i < j ? i : j;
    Tache* t = new Tache(nom, duree);
    Tache* t1 = taches[i];
    Tache* t2 = taches[j];

    t2->ajouteDependance(*t);
    t->ajouteDependance(*t1);
    taches.insert(taches.begin() + j, t);
	topological_sort();
    return (true);
}

bool ProtoProjet::ajoute(const string nom, const int duree, const int tache_id)
{
	int i = 0;
	while (i < taches.size()){
		if (taches[i]->getId() == tache_id)
			break;
		i++;
	}
	if (i == taches.size() || i == taches.size() - 1)
		return (false);
	
    int j = taches.size() - 1;

    Tache* t = new Tache(nom, duree);
    Tache* t1 = taches[i];
    Tache* t2 = taches[j];

    t2->ajouteDependance(*t);
    t->ajouteDependance(*t1);
    taches.insert(taches.begin() + j, t);
	topological_sort();
    return (true);
}

