#include "Task.h"

Task::Task(int id, std::string desc, Time start,Time end, bool done, bool important)
    :id(id), description(desc), startTime(start), endTime(end), isDone(done), important(important) {}
//Cambia stato
void Task::toggleStatus() {
    isDone = !isDone;
}

std::string Task::getDescription() const { return description; }
Time Task::getStartTime() const { return startTime; }
Time Task::getEndTime() const { return endTime; }
bool Task::getStatus() const { return isDone; }
bool Task::operator<(const Task& other)const { return startTime < other.startTime; }
int Task::getId()const { return id; }
bool Task::isImportant() const {return important; }

std::string Task::toString() const {
    std::string status = isDone ? "[FATTO]   " : "[DA FARE] ";
    return status + startTime.formatTime() + " - " + endTime.formatTime() + " | " + description;
}