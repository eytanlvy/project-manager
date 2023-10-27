#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cassert>  

class Task
{
	private:
		std::string name;
		int id;
		int duration;
		bool is_accomplished;
		std::vector<Task*> dependencies;
		static int lastId;
		bool marked{false};

		Task(const Task& other);

	public:
		friend class ProtoProject;
		Task(const std::string& name, int duration);
		virtual ~Task();
		const Task& operator=(const Task& other)=delete;

		std::string const getName() const;
		int const getId() const;
		int const getDuration() const;
		bool const isAccomplished() const;
		std::vector<Task*> const getDependances() const;
		bool is_accomplishable();
		bool accomplish();
		void accomplish_cascade();
		bool depends_from(Task & x);
		bool addDependency(Task & x);
		int durationParallelized();

		const bool isMarked() const;
		void mark(bool value);
		void PP_postfixe(std::vector<Task*>& sortedTasks);
};

std::ostream& operator<<( std::ostream &out , const Task &x );

#endif