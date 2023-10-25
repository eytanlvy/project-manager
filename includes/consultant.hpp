#ifndef CONSULTANT_HPP
#define CONSULTANT_HPP

#include "manager.hpp"

class Consultant : public Manager {
    public:
        std::pair<std::vector<int>, int> review(const RunProject &);
};

#endif