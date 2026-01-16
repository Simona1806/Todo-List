#ifndef TASK_H
#define TASK_H

#include <string>
#include "Time.h"

class Task {
private:
    int id;
    std::string description;
    Time startTime;
    Time endTime;
    bool isDone;
    bool important;


public:
    Task(int id, std::string desc, Time start, Time end, bool done = false, bool important = false);
    // Getters
    std::string getDescription() const;
    Time getStartTime() const ;
    Time getEndTime() const;
    bool getStatus() const ;
    bool isImportant() const;
    int getId() const;
    // Metodi
    void toggleStatus();
    std::string toString() const;
    bool operator<(const Task& other) const;
};

#endif