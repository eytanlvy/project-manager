#ifndef GESTIONNAIRE_HPP
#define GESTIONNAIRE_HPP

#include "run_project.hpp"

#include <vector>
#include <cstdlib>

class Manager {
    public:
        virtual std::pair<std::vector<int>, int> review(const RunProject &);
};

#endif