#include "../includes/consultant.hpp"
#include "../includes/error_management.hpp"

/*
    Une seul personne doit réaliser les taches => pas de parralèllisation
    renvois <liste de tache restantes, dans l'ordre, somme du temps des taches>
*/
std::pair<std::vector<int>, int> Consultant::avis(const RunProjet &) {
    throw NotImplemented();
}