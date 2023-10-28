#include "../includes/error_management.hpp"
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
    std::vector<int> tasks;
    ProtoProject protoProject;

    for (int i = 0; i < 6; i++) {
        char current_char = (char)((int)'A' + i);
        std::string current_name = "Task " + std::to_string(current_char);
        
        protoProject.add(current_name, 1);
        tasks.push_back(i);
    }

    RunProject runProject{protoProject};
    int final_task_id = runProject.consult_tasks().front()->getId();
    runProject.run(final_task_id);
}
