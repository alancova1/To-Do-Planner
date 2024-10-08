#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Task {
public:
    string name;

    Task(string taskName) : name(taskName) {}
};

class TodoList {
private:
    vector<Task> tasks;

public:
    void addTask(const string &taskName) {
        tasks.push_back(Task(taskName));
        cout << "Task added: " << taskName << endl;
    }

    void viewTasks() {
        if (tasks.empty()) {
            cout << "No tasks in the list." << endl;
            return;
        }
        cout << "To-Do List:" << endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i].name << endl;
        }
    }

    void deleteTask(int taskIndex) {
        if (taskIndex < 1 || taskIndex > tasks.size()) {
            cout << "Invalid task number." << endl;
            return;
        }
        cout << "Task deleted: " << tasks[taskIndex - 1].name << endl;
        tasks.erase(tasks.begin() + (taskIndex - 1));
    }
};

int main() {
    TodoList todoList;
    int choice;
    string taskName;

    do {
        cout << "\nTo-Do List Planner" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Delete Task" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter task name: ";
                cin.ignore(); 
                getline(cin, taskName);
                todoList.addTask(taskName);
                break;
            case 2:
                todoList.viewTasks();
                break;
            case 3:
                int taskIndex;
                cout << "Enter task number to delete: ";
                cin >> taskIndex;
                todoList.deleteTask(taskIndex);
                break;
            case 4:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}