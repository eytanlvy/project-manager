#ifndef EXPERT_HPP
#define EXPERT_HPP

#include "manager.hpp"

class Expert : public Manager {
    public:
        std::pair<std::vector<int>, int> review(const RunProject & project);
};

#endif