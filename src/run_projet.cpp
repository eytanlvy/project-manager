#include "../includes/run_projet.hpp"

#include <vector>

RunProjet::RunProjet(ProtoProjet proto_projet) {
    this->taches = proto_projet.taches;
    proto_projet.unsafe_hard_reset();
};