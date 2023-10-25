#include "../includes/error_management.hpp"
#include <iostream>
#include <stdlib.h>

#include "../includes/task.hpp"
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

int main(void) {
    test_tasks();
    std::cout << "Test were successfull!" << std::endl;
    return EXIT_SUCCESS;
}