#ifndef PROTO_PROJECT_HPP
#define PROTO_PROJECT_HPP

#include "project.hpp"

class RunProject;

class ProtoProject : public Project {
	friend class RunProject;
	private:
		void unsafe_hard_reset();
		void insert_between_two_tasks(Task *new_task, Task *task_after, Task *task_before);
	public:
		ProtoProject();
		ProtoProject(const ProtoProject& other);

		bool add (const std::string name, const int duration);
		bool add (const std::string name, const int duration, const int task_id);
		bool add (const std::string name, const int duration, const int task_1, const int task_2);
};

#endif