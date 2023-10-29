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

std::vector<std::pair<void (*)(), std::string>> test_functions{
        {test_tasks, "Tasks and dependencies"}, 
        {test_proto, "ProtoProject"},
        {test_cascade, "RunProject cascade"},
        {test_expert, "Expert"}
        };

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
    std::cout << "\n\nRunning tests...\n" << std::endl;
    int successfull = 0;
    for (int i = 0; i < test_functions.size(); i++) {
        std::cout << "|---------------\t";
        std::cout << "Test " << std::to_string(i) << ": " 
            << test_functions[i].second << " \t\t---------------|\n\n" << std::flush;
        
        if (test_a_function(test_functions[i].first)) {
            std::cout << "\n✅ S ✅ U ✅ C ✅ C ✅ E ✅ S ✅ S ✅" << std::endl;
            successfull++;
        } else std::cout << "\n❌ F ❌ A ❌ I ❌ L ❌ E ❌ D ❌" << std::endl;
        std::cout << std::endl;
    }
    
    std::cout << "\n" << std::to_string(successfull) << "/" << 
        std::to_string(test_functions.size());
        if (successfull == test_functions.size())
            std::cout <<" tests were successfull! 🎉" << std::endl;
        else std::cout << " tests were successfull. 😢" << std::endl;
    if (successfull != test_functions.size())
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}