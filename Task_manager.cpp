#include "task_manager.hpp"

void TaskManager::addTask(const Task& task) {
    tasks.push_back(task);
    tasksByPriority[task.priority].push_back(task);
}

void TaskManager::displayTasksByPriority(int priority) {
    if (tasksByPriority.find(priority) != tasksByPriority.end()) {
        cout << "Tasks with priority " << priority << ":" << endl;
        for (const auto& task : tasksByPriority[priority]) {
            cout << "Name: " << task.name << ", Description: " << task.description << ", Deadline: " << task.deadline << ", Completed: " << (task.completed ? "Yes" : "No") << endl;
        }
    } else {
        cout << "No tasks with priority " << priority << "." << endl;
    }
}

void TaskManager::displayAllTasks() {
    cout << "All tasks:" << endl;
    for (const auto& task : tasks) {
        cout << "Name: " << task.name << ", Description: " << task.description << ", Priority: " << task.priority << ", Deadline: " << task.deadline << ", Completed: " << (task.completed ? "Yes" : "No") << endl;
    }
}

void TaskManager::markTaskCompleted(int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks[index].completed = true;
    }
}

void TaskManager::editTask(int index, const Task& newTask) {
    if (index >= 0 && index < tasks.size()) {
        tasks[index] = newTask;
    }
}

void TaskManager::sortTasksByPriority() {
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.priority < b.priority;
    });
}

void TaskManager::sortTasksByDeadline() {
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.deadline < b.deadline;
    });
}

void TaskManager::searchTasksByName(const string& name) {
    cout << "Search results for tasks with name '" << name << "':" << endl;
    bool found = false;
    for (const auto& task : tasks) {
        if (task.name == name) {
            cout << "Name: " << task.name << ", Description: " << task.description << ", Priority: " << task.priority << ", Deadline: " << task.deadline << ", Completed: " << (task.completed ? "Yes" : "No") << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No tasks found with name '" << name << "'." << endl;
    }
}

int TaskManager::getNumTasks() const {
    return tasks.size();
}

Task TaskManager::getTask(int index) const {
    if (index >= 0 && index < tasks.size()) {
        return tasks[index];
    } else {
        return Task("", "", 0, "");
    }
}

void TaskReminder::setReminder(const Task& task, int reminderType, int reminderFrequency) {
    cout << "Reminder set for task: " << task.name << ", Deadline: " << task.deadline << endl;

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
    }
}

void TaskReminder::scheduleNotification(const Task& task, int reminderFrequency) {
    switch (reminderFrequency) {
        case ONCE:
            cout << "Notification scheduled once for task: " << task.name << ", Deadline: " << task.deadline << endl;
            break;
        case DAILY:
            cout << "Notification scheduled daily for task: " << task.name << ", Deadline: " << task.deadline << endl;
            break;
        case WEEKLY:
            cout << "Notification scheduled weekly for task: " << task.name << ", Deadline: " << task.deadline << endl;
            break;
    }
}

void TaskReminder::sendEmailReminder(const Task& task) {
    cout << "Email reminder sent for task: " << task.name << ", Deadline: " << task.deadline << endl;
}

void TaskReminder::sendSMSReminder(const Task& task) {
    cout << "SMS reminder sent for task: " << task.name << ", Deadline: " << task.deadline << endl;
}

UserAuthentication::UserAuthentication() {
    userCredentials["admin"] = "password123";
}

bool UserAuthentication::authenticateUser(const string& username, const string& password) {
    if (userCredentials.find(username) != userCredentials.end() && userCredentials[username] == password) {
        cout << "User authenticated successfully!" << endl;
        return true;
    } else {
        cout << "Invalid username or password. Authentication failed." << endl;
        return false;
    }
}

void UserAuthentication::createUser(const string& username, const string& password) {
    userCredentials[username] = password;
    cout << "User account created successfully!" << endl;
}
int getInputInteger(const string& prompt) {
    int input;
    cout << prompt;
    cin >> input;
    return input;
}

string getInputString(const string& prompt) {
    string input;
    cout << prompt;
    cin.ignore();
    getline(cin, input);
    return input;
}

int main() {
    TaskManager taskManager;
    TaskReminder taskReminder;
    UserAuthentication userAuth;

    int choice;
    do {
        cout << "==============================" << endl;
        cout << "        Task Manager          " << endl;
        cout << "==============================" << endl;
        cout << "1. Create User Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "==============================" << endl;
        choice = getInputInteger("Enter your choice: ");

        switch (choice) {
            case 1: {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                userAuth.createUser(username, password);
                break;
            }
            case 2: {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                if (userAuth.authenticateUser(username, password)) {
                    int taskChoice;
                    do {
                        cout << "==============================" << endl;
                        cout << "        Task Manager          " << endl;
                        cout << "==============================" << endl;
                        cout << "1. Add Task" << endl;
                        cout << "2. Edit Task" << endl;
                        cout << "3. Mark Task as Completed" << endl;
                        cout << "4. View All Tasks" << endl;
                        cout << "5. Sort Tasks by Priority" << endl;
                        cout << "6. Sort Tasks by Deadline" << endl;
                        cout << "7. Search Tasks by Name" << endl;
                        cout << "8. Set Reminder for a Task" << endl;
                        cout << "9. Logout" << endl;
                        cout << "==============================" << endl;
                        taskChoice = getInputInteger("Enter your choice: ");

                        switch (taskChoice) {
                            case 1: {
                                string name, description, deadline;
                                int priority;
                                cout << "Enter task name: ";
                                cin >> name;
                                cout << "Enter task description: ";
                                cin.ignore();
                                getline(cin, description);
                                priority = getInputInteger("Enter task priority (1 - 5): ");
                                cout << "Enter task deadline (YYYY-MM-DD): ";
                                cin >> deadline;
                                Task task(name, description, priority, deadline);
                                taskManager.addTask(task);
                                cout << "Task added successfully!" << endl;
                                break;
                            }
                            case 2: {
                                int index;
                                index = getInputInteger("Enter the index of the task to edit (1 - " + to_string(taskManager.getNumTasks()) + "): ");
                                string name, description, deadline;
                                int priority;
                                cout << "Enter new task name: ";
                                cin >> name;
                                cout << "Enter new task description: ";
                                cin.ignore();
                                getline(cin, description);
                                priority = getInputInteger("Enter new task priority (1 - 5): ");
                                cout << "Enter new task deadline (YYYY-MM-DD): ";
                                cin >> deadline;
                                Task newTask(name, description, priority, deadline);
                                taskManager.editTask(index - 1, newTask);
                                cout << "Task edited successfully!" << endl;
                                break;
                            }
                            case 3: {
                                int index;
                                index = getInputInteger("Enter the index of the task to mark as completed (1 - " + to_string(taskManager.getNumTasks()) + "): ");
                                taskManager.markTaskCompleted(index - 1);
                                cout << "Task marked as completed." << endl;
                                break;
                            }
                            case 4:
                                taskManager.displayAllTasks();
                                break;
                            case 5:
                                taskManager.sortTasksByPriority();
                                cout << "Tasks sorted by priority." << endl;
                                break;
                            case 6:
                                taskManager.sortTasksByDeadline();
                                cout << "Tasks sorted by deadline." << endl;
                                break;
                            case 7: {
                                string name;
                                cout << "Enter task name to search: ";
                                cin >> name;
                                taskManager.searchTasksByName(name);
                                break;
                            }
                            case 8: {
                                int index;
                                index = getInputInteger("Enter the index of the task to set a reminder for (1 - " + to_string(taskManager.getNumTasks()) + "): ");
                                int reminderType, reminderFrequency;
                                cout << "Choose reminder type:" << endl;
                                cout << "1. Notification" << endl;
                                cout << "2. Email" << endl;
                                cout << "3. SMS" << endl;
                                cout << "Enter your choice: ";
                                cin >> reminderType;
                                cout << "Choose reminder frequency:" << endl;
                                cout << "1. Once" << endl;
                                cout << "2. Daily" << endl;
                                cout << "3. Weekly" << endl;
                                cout << "Enter your choice: ";
                                cin >> reminderFrequency;
                                if (index >= 1 && index <= taskManager.getNumTasks()) {
                                    Task task = taskManager.getTask(index - 1);
                                    taskReminder.setReminder(task, reminderType, reminderFrequency);
                                } else {
                                    cout << "Invalid task index." << endl;
                                }
                                break;
                            }
                            case 9:
                                cout << "Logging out..." << endl;
                                break;
                            default:
                                cout << "Invalid choice. Please try again." << endl;
                        }

                    } while (taskChoice != 9);
                }
                break;
            }
            case 3:
                cout << "Exiting the task manager..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
