#ifndef TASK_H
#define TASK_H

#include <string>
#include "Time.h"

class Task {
private:
    std::string description;
    Time startTime;
    Time endTime;
    bool isDone;

public:
    Task(std::string desc, Time start, Time end, bool done = false);
    // Getters
    std::string getDescription() const;
    Time getStartTime() const;
    Time getEndTime() const;
    bool getStatus() const;
    // Metodi
    void toggleStatus();
    std::string toString() const;
};

#endif