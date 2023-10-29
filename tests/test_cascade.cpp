#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../includes/task.hpp"
#include "../includes/proto_project.hpp"
#include "../includes/run_project.hpp"
#include "../includes/debug.hpp"
#include "../includes/test.hpp"

void test_cascade() {
    ProtoProject protoProject;

    protoProject.add("Task A", 2);
    Task *task_A = protoProject.contains("Task A");
    protoProject.add("Task B", 2, 3);
    Task *task_B = protoProject.contains("Task B");


    protoProject.add("Task C", 1, task_A->get_id());
    Task *task_C = protoProject.contains("Task C"); 
    protoProject.add("Task D", 1, task_C->get_id());

    protoProject.add("Task E", 20, task_B->get_id());

    std::cout << "Create a protoProject" << std::endl;

    RunProject runProject{protoProject};

    int final_task_id = runProject.consult_tasks()[0]->get_id();

    runProject.run(final_task_id);

    std::vector<Task *> tasks = runProject.consult_tasks();
    for (auto task: tasks)
        std::cout <<"[" << task->is_accomplished() << "], ";
    std::cout << std::endl;
}
