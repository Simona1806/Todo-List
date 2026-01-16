#ifndef TODOMANAGER_H
#define TODOMANAGER_H

#include <vector>
#include <string>
#include "Task.h"

class TodoManager {
private:
    std::vector<Task> taskList;
    int nextId=1;
    const std::string fileName = "database_todo.txt";
    void autoSave() const;
    void loadData();

public:
    TodoManager();
    void addEntry(const std::string& desc, const Time& start, const Time& end, bool important = false);
    void removeEntry(int index);
    void changeStatus(int index);
    void showList() const;
    bool hasNoTasks() const;
    bool Overlapping(const Time& newStart, const Time& newEnd) const;
    void sortTasks();
};

#endif