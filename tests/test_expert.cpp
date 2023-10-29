#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <unistd.h>

#include "../includes/task.hpp"
#include "../includes/proto_project.hpp"
#include "../includes/run_project.hpp"
#include "../includes/expert.hpp"
#include "../includes/debug.hpp"
#include "../includes/test.hpp"


void test_expert() {
    ProtoProject protoProject;

    protoProject.add("Task A", 2);
    auto task_A = protoProject.contains("Task A");
    protoProject.add("Task B", 2, 3);
    auto task_B = protoProject.contains("Task B");


    protoProject.add("Task C", 1, task_A->get_id());
    auto task_C = protoProject.contains("Task C"); 
    protoProject.add("Task D", 1, task_C->get_id());

    protoProject.add("Task E", 20, task_B->get_id());

    std::cout << "Create a protoProject" << std::endl;

    RunProject runProject{protoProject};
    std::cout << "Convert it to a runProject" << std::endl;

    Expert expert;
    std::cout << "Initialise an expert" << std::endl;

    auto review = expert.review(runProject);
    assert(runProject.consult_tasks().size() == 7);

    std::cout << "Expected result" << std::endl;
    std::cout << "\tTask list : [Debut, Task A, Task B, Task E, Task C, Task D, Fin, ]" << std::endl;
    std::cout << "\tReview time : 24" << std::endl;

    std::cout << "Review result" << std::endl;
    std::cout << "\tTask list : " + Debug::task_list_to_string(runProject, review.first) << std::endl;
    std::cout << "\tReview time : " + std::to_string(review.second) << std::endl;
}
