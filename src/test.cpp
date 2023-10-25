#include "../includes/error_management.hpp"
#include <iostream>
#include <stdlib.h>

#include "../includes/tache.hpp"
#include "../includes/proto_projet.hpp"

void test_taches() {
    std::cout << "Test 1: Tâches et dépendances" << std::endl;

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
	assert(tache3.depends_from(tache1) && tache3.depends_from(tache2) &&tache3.depends_from(tache4));
	assert(tache5.depends_from(tache1) && tache5.depends_from(tache2) && tache5.depends_from(tache4));
	assert(tache5.dureeParal() == tache3.dureeParal());
}

void test_proto()
{
    std::cout << "Test 2: ProtoProjet" << std::endl;
    ProtoProjet protoProjet;
    for (Tache* tache : protoProjet.consult_tasks()) {
        std::cout << *tache << std::endl;
    }

    protoProjet.ajoute("Tache A", 3);
    protoProjet.ajoute("Tache B", 2);
    protoProjet.ajoute("Tache C", 4);

    std::cout << "ProtoProjet après ajout de tâches aléatoires:" << std::endl;
    for (Tache* tache : protoProjet.consult_tasks()) {
        std::cout << *tache << std::endl;
    }

    protoProjet.ajoute("Tache D", 5, 2); 

    std::cout << "ProtoProjet après ajout de Tache D:" << std::endl;
    for (Tache* tache : protoProjet.consult_tasks()) {
        std::cout << *tache << std::endl;
    }

    protoProjet.ajoute("Tache E", 2, 1, 3); 

    std::cout << "ProtoProjet après ajout de Tache E:" << std::endl;
    for (Tache* tache : protoProjet.consult_tasks()) {
        std::cout << *tache << std::endl;
    }

}

int main(void) {
    test_taches();
    test_proto();
    
    std::cout << "Tests were successfull!" << std::endl;
    return EXIT_SUCCESS;
}