#include "task_manager.hpp"
#include <algorithm>

void TaskManager::addTask(const Task& task) {
    tasks.push_back(task);
    tasksByPriority[task.priority].push_back(task);
}

void TaskManager::displayTasksByPriority(unsigned int priority) {
    if (tasksByPriority.find(priority) != tasksByPriority.end()) {
        std::cout << "Tasks with priority " << priority << ":" << std::endl;
        for (const auto& task : tasksByPriority[priority]) {
            std::cout << "Name: " << task.name << ", Description: " << task.description << ", Deadline: " << task.deadline << ", Completed: " << (task.completed ? "Yes" : "No") << std::endl;
        }
    } else {
        std::cout << "No tasks with priority " << priority << "." << std::endl;
    }
}

void TaskManager::displayAllTasks() {
    std::cout << "All tasks:" << std::endl;
    for (const auto& task : tasks) {
        std::cout << "Name: " << task.name << ", Description: " << task.description << ", Priority: " << task.priority << ", Deadline: " << task.deadline << ", Completed: " << (task.completed ? "Yes" : "No") << std::endl;
    }
}

void TaskManager::markTaskCompleted(size_t index) {
    if (index < tasks.size()) {
        tasks[index].completed = true;
    } else {
        std::cout << "Invalid task index." << std::endl;
    }
}

void TaskManager::editTask(size_t index, const Task& newTask) {
    if (index < tasks.size()) {
        tasks[index] = newTask;
    } else {
        std::cout << "Invalid task index." << std::endl;
    }
}

void TaskManager::sortTasksByPriority() {
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.priority < b.priority;
    });
}

void TaskManager::sortTasksByDeadline() {
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.deadline < b.deadline;
    });
}

void TaskManager::searchTasksByName(const std::string& name) {
    for (const auto& task : tasks) {
        if (task.name == name) {
            std::cout << "Name: " << task.name << ", Description: " << task.description << ", Priority: " << task.priority << ", Deadline: " << task.deadline << ", Completed: " << (task.completed ? "Yes" : "No") << std::endl;
        }
    }
}

int TaskManager::getNumTasks() const {
    return tasks.size();
}

Task TaskManager::getTask(size_t index) const {
    if (index < tasks.size()) {
        return tasks[index];
    } else {
        std::cerr << "Invalid task index." << std::endl;
        return Task();
    }
}

void TaskReminder::setReminder(const Task& task, int reminderType, int reminderFrequency) {
    std::cout << "Reminder set for task: " << task.name << ", Deadline: " << task.deadline << std::endl;

    switch (reminderType) {
        case NOTIFICATION:
            scheduleNotification(task, reminderFrequency);
            break;
        case EMAIL:
            sendEmailReminder(task);
            break;
        case SMS:
            sendSMSReminder(task);
            break;
        default:
            std::cerr << "Invalid reminder type." << std::endl;
    }
}

void TaskReminder::scheduleNotification(const Task& task, int reminderFrequency) {
    switch (reminderFrequency) {
        case ONCE:
            std::cout << "Notification scheduled once for task: " << task.name << ", Deadline: " << task.deadline << std::endl;
            break;
        case DAILY:
            std::cout << "Notification scheduled daily for task: " << task.name << ", Deadline: " << task.deadline << std::endl;
            break;
        case WEEKLY:
            std::cout << "Notification scheduled weekly for task: " << task.name << ", Deadline: " << task.deadline << std::endl;
            break;
        default:
            std::cerr << "Invalid reminder frequency." << std::endl;
    }
}

void TaskReminder::sendEmailReminder(const Task& task) {
    std::cout << "Email reminder sent for task: " << task.name << ", Deadline: " << task.deadline << std::endl;
}

void TaskReminder::sendSMSReminder(const Task& task) {
    std::cout << "SMS reminder sent for task: " << task.name << ", Deadline: " << task.deadline << std::endl;
}

UserAuthentication::UserAuthentication() {
    userCredentials["admin"] = "password123";
}

bool UserAuthentication::authenticateUser(const std::string& username, const std::string& password) {
    if (userCredentials.find(username) != userCredentials.end() && userCredentials[username] == password) {
        std::cout << "User authenticated successfully!" << std::endl;
        return true;
    } else {
        std::cout << "Invalid username or password. Authentication failed." << std::endl;
        return false;
    }
}

void UserAuthentication::createUser(const std::string& username, const std::string& password) {
    userCredentials[username] = password;
    std::cout << "User account created successfully!" << std::endl;
}

int getInputInteger(const std::string& prompt) {
    int input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}

std::string getInputString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::cin.ignore();
    std::getline(std::cin, input);
    return input;
}

void manageTaskManager() {
    TaskManager taskManager;
    TaskReminder taskReminder;
    UserAuthentication userAuth;

    int choice;
    do {
        std::cout << "==============================" << std::endl;
        std::cout << "        Task Manager          " << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "1. Create User Account" << std::endl;
        std::cout << "2. Login" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "==============================" << std::endl;
        choice = getInputInteger("Enter your choice: ");

        switch (choice) {
            case 1: {
                std::string username, password;
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                userAuth.createUser(username, password);
                break;
            }
            case 2: {
                std::string username, password;
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                if (userAuth.authenticateUser(username, password)) {
                    manageTasks(taskManager, taskReminder);
                }
                break;
            }
            case 3:
                std::cout << "Exiting the task manager..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 3);
}

void manageTasks(TaskManager& taskManager, TaskReminder& taskReminder) {
    int taskChoice;
    do {
        std::cout << "==============================" << std::endl;
        std::cout << "        Task Manager          " << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "1. Add Task" << std::endl;
        std::cout << "2. Edit Task" << std::endl;
        std::cout << "3. Mark Task as Completed" << std::endl;
        std::cout << "4. View All Tasks" << std::endl;
        std::cout << "5. Sort Tasks by Priority" << std::endl;
        std::cout << "6. Sort Tasks by Deadline" << std::endl;
        std::cout << "7. Search Tasks by Name" << std::endl;
        std::cout << "8. Set Reminder for a Task" << std::endl;
        std::cout << "9. Logout" << std::endl;
        std::cout << "==============================" << std::endl;
        taskChoice = getInputInteger("Enter your choice: ");

        switch (taskChoice) {
            case 1: {
                std::string name, description, deadline;
                int priority;
                std::cout << "Enter task name: ";
                std::cin >> name;
                std::cout << "Enter task description: ";
                std::cin.ignore();
                std::getline(std::cin, description);
                priority = getInputInteger("Enter task priority (1 - 5): ");
                std::cout << "Enter task deadline (YYYY-MM-DD): ";
                std::cin >> deadline;
                Task task(name, description, priority, deadline);
                taskManager.addTask(task);
                std::cout << "Task added successfully!" << std::endl;
                break;
            }
            case 2: {
                int index;
                index = getInputInteger("Enter the index of the task to edit (1 - " + std::to_string(taskManager.getNumTasks()) + "): ");
                std::string name, description, deadline;
                int priority;
                std::cout << "Enter new task name: ";
                std::cin >> name;
                std::cout << "Enter new task description: ";
                std::cin.ignore();
                std::getline(std::cin, description);
                priority = getInputInteger("Enter new task priority (1 - 5): ");
                std::cout << "Enter new task deadline (YYYY-MM-DD): ";
                std::cin >> deadline;
                Task newTask(name, description, priority, deadline);
                taskManager.editTask(index - 1, newTask);
                std::cout << "Task edited successfully!" << std::endl;
                break;
            }
            case 3: {
                int index;
                index = getInputInteger("Enter the index of the task to mark as completed (1 - " + std::to_string(taskManager.getNumTasks()) + "): ");
                taskManager.markTaskCompleted(index - 1);
                std::cout << "Task marked as completed." << std::endl;
                break;
            }
            case 4:
                taskManager.displayAllTasks();
                break;
            case 5:
                taskManager.sortTasksByPriority();
                std::cout << "Tasks sorted by priority." << std::endl;
                break;
            case 6:
                taskManager.sortTasksByDeadline();
                std::cout << "Tasks sorted by deadline." << std::endl;
                break;
            case 7: {
                std::string name;
                std::cout << "Enter task name to search: ";
                std::cin >> name;
                taskManager.searchTasksByName(name);
                break;
            }
            case 8: {
                int index;
                index = getInputInteger("Enter the index of the task to set a reminder for (1 - " + std::to_string(taskManager.getNumTasks()) + "): ");
                int reminderType, reminderFrequency;
                std::cout << "Choose reminder type:" << std::endl;
                std::cout << "1. Notification" << std::endl;
                std::cout << "2. Email" << std::endl;
                std::cout << "3. SMS" << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> reminderType;
                std::cout << "Choose reminder frequency:" << std::endl;
                std::cout << "1. Once" << std::endl;
                std::cout << "2. Daily" << std::endl;
                std::cout << "3. Weekly" << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> reminderFrequency;
                if (index >= 1 && index <= taskManager.getNumTasks()) {
                    Task task = taskManager.getTask(index - 1);
                    taskReminder.setReminder(task, reminderType, reminderFrequency);
                } else {
                    std::cout << "Invalid task index." << std::endl;
                }
                break;
            }
            case 9:
                std::cout << "Logging out..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }

    } while (taskChoice != 9);
}

/*
int main() {
    manageTaskManager();
    return 0;
}
*/
