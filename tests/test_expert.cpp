#include "../includes/error_management.hpp"
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

std::string task_list_to_string(RunProject const & project, std::vector<int> tasks_id) {
    std::string result = "[";
    for (auto task_id : tasks_id)
        result += project.contains(task_id)->getName();
    result += "]";
    return result;
};

void test_expert() {
    ProtoProject protoProject;

    protoProject.add("Task A", 2);
    auto task_A = protoProject.contains("Task A");
    protoProject.add("Task B", 2);
    auto task_B = protoProject.contains("Task B");


    protoProject.add("Task C", 1, task_A->getId());
    auto task_C = protoProject.contains("Task C"); 
    protoProject.add("Task D", 1, task_C->getId());

    protoProject.add("Task E", 20, task_B->getId());

    Debug::log("Create a protoProject");

    RunProject runProject{protoProject};
    Debug::log("Convert it to a runProject");

    Expert expert;
    Debug::log("Initialise an expert");

    auto review = expert.review(runProject);

    Debug::log("Review result");
    Debug::log("\tTask list : " + task_list_to_string(runProject, review.first));
    Debug::log("\tReview time : " + std::to_string(review.second));
}
