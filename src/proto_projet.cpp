# include "../includes/proto_projet.hpp"
# include "../includes/debug.hpp"

using namespace std;

void ProtoProjet::unsafe_hard_reset() {
    this->taches.clear();

    Tache* debut = new Tache("Debut", 0);
	Tache* fin = new Tache("Fin", 0);
	fin->ajouteDependance(*debut);
	taches.push_back(fin);
	taches.push_back(debut);
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
    Debug::log("i: " + std::to_string(i) + " j:" + std::to_string(j));
    Tache* t = new Tache(nom, duree);
    Tache* t1 = taches[i];
    Tache* t2 = taches[j];

    t1->ajouteDependance(*t);
    t->ajouteDependance(*t2);
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
	if (i == taches.size() || i == 0)
		return (false);
	
    Tache* t = new Tache(nom, duree);
    Tache* t1 = taches[0];
    Tache* t2 = taches[i];

    t1->ajouteDependance(*t);
    t->ajouteDependance(*t2);
    taches.insert(taches.begin() + i, t);
	topological_sort();
    return (true);
}

bool ProtoProjet::ajoute(const string nom, const int duree, const int tache1, const int tache2)
{
    int i = -1;
    int j = -1;

    for (int k = 0; k < taches.size(); k++){
        if (taches[k]->getId() == tache1)
            i = k;
        if (taches[k]->getId() == tache2)
            j = k;
    }
    if (i == -1 || j == -1)
        return (false);
    
    Tache* t = new Tache(nom, duree);
    Tache* t1 = i < j ? taches[i] : taches[j];
    Tache* t2 = i < j ? taches[j] : taches[i];

    t1->ajouteDependance(*t);
    t->ajouteDependance(*t2);
    if (i < j)
        taches.insert(taches.begin() + j, t);
    else
        taches.insert(taches.begin() + i, t);
	topological_sort();
    return (true);
}