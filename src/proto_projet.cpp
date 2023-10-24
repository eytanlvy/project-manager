# include "../includes/proto_projet.hpp"

using namespace std;


ProtoProjet::ProtoProjet()
{
	Tache* debut = new Tache("Debut", 0);
	Tache* fin = new Tache("Fin", 0);
	fin->ajouteDependance(*debut);
	taches.push_back(fin);
	taches.push_back(debut);
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

    cout<<"APAGNAN"<<endl;

	ProtoProjet protoProjet{};
    cout << "ProtoProjet initial:" << endl;

    protoProjet.ajoute("Tache A", 3);
    protoProjet.ajoute("Tache B", 2);
    protoProjet.ajoute("Tache C", 4);

    cout << "ProtoProjet après ajout de tâches aléatoires:" << endl;
    for (Tache* tache : protoProjet.consult_tasks()) {
        cout << *tache << endl;
    }

    protoProjet.ajoute("Tache D", 5, 2);

    cout << "ProtoProjet après ajout de Tache D:" << endl;
    for (Tache* tache : protoProjet.consult_tasks()) {
        cout << *tache << endl;
    }

    protoProjet.ajoute("Tache E", 2, 1, 3);

    cout << "ProtoProjet après ajout de Tache E:" << endl;
    for (Tache* tache : protoProjet.consult_tasks()) {
        cout << *tache << endl;
	}
    return 0;
}