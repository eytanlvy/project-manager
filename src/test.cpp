#include "../includes/utils/error_management.hpp"
#include <iostream>
#include <stdlib.h>

#include "../includes/tache.hpp"

/*
    Test must return true if they fail, false otherwise
*/

bool test_taches(bool debug) {
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
	assert(tache3.depends_from(tache1) && tache3.depends_from(tache2) &&tache3.depends_from(tache4));
	assert(tache5.depends_from(tache1) && tache5.depends_from(tache2) && tache5.depends_from(tache4));
	assert(tache5.dureeParal() == tache3.dureeParal());
    
    return false;
}

int main(void) {
    test_taches(false);
    std::cout << "Test successfull" << std::endl;
    return EXIT_SUCCESS;
}