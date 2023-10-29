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


    RunProject runProject{protoProject};

    int final_task_id = runProject.consult_tasks()[0]->get_id();

    runProject.run(final_task_id);

    std::cout << "Expected output" << std::endl;
    std::cout << "[1], [1], [1], [1], [1], [1], [1], " << std::endl;
    std::cout << std::endl;
    std::cout << "Achieved output" << std::endl;
    std::vector<Task *> tasks = runProject.consult_tasks();
    for (auto task: tasks)
        std::cout <<"[" << task->is_accomplished() << "], ";
    std::cout << std::endl;
}

void test_cascade2() {
    ProtoProject protoProject;

    protoProject.add("Task A", 2);
    Task *task_A = protoProject.contains("Task A");
    protoProject.add("Task B", 2, 3);
    Task *task_B = protoProject.contains("Task B");


    protoProject.add("Task C", 6, task_A->get_id());
    Task *task_C = protoProject.contains("Task C"); 
    protoProject.add("Task D", 1, task_C->get_id());

    protoProject.add("Task E", 15, task_B->get_id());


    RunProject runProject{protoProject};

    std::vector<int> tasks_to_run;
    tasks_to_run.push_back(runProject.consult_tasks()[2]->get_id());
    runProject.run(tasks_to_run);

    std::cout << "Expected output" << std::endl;
    std::cout << "[0], [0], [1], [1], [0], [1], [1], " << std::endl;
    std::cout << std::endl;
    std::cout << "Achieved output" << std::endl;
    std::vector<Task *> tasks = runProject.consult_tasks();
    for (auto task: tasks)
        std::cout <<"[" << task->is_accomplished() << "], ";
    std::cout << std::endl;
}