#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Task {
public:
    std::string name;
    std::string description;
    unsigned int priority;
    std::string deadline;
    bool completed;

    Task() : name(""), description(""), priority(0), deadline(""), completed(false) {}
    Task(const std::string& name, const std::string& description, unsigned int priority, const std::string& deadline)
        : name(name), description(description), priority(priority), deadline(deadline), completed(false) {}
};

class TaskManager {
private:
    std::vector<Task> tasks;
    std::unordered_map<unsigned int, std::vector<Task>> tasksByPriority;

public:
    void addTask(const Task& task);
    void displayTasksByPriority(unsigned int priority);
    void displayAllTasks();
    void markTaskCompleted(size_t index);
    void editTask(size_t index, const Task& newTask);
    void sortTasksByPriority();
    void sortTasksByDeadline();
    void searchTasksByName(const std::string& name);
    int getNumTasks() const;
    Task getTask(size_t index) const;
};

class TaskReminder {
public:
    static const int NOTIFICATION = 1;
    static const int EMAIL = 2;
    static const int SMS = 3;

    static const int ONCE = 1;
    static const int DAILY = 2;
    static const int WEEKLY = 3;

    void setReminder(const Task& task, int reminderType, int reminderFrequency);

    void scheduleNotification(const Task& task, int reminderFrequency);
    void sendEmailReminder(const Task& task);
    void sendSMSReminder(const Task& task);
};

class UserAuthentication {
private:
    std::unordered_map<std::string, std::string> userCredentials;

public:
    UserAuthentication();
    bool authenticateUser(const std::string& username, const std::string& password);
    void createUser(const std::string& username, const std::string& password);
};

int getInputInteger(const std::string& prompt);
std::string getInputString(const std::string& prompt);
void manageTaskManager();
void manageTasks(TaskManager& taskManager, TaskReminder& taskReminder);

#endif /* TASK_MANAGER_HPP */
