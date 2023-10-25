#ifndef PROTO_PROJECT_HPP
#define PROTO_PROJECT_HPP

#include "project.hpp"

class RunProject;

class ProtoProject : public Project {
	friend class RunProject;
	private:
		void unsafe_hard_reset();
	public:
		ProtoProject();
		bool ajoute (const std::string name, const int duration);
		bool ajoute (const std::string name, const int duration, const int task_id);
		bool ajoute (const std::string name, const int duration, const int task_1, const int task_2);
};

#endif