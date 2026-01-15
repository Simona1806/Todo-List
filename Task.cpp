#include "Task.h"

Task::Task(std::string desc, Time start,Time end, bool done)
    : description(desc), startTime(start), endTime(end), isDone(done) {}
//Cambia stato
void Task::toggleStatus() {
    isDone = !isDone;
}

std::string Task::getDescription() const { return description; }
Time Task::getStartTime() const { return startTime; }
Time Task::getEndTime() const { return endTime; }
bool Task::getStatus() const { return isDone; }
bool Task::operator<(const Task& other)const { return this->startTime < other.startTime; }

std::string Task::toString() const {
    std::string status = isDone ? "[FATTO]   " : "[DA FARE] ";
    return status + startTime.formatTime() + " - " + endTime.formatTime() + " | " + description;
}