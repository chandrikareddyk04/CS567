#include <deepstate/DeepState.hpp>
#include "task_manager.hpp"

using namespace deepstate;

TEST(TaskManager, AddTask) {
    TaskManager taskManager;
    Task task("Task 1", "Description 1", 3, "2024-05-31");
    taskManager.addTask(task);
    ASSERT_EQ(taskManager.getNumTasks(), 1);
}

TEST(TaskManager, MarkTaskCompleted) {
    TaskManager taskManager;
    Task task("Task 1", "Description 1", 3, "2024-05-31");
    taskManager.addTask(task);
    taskManager.markTaskCompleted(0);
    ASSERT_TRUE(taskManager.getTask(0).completed);
}

TEST(TaskManager, SortTasksByPriority) {
    TaskManager taskManager;
    taskManager.addTask(Task("Task 1", "Description 1", 3, "2024-05-31"));
    taskManager.addTask(Task("Task 2", "Description 2", 1, "2024-06-15"));
    taskManager.addTask(Task("Task 3", "Description 3", 2, "2024-07-01"));
    taskManager.sortTasksByPriority();
    ASSERT_TRUE(taskManager.getTask(0).priority <= taskManager.getTask(1).priority);
    ASSERT_TRUE(taskManager.getTask(1).priority <= taskManager.getTask(2).priority);
}

TEST(TaskManager, SortTasksByDeadline) {
    TaskManager taskManager;
    taskManager.addTask(Task("Task 1", "Description 1", 3, "2024-06-15"));
    taskManager.addTask(Task("Task 2", "Description 2", 1, "2024-05-31"));
    taskManager.addTask(Task("Task 3", "Description 3", 2, "2024-07-01"));
    taskManager.sortTasksByDeadline();
    ASSERT_TRUE(taskManager.getTask(0).deadline <= taskManager.getTask(1).deadline);
    ASSERT_TRUE(taskManager.getTask(1).deadline <= taskManager.getTask(2).deadline);
}