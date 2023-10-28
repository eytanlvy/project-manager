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

    std::cout << "-------------------" << std::endl;
    std::cout << "TASK METHODS: "  << std::endl;
    std::cout << std::endl;
    std::cout << "Expected output: "  << std::endl;
    std::cout << "#5 : \"task5\" --> 4 " << std::endl;
    std::cout << "#4 : \"task4\" --> 1 " << std::endl;
    std::cout << "#1 : \"task1\" --> 2, 3 " << std::endl; 
    std::cout << "#2 : \"task2\" --> 3 " << std::endl;
    std::cout << "#3 : \"task3\" " << std::endl;
    std::cout <<std::endl;

    std::cout << "Achieved output: "  << std::endl;
    task5.print_dependencies();
    std::cout << "-------------------" << std::endl;

}