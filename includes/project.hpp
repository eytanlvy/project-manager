#ifndef PROJECT_HPP
#define PROJECT_HPP

#include "task.hpp"
#include <cstdlib>
#include <ctime>
#include <optional>

class Project
{
	protected:
		std::vector <Task*> tasks;
		Task *get_task(const int task_id);
		Project();
		void topological_sort();
		void clean_marks();
	public:
		virtual ~Project();
		
		std::vector<Task*> const consult_tasks() const;
		std::pair<int,int> pick_two_random_tasks() const;
		
		Task *contains(std::string name) const;
		Task *contains(int id) const;
};

std::ostream& operator<<( std::ostream &out , const Project &x );

#endif