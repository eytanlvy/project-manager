#ifndef GESTIONNAIRE_HPP
#define GESTIONNAIRE_HPP

#include "run_project.hpp"

#include <vector>
#include <cstdlib>

class Gestionnaire {
    public:
        virtual std::pair<std::vector<int>, int> avis(const RunProject &);
};

#endif