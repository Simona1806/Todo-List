#ifndef TODOMANAGER_H
#define TODOMANAGER_H

#include <vector>
#include <string>
#include "Task.h"

class TodoManager {
private:
    std::vector<Task> taskList;
    const std::string fileName = "database_todo.txt";

    void autoSave() const;
    void loadData();

public:
    TodoManager();

    void addEntry(const std::string& desc, const std::string& start, const std::string& end);
    void removeEntry(int index);
    void changeStatus(int index);

    void showList() const;
    bool hasNoTasks() const;
};

#endif