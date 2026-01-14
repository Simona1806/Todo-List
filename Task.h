#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
private:
    std::string description;
    std::string startTime;
    std::string endTime;
    bool isDone;

public:
    Task(std::string desc, std::string start, std::string end, bool done = false);
    // Getters
    std::string getDescription() const;
    std::string getStartTime() const;
    std::string getEndTime() const;
    bool getStatus() const;
    // Metodi
    void toggleStatus();
    std::string toString() const;
};

#endif