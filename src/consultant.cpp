#include "../includes/consultant.hpp"
#include "../includes/error_management.hpp"

/*
    Une seul personne doit réaliser les tasks => pas de parralèllisation
    renvois <liste de tache restantes, dans l'ordre, somme du temps des tasks>
*/
std::pair<std::vector<int>, int> Consultant::avis(const RunProject &) {
    throw NotImplemented();
}