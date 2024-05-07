#include <deepstate/DeepState.hpp>
#include "task_manager.hpp"

#define MAX_STRING_LENGTH 100

using namespace deepstate;

TEST(TaskManager, AddTask) {
    TaskManager taskManager;
    std::string name = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    std::string description = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    int priority = DeepState_IntInRange(1, 5);
    std::string deadline = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    Task task(name, description, priority, deadline);
    size_t initialNumTasks = taskManager.getNumTasks();
    taskManager.addTask(task);
    ASSERT(taskManager.getNumTasks() >= initialNumTasks);
}

TEST(TaskReminder, SetReminder) {
    TaskReminder taskReminder;
    std::string name = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    std::string description = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    int priority = DeepState_IntInRange(1, 5);
    std::string deadline = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    int reminderType = DeepState_Int();
    int reminderFrequency = DeepState_Int();
    Task task(name, description, priority, deadline);
    taskReminder.setReminder(task, reminderType, reminderFrequency);
}

TEST(UserAuthentication, CreateUser) {
    UserAuthentication userAuth;
    std::string username = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    std::string password = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    userAuth.createUser(username, password);
}

TEST(UserAuthentication, AuthenticateUser) {
    UserAuthentication userAuth;
    std::string username = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    std::string password = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    userAuth.authenticateUser(username, password);
}
TEST(TaskManager, MarkTaskCompleted) {
    TaskManager taskManager;
    std::string name = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    std::string description = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    int priority = DeepState_IntInRange(1, 5);
    std::string deadline = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    Task task(name, description, priority, deadline);
    taskManager.addTask(task);
    size_t index = DeepState_SizeInRange(0, taskManager.getNumTasks() - 1);
    taskManager.markTaskCompleted(index);
}

TEST(TaskManager, EditTask) {
    TaskManager taskManager;
    std::string name = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    std::string description = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    int priority = DeepState_IntInRange(1, 5);
    std::string deadline = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    Task task(name, description, priority, deadline);
    taskManager.addTask(task);
    size_t index = DeepState_SizeInRange(0, taskManager.getNumTasks() - 1);
    std::string newName = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    std::string newDescription = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    int newPriority = DeepState_IntInRange(1, 5);
    std::string newDeadline = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    Task newTask(newName, newDescription, newPriority, newDeadline);
    taskManager.editTask(index, newTask);
}

TEST(TaskManager, SearchTasksByName) {
    TaskManager taskManager;
    std::string name = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    std::string description = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    int priority = DeepState_IntInRange(1, 5);
    std::string deadline = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    Task task(name, description, priority, deadline);
    taskManager.addTask(task);
    std::string searchName = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    taskManager.searchTasksByName(searchName);
}

TEST(TaskManager, GetTask) {
    TaskManager taskManager;
    std::string name = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    std::string description = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    int priority = DeepState_IntInRange(1, 5);
    std::string deadline = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    Task task(name, description, priority, deadline);
    taskManager.addTask(task);
    size_t index = DeepState_SizeInRange(0, taskManager.getNumTasks() - 1);
    Task retrievedTask = taskManager.getTask(index);
}

TEST(TaskReminder, ScheduleNotification) {
    TaskReminder taskReminder;
    std::string name = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    std::string description = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    int priority = DeepState_IntInRange(1, 5);
    std::string deadline = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    int reminderFrequency = DeepState_Int();
    Task task(name, description, priority, deadline);
    taskReminder.scheduleNotification(task, reminderFrequency);
}

TEST(TaskReminder, SendEmailReminder) {
    TaskReminder taskReminder;
    std::string name = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    std::string description = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    int priority = DeepState_IntInRange(1, 5);
    std::string deadline = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    Task task(name, description, priority, deadline);
    taskReminder.sendEmailReminder(task);
}

TEST(TaskReminder, SendSMSReminder) {
    TaskReminder taskReminder;
    std::string name = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    std::string description = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    int priority = DeepState_IntInRange(1, 5);
    std::string deadline = DeepState_CStrUpToLen(MAX_STRING_LENGTH);
    Task task(name, description, priority, deadline);
    taskReminder.sendSMSReminder(task);
}
