#include "../includes/expert.hpp"
#include "../includes/error_management.hpp"

/*
    Les taches peuvent être paraléllisées.
    renvois <liste de tache restantes, dans l'ordre, temps d'execution des taches>
*/
std::pair<std::vector<int>, int> Expert::review(const RunProject &) {
    throw NotImplemented();
}