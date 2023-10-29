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
	public:
		virtual ~Project();
		Project(const Project& other) = delete;
		Project& operator=(const Project& other) = default;
		
		std::vector<Task*> const consult_tasks() const;
		std::pair<int,int> pick_two_random_tasks() const;
		
		Task *contains(std::string name) const;
		Task *contains(int id) const;
		
		void topological_sort();
		void cleanMarks();
	
};

std::ostream& operator<<( std::ostream &out , const Project &x );

#endif