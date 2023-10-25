#ifndef CONSULTANT_HPP
#define CONSULTANT_HPP

#include "gestionnaire.hpp"

class Consultant : public Gestionnaire {
    public:
        std::pair<std::vector<int>, int> avis(const RunProject &);
};

#endif