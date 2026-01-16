#include "Time.h"
#include <iomanip>
#include <sstream>

Time::Time(int h, int m) {
    if (h >= 0 && h < 24) hours(h); else hours(0);
    if (m >= 0 && m < 60) minutes(m); else minutes(0);
}
//overloading degli operatori per poterli usare nel confronto delle ore e minuti
bool Time::operator==(const Time& other) const {
    return hours == other.hours && minutes == other.minutes;
}
bool Time::operator<(const Time& other) const {
    if (hours != other.hours) {
        return hours < other.hours;
    }
    return minutes < other.minutes;
}
bool Time::operator<=(const Time& other) const {
    return (*this < other) || (*this == other);
}
bool Time::operator>(const Time& other) const {
    return !(*this <= other);
}
bool Time::operator>=(const Time& other) const {
    return !(*this < other);
}
//overlaoding dell'operatore << per poter inserire correttamente l'orario sul file
std::ostream& operator<<(std::ostream& os, const Time& t) {
    os << t.formatTime();
    return os;
}
//funzione che permette di rendere il formato time in stringa per poterlo stampare sul terminale,
//ma anche per poterlo inserire sul file correttamente
std::string Time::formatTime() const {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << hours << ":"
       << std::setw(2) << std::setfill('0') << minutes;
    return ss.str();
}