#include "TimeCode.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
using namespace std;

// Constructor
TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec) {
    t = ComponentsToSeconds(hr, min, sec);
}

// Copy Constructor
TimeCode::TimeCode(const TimeCode& tc) {
    t = tc.t;
}

// Reset TimeCode to 0
void TimeCode::reset() {
    t = 0;
}

// Setters
void TimeCode::SetHours(unsigned int hours) {
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(hours, m, s);
}

void TimeCode::SetMinutes(unsigned int minutes) {
    if (minutes >= 60) throw invalid_argument("Minutes must be < 60");
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(h, minutes, s);
}

void TimeCode::SetSeconds(unsigned int seconds) {
    if (seconds >= 60) throw invalid_argument("Seconds must be < 60");
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(h, m, seconds);
}

// Getters
unsigned int TimeCode::GetHours() const {
    unsigned int h, m, s;
    GetComponents(h, m, s);
    return h;
}

unsigned int TimeCode::GetMinutes() const {
    unsigned int h, m, s;
    GetComponents(h, m, s);
    return m;
}

unsigned int TimeCode::GetSeconds() const {
    unsigned int h, m, s;
    GetComponents(h, m, s);
    return s;
}

// Convert total seconds into hours, minutes, and seconds
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const {
    hr = t / 3600;
    min = (t % 3600) / 60;
    sec = t % 60;
}

// Convert components to total seconds
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec) {
    return (hr * 3600) + (min * 60) + sec;
}

// Convert to string format hh:mm:ss
string TimeCode::ToString() const {
    unsigned int h, m, s;
    GetComponents(h, m, s);
    stringstream ss;
    ss << h << ":" << m << ":" << s;
    return ss.str();
}

// Operators
TimeCode TimeCode::operator+(const TimeCode& other) const {
    return TimeCode(0, 0, t + other.t);
}

TimeCode TimeCode::operator-(const TimeCode& other) const {
    if (t < other.t) throw invalid_argument("Negative TimeCode is not allowed");
    return TimeCode(0, 0, t - other.t);
}

TimeCode TimeCode::operator*(double a) const {
    return TimeCode(0, 0, static_cast<long long unsigned int>(t * a));
}

TimeCode TimeCode::operator/(double a) const {
    if (a == 0) throw invalid_argument("Division by zero");
    return TimeCode(0, 0, static_cast<long long unsigned int>(t / a));
}

// Comparisons
bool TimeCode::operator==(const TimeCode& other) const { return t == other.t; }
bool TimeCode::operator!=(const TimeCode& other) const { return t != other.t; }
bool TimeCode::operator<(const TimeCode& other) const { return t < other.t; }
bool TimeCode::operator<=(const TimeCode& other) const { return t <= other.t; }
bool TimeCode::operator>(const TimeCode& other) const { return t > other.t; }
bool TimeCode::operator>=(const TimeCode& other) const { return t >= other.t; }