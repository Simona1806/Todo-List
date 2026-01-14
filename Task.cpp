#include "Task.h"

Task::Task(std::string desc, std::string start, std::string end, bool done)
    : description(desc), startTime(start), endTime(end), isDone(done) {}
//Cambia stato
void Task::toggleStatus() {
    isDone = !isDone;
}

std::string Task::getDescription() const { return description; }
std::string Task::getStartTime() const { return startTime; }
std::string Task::getEndTime() const { return endTime; }
bool Task::getStatus() const { return isDone; }

std::string Task::toString() const {
    std::string status = isDone ? "[FATTO]   " : "[DA FARE] ";
    return status + startTime + " - " + endTime + " | " + description;
}