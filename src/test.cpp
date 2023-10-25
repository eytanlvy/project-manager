#include "../includes/error_management.hpp"
#include <iostream>
#include <stdlib.h>

#include "../includes/task.hpp"
#include "../includes/proto_project.hpp"
#include "../includes/debug.hpp"

void test_tasks() {
    std::cout << "Test 1: Tâches et dépendances" << std::endl;

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

void test_proto()
{
    std::cout << "Test 2: ProtoProject" << std::endl;
    ProtoProject protoProject;
    for (Task* task : protoProject.consult_tasks()) {
        std::cout << *task << std::endl;
    }

    protoProject.add("Tache A", 3);
    protoProject.add("Tache B", 2);
    protoProject.add("Tache C", 4);

    std::cout << "ProtoProject après ajout de tâches aléatoires:" << std::endl;
    for (Task* task : protoProject.consult_tasks()) {
        std::cout << *task << std::endl;
    }

    protoProject.add("Tache D", 5, 8); 

    std::cout << "ProtoProject après ajout de Tache D:" << std::endl;
    for (Task* task : protoProject.consult_tasks()) {
        std::cout << *task << std::endl;
    }

    protoProject.add("Tache E", 2, 11, 10); 

    std::cout << "ProtoProject après ajout de Tache E:" << std::endl;
    for (Task* task : protoProject.consult_tasks()) {
        std::cout << *task << std::endl;
    }

}

int main(void) {
    test_tasks();
    test_proto();
    
    std::cout << "Tests were successfull!" << std::endl;
    return EXIT_SUCCESS;
}