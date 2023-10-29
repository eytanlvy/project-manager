#include "../includes/expert.hpp"
#include "../includes/error_management.hpp"
#include <../includes/task.hpp>

#include <algorithm>
#include <tuple>
#include <map>

void Expert::update_min(int & min_value, int & min_index, int const & x_value, int const & x_index) {
    if (min_value < x_value && min_value != -1) {
        min_value = x_value;
        min_index = x_index;
    }
}

void Expert::find_nearest(
    std::vector<Task *> const &tasks,
    std::map<int, int> const & map,
    std::vector<std::vector<int>> const & all_dependencies,

    int & remaning,
    std::vector<bool> & visiteds,
    std::vector<int> & distances,
    std::vector<int> & result
) {

    int min_distance = -1;
    int min_index = -1;


    for (int i = 0; i < tasks.size(); i++) {
        Task const *parent = tasks[i];
        int parent_distance = distances[i];
        
        if(parent_distance == -1) continue;
        for (int child_index : all_dependencies[map.at(parent->getId())]) {
            if (visiteds[child_index]) continue;
            distances[child_index] = parent_distance + tasks[child_index]->get_duration();
            update_min(min_distance, min_index, distances[child_index], child_index);
        }
    }

    visiteds[min_index] = true;
    result.push_back(map.at(min_index));
    remaning--;
}

void Expert::sort_by_distance_to_end(
    std::vector<Task *> const tasks,
    std::vector<int> &result
    ) {

    std::map<int, int> map;
    for (int i = 0; i < tasks.size(); i++)
        map.insert({tasks[i]->getId(), i});

    int remaning = 0;

    std::vector<std::vector<int>> all_dependencies(tasks.size());
    std::vector<bool> visiteds;
    std::vector<int> distances;
    for (auto task : tasks) {
        visiteds.push_back(task->is_accomplished());
        if (!task->is_accomplished()) 
            remaning++;

        distances.push_back(-1);
        for (auto dependence : task->get_dependencies())
            all_dependencies[ map[task->getId()] ].push_back(
                map[dependence->getId()]
            );
    }

    remaning--;
    visiteds[0] = true;
    distances[0] = 0;
    result.push_back(tasks[0]->getId());

    while (remaning != 0)
        find_nearest(
            tasks, map, all_dependencies, // à ne pas modifier
            remaning, visiteds, distances, result // à actualiser
        );
}

/*
    Les taches peuvent être paraléllisées.
    renvois <liste de tache restantes, dans l'ordre, temps d'execution des taches>
*/
std::pair<std::vector<int>, int> Expert::review(const RunProject & project) {
    std::vector<Task *> tasks = project.consult_tasks();
    std::vector<int> remaning_tasks;

    int remaning_time = tasks.front()->duration_parallelized();
    if (tasks[0]->is_accomplished()) return {remaning_tasks, remaning_time};

    sort_by_distance_to_end(tasks, remaning_tasks);
    std::reverse(remaning_tasks.begin(), remaning_tasks.end());

    return {remaning_tasks, remaning_time};
}