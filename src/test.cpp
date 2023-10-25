#include "../includes/error_management.hpp"
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../includes/task.hpp"
#include "../includes/proto_project.hpp"
#include "../includes/debug.hpp"

void test_tasks() {
    Task task1("task1", 3);
    Task task2("task2", 2);
    Task task3("task3", 4);

    task1.addDependency(task2);
    task1.addDependency(task3);
    task2.addDependency(task3);

	assert(task1.depends_from(task2));
	assert(!task2.depends_from(task1));
	assert(task2.depends_from(task3));
	assert(!task3.depends_from(task1));

    Task task4("task4", 2);
    Task task5("task5", 1);

    task4.addDependency(task1);
    task4.addDependency(task2);
    task5.addDependency(task4);

    task3 = task5;
	assert(task3.depends_from(task1) && task3.depends_from(task2) &&task3.depends_from(task4));
	assert(task5.depends_from(task1) && task5.depends_from(task2) && task5.depends_from(task4));
	assert(task5.durationParallelized() == task3.durationParallelized());
}

void test_proto() {
    test_tasks(); // test non indépendant ?
    ProtoProject protoProject;

    protoProject.add("Task D", 5, 6); 
    assert(protoProject.consult_tasks()[1]->getId() == 8);  

    protoProject.add("Task E", 2, 8, 6); 
    assert(protoProject.consult_tasks()[2]->getId() == 9);


    protoProject.add("Task A", 3);
    protoProject.add("Task B", 2);
    protoProject.add("Task C", 4);
    assert(protoProject.consult_tasks().size() == 7);

    protoProject.add("Task F", 2, 0, 6);
    protoProject.add("Task G", 1, 5);
    assert(protoProject.consult_tasks().size() == 7);

}


bool test_a_function(void (*functionToTest)()) {
    pid_t child_pid = fork();

    if (child_pid == 0) {
        functionToTest();
        exit(0);
    }

    int status;
    waitpid(child_pid, &status, 0);
    return WIFEXITED(status) && (WEXITSTATUS(status) == 0);
}

int main(void) {
    std::vector<std::pair<void (*)(), std::string>> test_functions{
        std::pair<void (*)(), std::string>{test_tasks, "Tasks and dependencies"}, 
        std::pair<void (*)(), std::string>{test_proto, "ProtoProject"}
        };

    int successfull = 0;
    for (int i = 0; i < test_functions.size(); i++) {
        std::cout << "Test " << std::to_string(i) << ": " 
            << test_functions[i].second << " \t| " << std::flush;
        
        if (test_a_function(test_functions[i].first)) {
            std::cout << "✅";
            successfull++;
        } else std::cout << "❌";
        std::cout << std::endl;
    }
    
    std::cout << "\n" << std::to_string(successfull) << "/" << 
        std::to_string(test_functions.size()) << 
        " tests were successfull! 🎉" << std::endl;
    if (successfull != test_functions.size())
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}