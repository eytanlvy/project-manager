#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cassert>  

class ProtoProject;
class RunProject;

class Task
{
	private:
		std::string name;
		int id;
		int duration;
		bool accomplished;
		std::vector<Task*> dependencies;
		static int lastId;
		bool marked{false};

		Task(const Task& other);
		void print_dependencies(std::vector<int>& printed) const;

	public:
		friend class ProtoProject;
		friend class RunProject;

		Task(const std::string& name, int duration);
		virtual ~Task();
		const Task& operator=(const Task& other) = delete;

		std::string const getName() const;
		int const getId() const;
		int const get_duration() const;
		bool const is_accomplished() const;
		std::vector<Task*> const get_dependencies() const;
		bool is_accomplishable();
		bool accomplish();
		void accomplish_cascade();
		bool depends_from(Task & x);
		bool add_dependency(Task & x);
		int duration_parallelized();

		const bool isMarked() const;
		void mark(bool value);
		void pp_postfixe(std::vector<Task*>& sortedTasks);

		void print_dependencies() const;
};

std::ostream& operator<<( std::ostream &out , const Task &x );

#endif