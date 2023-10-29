#ifndef CONSULTANT_HPP
#define CONSULTANT_HPP

#include "manager.hpp"
#include "ostream"

class Consultant : public Manager {
    public:
        std::pair<std::vector<int>, int> review(const RunProject & project);

        Consultant() = default;
        Consultant(const Consultant &) = default;
        Consultant & operator=(const Consultant &) = default;
        ~Consultant() = default;
        std::ostream& operator<<(std::ostream& os) = delete;
};

#endif