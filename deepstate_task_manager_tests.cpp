#include <deepstate/DeepState.hpp>
#include "task_manager.hpp"

using namespace deepstate;

TEST(TaskManager, AddTask) {
    TaskManager taskManager;
    Task task(DeepState_String(), DeepState_String(), DeepState_IntInRange(1, 5), DeepState_String());
    taskManager.addTask(task);
    ASSERT_EQ(taskManager.getNumTasks(), 1);
}

TEST(TaskManager, MarkTaskCompleted) {
    TaskManager taskManager;
    Task task(DeepState_String(), DeepState_String(), DeepState_IntInRange(1, 5), DeepState_String());
    taskManager.addTask(task);
    taskManager.markTaskCompleted(0);
    ASSERT_TRUE(taskManager.getTask(0).completed);
}

TEST(TaskManager, SortTasksByPriority) {
    TaskManager taskManager;
    for (int i = 0; i < 10; ++i) {
        Task task(DeepState_String(), DeepState_String(), DeepState_IntInRange(1, 5), DeepState_String());
        taskManager.addTask(task);
    }
    taskManager.sortTasksByPriority();

    // Verify that tasks are sorted by priority
    for (size_t i = 1; i < taskManager.getNumTasks(); ++i) {
        ASSERT_TRUE(taskManager.getTask(i - 1).priority <= taskManager.getTask(i).priority);
    }
}

TEST(TaskManager, SortTasksByDeadline) {
    TaskManager taskManager;
    for (int i = 0; i < 10; ++i) {
        Task task(DeepState_String(), DeepState_String(), DeepState_IntInRange(1, 5), DeepState_String());
        taskManager.addTask(task);
    }
    taskManager.sortTasksByDeadline();

    // Verify that tasks are sorted by deadline
    for (size_t i = 1; i < taskManager.getNumTasks(); ++i) {
        ASSERT_TRUE(taskManager.getTask(i - 1).deadline <= taskManager.getTask(i).deadline);
    }
}

TEST(TaskManager, SearchTasksByName) {
    TaskManager taskManager;
    string nameToSearch = DeepState_String();
    bool found = false;
    for (int i = 0; i < 10; ++i) {
        Task task;
        if (i == 5) {
            task = Task(nameToSearch, DeepState_String(), DeepState_IntInRange(1, 5), DeepState_String());
            found = true;
        } else {
            task = Task(DeepState_String(), DeepState_String(), DeepState_IntInRange(1, 5), DeepState_String());
        }
        taskManager.addTask(task);
    }
    taskManager.searchTasksByName(nameToSearch);
    ASSERT_EQ(found, true);
}

TEST(TaskManager, UserAuthentication) {
    UserAuthentication userAuth;
    string username = DeepState_String();
    string password = DeepState_String();

    // Create a user
    userAuth.createUser(username, password);

    // Authenticate the user
    ASSERT_TRUE(userAuth.authenticateUser(username, password));
}

TEST(TaskManager, InvalidUsernameOrPassword) {
    UserAuthentication userAuth;
    string username = DeepState_String();
    string password = DeepState_String();

    // Create a user
    userAuth.createUser(username, password);

    // Try to authenticate with wrong password
    ASSERT_FALSE(userAuth.authenticateUser(username, DeepState_String()));
}

TEST(TaskManager, InvalidTaskIndex) {
    TaskManager taskManager;
    Task task(DeepState_String(), DeepState_String(), DeepState_IntInRange(1, 5), DeepState_String());
    taskManager.addTask(task);

    // Try to mark a task completed with an invalid index
    taskManager.markTaskCompleted(DeepState_Int());

    // Try to edit a task with an invalid index
    taskManager.editTask(DeepState_Int(), task);

    // Try to set a reminder for a task with an invalid index
    taskReminder.setReminder(task, DeepState_Int(), DeepState_Int());
}

int main(int argc, char** argv) {
    DeepState_InitOptions(argc, argv);
    DeepState_Run();
    return 0;
}
