#ifndef PROJECT_HPP
#define PROJECT_HPP

#include "task.hpp"
#include <cstdlib>
#include <ctime>

class Project
{
	protected:
		std::vector <Task*> tasks;
		Task *get_task(const int task_id);
	public:
		Project();
		Project(const Project& other);
		virtual ~Project();
		
		Project& operator=(const Project& other);
		
		std::vector<Task*> const consult_tasks() const;
		std::pair<int,int> pick_two_random_tasks();
		
		Task *contains(std::string name);
		Task *contains(int id);
		
		void topological_sort();
		void cleanMarks();
	
};
std::ostream& operator<<( std::ostream &out , const Project &x );

#endif