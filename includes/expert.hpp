#ifndef EXPERT_HPP
#define EXPERT_HPP

#include "manager.hpp"
#include <ostream>
#include <vector>
#include <map>

class Expert : public Manager {
    private:
        static void update_indices_of_necessity(
            int const & task_to_free,
            std::vector<std::vector<int>> const & all_dependencies,
            std::vector<int> & indices_of_necessity
        );
        static void update_min(
            int & min_value, int & min_index, 
            int const & x_value, int const & x_index
            );
        static void find_nearest(
            std::vector<Task *> const &tasks,
            std::map<int, int> const & map,
            std::vector<std::vector<int>> const & all_dependencies,
            int & remaning,
            std::vector<bool> & visiteds,
            std::vector<int> & distances,
            std::vector<int> & indices_of_necessity,
            std::vector<int> & result
        );
        static void sort_by_distance_to_end(
            std::vector<Task *> const tasks,
            std::vector<int> &result
        );

    public:
        Expert() = default;
        Expert(const Expert &) = default;
        Expert & operator=(const Expert &) = default;
        ~Expert() = default;
        std::ostream& operator<<(std::ostream& os) = delete;

        std::pair<std::vector<int>, int> review(const RunProject & project);
};

#endif