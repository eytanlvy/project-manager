#ifndef EXPERT_HPP
#define EXPERT_HPP

#include "manager.hpp"
#include <ostream>

class Expert : public Manager {
    public:
        Expert(const Expert &) = default;
        Expert & operator=(const Expert &) = default;
        ~Expert() = default;
        std::ostream& operator<<(std::ostream& os) = delete;

        std::pair<std::vector<int>, int> review(const RunProject & project);
};

#endif