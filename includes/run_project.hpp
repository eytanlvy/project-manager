#ifndef RUN_PROJECT_HPP
#define RUN_PROJECT_HPP

#include "task.hpp"
#include "project.hpp"
#include "proto_project.hpp"

class RunProject : public Project {
	private:
		void reset_tasks(std::vector<bool> memory);
	public:
		RunProject(ProtoProject proto_projet);

		bool run(Task *task, bool force_dependencies = true);
		bool run(const int task_id, bool force_dependencies = true);

		bool run(std::vector<Task*> tasks, bool force_dependencies = true);
		bool run(std::vector<int> tasks_id, bool force_dependencies = true);
};

#endif