#ifndef TIME_H
#define TIME_H

#include <string>

class Time {
private:
    int hours;
    int minutes;

public:
    Time(int h = 0, int m = 0);

    // Operatori di confronto
    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>=(const Time& other) const;
    bool operator==(const Time& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Time& t);

    // Per stampare l'orario in formato HH:MM
    std::string formatTime() const;
    
    // Getters per il salvataggio su file
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
};

#endif