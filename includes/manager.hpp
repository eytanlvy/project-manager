#ifndef GESTIONNAIRE_HPP
#define GESTIONNAIRE_HPP

#include "run_project.hpp"

#include <vector>
#include <cstdlib>
#include <iostream>

class Manager {
    public:
        Manager(const Manager &) = default;
        Manager & operator=(const Manager &) = default;
        ~Manager() = default;
        std::ostream& operator<<(std::ostream& os) = delete;

        virtual std::pair<std::vector<int>, int> review(const RunProject & project);
};

#endif