#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <map>

using namespace std;

struct Task {
    string name;
    string description;
    int priority;
    string deadline;
    bool completed;
    Task(string n, string desc, int pri, string ddl) : name(n), description(desc), priority(pri), deadline(ddl), completed(false) {}
};

class TaskManager {
private:
    unordered_map<int, vector<Task>> tasksByPriority;
    vector<Task> tasks;

public:
    void addTask(const Task& task);

    void displayTasksByPriority(int priority);

    void displayAllTasks();

    void markTaskCompleted(int index);

    void editTask(int index, const Task& newTask);

    void sortTasksByPriority();

    void sortTasksByDeadline();

    void searchTasksByName(const string& name);

    int getNumTasks() const;

    Task getTask(int index) const;
};

class TaskReminder {
public:
    enum ReminderType {
        NOTIFICATION,
        EMAIL,
        SMS
    };

    enum ReminderFrequency {
        ONCE,
        DAILY,
        WEEKLY
    };

    void setReminder(const Task& task, int reminderType = NOTIFICATION, int reminderFrequency = ONCE);

    void scheduleNotification(const Task& task, int reminderFrequency);

    void sendEmailReminder(const Task& task);

    void sendSMSReminder(const Task& task);
};

class UserAuthentication {
private:
    map<string, string> userCredentials;

public:
    UserAuthentication();

    bool authenticateUser(const string& username, const string& password);

    void createUser(const string& username, const string& password);
};

int getInputInteger(const string& prompt);

string getInputString(const string& prompt);

#endif
