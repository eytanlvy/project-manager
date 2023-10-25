#include "../includes/run_projet.hpp"

#include "../includes/error_management.hpp"
#include <vector>

RunProjet::RunProjet(ProtoProjet proto_projet) {
    this->taches = proto_projet.taches;
    proto_projet.unsafe_hard_reset();
};

bool RunProjet::run(Tache *tache, bool force_dependencies=true) {
    if (!force_dependencies)
        return tache->realise();
    
    tache->realise_cascade();

    return true;
}

bool RunProjet::run(std::vector<Tache *> taches, bool force_dependencies=true) {
    if (!force_dependencies)
        throw NotImplemented();

    for (Tache *task : taches)
        this->run(task);

    return true;
}

bool RunProjet::run(const int tache_id, bool force_dependencies=true) {
    Tache *task = this->get_task(tache_id);

    return this->run(task);
}

bool RunProjet::run(std::vector<int> taches_id, bool force_dependencies=true) {
    if (!force_dependencies)
        throw NotImplemented();

    for (int task : taches_id)
        this->run(task);

    return true;
}