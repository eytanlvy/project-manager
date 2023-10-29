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

void test_proto() {
    ProtoProject protoProject;


    // Adds task D, duration 5, which depends on task Debut
    protoProject.add("Task D", 5, 2); 
    assert(protoProject.consult_tasks()[1]->get_id() == 3);
    std::cout << "-------------------" << std::endl;
    std::cout << "TESTING ADD() #1 : "  << std::endl;
    std::cout << std::endl;
    std::cout << "Expected output: "  << std::endl;
    std::cout << "#1 : \"Fin\" --> 2, 3 " << std::endl;
    std::cout << "#2 : \"Debut\" " << std::endl;
    std::cout << "#3 : \"Task D\" --> 2 " << std::endl;
    std::cout <<std::endl;
    std::cout << "Achieved output: "  << std::endl;
    protoProject.consult_tasks()[0]->print_dependencies();
    std::cout << "-------------------" << std::endl;


    // Adds task E of duration 2 which depends on task D
    protoProject.add("Task E", 2, 3, 1);  
    assert(protoProject.consult_tasks()[1]->get_id() == 4);
    std::cout << "TESTING ADD() #2 : "  << std::endl;
    std::cout << std::endl;
    std::cout << "Expected output: "  << std::endl;
    std::cout << "#1 : \"Fin\" --> 2, 3, 4 " << std::endl;
    std::cout << "#2 : \"Debut\" " << std::endl;
    std::cout << "#3 : \"Task D\" --> 2 " << std::endl;
    std::cout << "#4 : \"Task E\" --> 3 " << std::endl;
    std::cout <<std::endl;
    std::cout << "Achieved output: "  << std::endl;
    protoProject.consult_tasks()[0]->print_dependencies();
    std::cout << "-------------------" << std::endl;


    //Randomly add tasks A, B and C
    protoProject.add("Task A", 3);
    protoProject.add("Task B", 2);
    protoProject.add("Task C", 4);
    assert(protoProject.consult_tasks().size() == 7);
    std::cout << "TESTING ADD() #3 : "  << std::endl;
    std::cout << std::endl;
    std::cout << "Expected output: "  << std::endl;
    std::cout << "3 new tasks added with id #5, #6 and #7" <<std::endl;
    std::cout << "Len of tasks: 7" << std::endl; 
    std::cout <<std::endl;   
    std::cout << "Achieved output: "  << std::endl;
    protoProject.consult_tasks()[0]->print_dependencies();
    std::cout << "-------------------" << std::endl;

    // Invalid insertions
    protoProject.add("Task F", 2, 0, 0);
    protoProject.add("Task G", 1, 10);
    protoProject.add("Task H", 1, 10, 1);
    protoProject.add("Task I", 1, 0);
    assert(protoProject.consult_tasks().size() == 7);
    std::cout << "INVALID ADD() ATTEMPTS: "  << std::endl;
    std::cout << std::endl;
    std::cout << "Expected output: "  << std::endl;
    std::cout << "Nothing has changed" <<std::endl;
    std::cout << "Len of tasks: 7" << std::endl; 
    std::cout <<std::endl;   
    std::cout << "Achieved output: "  << std::endl;
    protoProject.consult_tasks()[0]->print_dependencies();
    std::cout << "-------------------" << std::endl;

    ProtoProject protoProject2(protoProject);
    for (int i = 0; i < protoProject.consult_tasks().size(); i++)
        assert(protoProject.consult_tasks()[i]->get_id() == protoProject2.consult_tasks()[i]->get_id());

}
