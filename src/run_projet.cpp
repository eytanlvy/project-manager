#include "../includes/run_projet.hpp"

#include "../includes/utils/error_management.hpp"
#include <vector>

RunProjet::RunProjet(ProtoProjet proto_projet) {
    this->taches = proto_projet.taches;
    proto_projet.unsafe_hard_reset();
};

void RunProjet::run(Tache *tache) {
    tache->realise_cascade();
}

void RunProjet::run(std::vector<Tache *> taches) {
    for (Tache *task : taches)
        this->run(task);
}

void RunProjet::run(const int tache_id) {
    Tache *task = this->get_task(tache_id);
    this->run(task);
}

void RunProjet::run(std::vector<int> taches_id) {
    for (int task : taches_id)
        this->run(task);
}