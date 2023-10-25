#ifndef EXPERT_HPP
#define EXPERT_HPP

#include "gestionnaire.hpp"

class Expert : public Gestionnaire {
    public:
        std::pair<std::vector<int>, int> avis(const RunProject &);
};

#endif